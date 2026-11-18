#pragma once

#include "app/app.h"
#include "app/desktop_helper_script.h"
#include "common/notification_feed.h"
#include "include/cef_parser.h"
#include "include/cef_request.h"
#include "include/cef_request_context.h"
#include "include/cef_urlrequest.h"
#include "include/cef_task.h"
#include "include/wrapper/cef_helpers.h"
#include "include/views/cef_browser_view.h"
#include <algorithm>
#include <cmath>

namespace oa {
namespace {
using Clock = std::chrono::steady_clock;

class PetTask : public CefTask {
 public:
  explicit PetTask(std::function<void()> function) : function_(std::move(function)) {}
  void Execute() override { function_(); }
 private:
  std::function<void()> function_;
  IMPLEMENT_REFCOUNTING(PetTask);
};

std::string Origin(const std::string& url) {
  CefURLParts parts;
  if (!CefParseURL(url, parts) || !CefString(&parts.username).empty() || !CefString(&parts.password).empty()) return {};
  const auto scheme = CefString(&parts.scheme).ToString();
  if (scheme != "https" && scheme != "http") return {};
  return CefString(&parts.origin).ToString();
}

bool Hex64(const std::string& value) {
  return value.size() == 64 && std::all_of(value.begin(), value.end(), [](char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
  });
}

bool Integer(CefRefPtr<CefDictionaryValue> object, const char* key, int64_t& output) {
  if (!object || (object->GetType(key) != VTYPE_INT && object->GetType(key) != VTYPE_DOUBLE)) return false;
  const double value = object->GetType(key) == VTYPE_INT ? object->GetInt(key) : object->GetDouble(key);
  if (!std::isfinite(value) || value < 0 || value > 9007199254740991.0 || std::floor(value) != value) return false;
  output = static_cast<int64_t>(value);
  return true;
}

//2026.11.17 by codex, issue asynchronous no-cache requests with no stored credentials or redirect token forwarding.
class FeedRequest : public CefURLRequestClient {
 public:
  std::function<void(int, std::string)> complete;
  void OnRequestComplete(CefRefPtr<CefURLRequest> request) override {
    auto response = request->GetResponse();
    const int status = request->GetRequestStatus() == UR_SUCCESS && response ? response->GetStatus() : 0;
    auto callback = std::move(complete);
    if (callback) callback(status, std::move(body_));
  }
  void OnUploadProgress(CefRefPtr<CefURLRequest>, int64_t, int64_t) override {}
  void OnDownloadProgress(CefRefPtr<CefURLRequest>, int64_t, int64_t) override {}
  void OnDownloadData(CefRefPtr<CefURLRequest> request, const void* data, size_t size) override {
    if (body_.size() + size > 262144) { body_.clear(); request->Cancel(); return; }
    body_.append(static_cast<const char*>(data), size);
  }
  bool GetAuthCredentials(bool, const CefString&, int, const CefString&, const CefString&,
      CefRefPtr<CefAuthCallback>) override { return false; }
 private:
  std::string body_;
  IMPLEMENT_REFCOUNTING(FeedRequest);
};

template<class DesktopPet>
class DesktopHelperSession : public DesktopHelper, public std::enable_shared_from_this<DesktopHelperSession<DesktopPet>> {
 public:
  explicit DesktopHelperSession(std::shared_ptr<AppContext> context) : context_(context) {}
  ~DesktopHelperSession() override { Cancel(); }

  void Stop() override {
    CEF_REQUIRE_UI_THREAD();
    ++epoch_;
    if (browser_ && browser_->IsValid() && browser_->GetMainFrame()) {
      browser_->GetMainFrame()->ExecuteJavaScript("if(window.__oaPet)window.__oaPet.stop();", "", 0);
    }
    browser_ = nullptr;
    ResetSession();
  }

  bool Toggle() override {
    if (!logged_) {
      if constexpr (requires(DesktopPet& pet) { pet.SetResumeHandler(std::function<void()>{}); }) {
        hidden_ = false;
        Resume();
      }
      return false;
    }
    hidden_ = !hidden_;
    if (hidden_ || !logged_) pet_.Hide();
    else { pet_.Show(); Present(); }
    return logged_ && !hidden_;
  }

  CefRefPtr<CefImage> Icon() override { return pet_.Icon(); }

  void Loaded(CefRefPtr<CefBrowser> browser) override {
    Stop();
    auto context = context_.lock();
    if (!context || context->closing_in_background || browser->IsPopup() ||
        Origin(browser->GetMainFrame()->GetURL()) != Origin(context->settings.home_url) ||
        Origin(context->settings.home_url).empty()) return;
    browser_ = browser;
    if constexpr (requires(DesktopPet& pet) { pet.SetResumeHandler(std::function<void()>{}); }) {
      pet_.SetResumeHandler([weak = this->weak_from_this()] {
        if (auto self = weak.lock()) self->Resume();
      });
    }
    pet_.SetBrowseHandlers([weak = this->weak_from_this()] {
      if (auto self = weak.lock(); self && self->logged_ && !self->hidden_) {
        self->history_.Show();
        self->Present();
      }
    }, [weak = this->weak_from_this()](int direction) {
      if (auto self = weak.lock(); self && self->logged_ && !self->hidden_) {
        self->history_.Move(direction);
        self->Present();
      }
    });
    browser_->GetMainFrame()->ExecuteJavaScript(std::string(kDesktopHelperInstall) + "(" + std::to_string(epoch_) + ");", "", 0);
    Tick(epoch_, ++tick_generation_);
  }

  bool Message(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source,
      CefRefPtr<CefProcessMessage> message) override {
    CEF_REQUIRE_UI_THREAD();
    if (message->GetName() != "oa.pet") return false;
    auto context = context_.lock();
    if (!context || context->closing_in_background || !browser_ || !browser_->IsSame(browser) ||
        browser->IsPopup() || source != PID_RENDERER || !frame->IsMain() ||
        frame->GetIdentifier() != browser_->GetMainFrame()->GetIdentifier() ||
        Origin(frame->GetURL()) != Origin(context->settings.home_url) ||
        message->GetArgumentList()->GetSize() != 1) return true;
    const auto text = message->GetArgumentList()->GetString(0);
    if (text.length() > 65536) return true;
    auto value = CefParseJSON(text, JSON_PARSER_RFC);
    if (!value || value->GetType() != VTYPE_DICTIONARY) return true;
    auto data = value->GetDictionary();
    if (data->GetType("epoch") != VTYPE_INT || data->GetInt("epoch") != epoch_) return true;
    const auto kind = data->GetString("kind").ToString();
    if (kind == "state") State(data);
    else if (kind == "wake") {
      if (logged_ && Identity(data) == identity_) { dirty_ = true; Fetch(); }
    } else if ((kind == "grant" || kind == "connect-error") && connecting_ &&
        logged_ && data->GetString("identity") == identity_) {
      connecting_ = false;
      if (kind == "grant" && data->GetType("grant") == VTYPE_DICTIONARY) Grant(data->GetDictionary("grant"));
    } else if (kind == "opened") {
      history_.Hide();
      pet_.CloseMessage();
    } else if (kind == "editing") {
      pet_.Notify("詢報價單尚在編輯，請先儲存或取消後再點通知。", [weak = this->weak_from_this()] {
        if (auto self = weak.lock()) self->Open();
      }, [weak = this->weak_from_this()] {
        if (auto self = weak.lock()) self->history_.Hide();
      });
    }
    return true;
  }

 private:
  std::weak_ptr<AppContext> context_;
  CefRefPtr<CefBrowser> browser_;
  DesktopPet pet_;
  NotificationFeed feed_;
  CefRefPtr<CefURLRequest> request_;
  CefRefPtr<FeedRequest> request_client_;
  NotificationHistory history_;
  std::string identity_, api_, token_;
  int epoch_ = 0, request_generation_ = 0, tick_generation_ = 0;
  bool logged_ = false, hidden_ = false, connecting_ = false, dirty_ = false;
  Clock::time_point next_connect_{}, next_fetch_{}, deadline_{};

  void Cancel() {
    ++request_generation_;
    if (request_client_) request_client_->complete = {};
    if (request_) request_->Cancel();
    request_ = nullptr; request_client_ = nullptr;
  }

  //2026.11.18 by codex, replace stale native work after Windows resume and recheck the current page before reconnecting.
  void Resume() {
    auto context = context_.lock();
    if (!context || context->closing_in_background || !browser_ || !browser_->IsValid()) return;
    Cancel();
    connecting_ = false;
    token_.clear();
    next_connect_ = {}; next_fetch_ = {}; deadline_ = {};
    AppendLog(context->paths, "PET_RESUME_RECHECK");
    //2026.11.18 by codex, renew the observer generation while retaining the same-scope cursor and session history.
    ++epoch_;
    browser_->GetMainFrame()->ExecuteJavaScript(std::string(kDesktopHelperInstall) + "(" + std::to_string(epoch_) + ");", "", 0);
    Tick(epoch_, ++tick_generation_);
  }

  void ResetSession() {
    Cancel();
    logged_ = false; connecting_ = false; dirty_ = false;
    identity_.clear(); api_.clear(); token_.clear(); feed_ = {};
    history_.Clear(); pet_.Hide();
    next_connect_ = {}; next_fetch_ = {};
  }

  std::string Identity(CefRefPtr<CefDictionaryValue> state) {
    auto list = CefListValue::Create();
    list->SetString(0, state->GetString("api"));
    list->SetString(1, state->GetString("user"));
    list->SetString(2, state->GetString("database"));
    auto value = CefValue::Create(); value->SetList(list);
    return CefWriteJSON(value, JSON_WRITER_DEFAULT).ToString();
  }

  void State(CefRefPtr<CefDictionaryValue> data) {
    const bool logged = data->GetType("logged") == VTYPE_BOOL && data->GetBool("logged");
    const auto api = data->GetString("api").ToString();
    const auto identity = Identity(data);
    if (!logged || data->GetString("user").empty()) { ResetSession(); return; }
    if (identity != identity_) {
      ResetSession();
      identity_ = identity; logged_ = true;
      CefURLParts parts;
      const auto origin = Origin(api);
      if (!origin.empty() && CefParseURL(api, parts) && CefString(&parts.query).empty() && CefString(&parts.fragment).empty()) {
        const auto scheme = CefString(&parts.scheme).ToString();
        const auto host = CefString(&parts.host).ToString();
        //2026.11.17 by codex, require TLS for notification grants except isolated loopback verification.
        if (scheme == "https" || (scheme == "http" && (host == "127.0.0.1" || host == "localhost"))) {
          api_ = api + (api.ends_with('/') ? "" : "/");
        }
      }
    }
    if (!hidden_) pet_.Show();
    if (!api_.empty() && token_.empty() && !connecting_ && Clock::now() >= next_connect_) Connect();
  }

  void Connect() {
    connecting_ = true;
    deadline_ = Clock::now() + std::chrono::seconds(10);
    next_connect_ = Clock::now() + std::chrono::seconds(60);
    browser_->GetMainFrame()->ExecuteJavaScript("window.__oaPet&&window.__oaPet.connect(" +
      QuoteJavaScript(api_) + "," + QuoteJavaScript(identity_) + ");", "", 0);
  }

  void Grant(CefRefPtr<CefDictionaryValue> grant) {
    int64_t cursor, expires;
    const auto token = grant->GetString("token").ToString();
    const auto scope = grant->GetString("scope").ToString();
    const auto date = grant->GetString("date").ToString();
    if (!Hex64(token) || !Hex64(scope) || !NotificationFeed::ValidDate(date) ||
        !Integer(grant, "cursor", cursor) || !Integer(grant, "expires_at", expires)) return;
    token_ = token;
    feed_.Connect(scope, date, cursor);
    next_fetch_ = {};
    Fetch();
  }

  void Tick(int epoch, int generation) {
    if (epoch != epoch_ || generation != tick_generation_ || !browser_ || !browser_->IsValid()) return;
    browser_->GetMainFrame()->ExecuteJavaScript("window.__oaPet&&window.__oaPet.poll();", "", 0);
    if (Clock::now() >= deadline_) {
      if (request_) { Cancel(); next_fetch_ = Clock::now() + std::chrono::seconds(10); }
      if (connecting_) connecting_ = false;
    }
    if (logged_ && !token_.empty() && Clock::now() >= next_fetch_) Fetch();
    auto weak = this->weak_from_this();
    CefPostDelayedTask(TID_UI, new PetTask([weak, epoch, generation] {
      if (auto self = weak.lock()) self->Tick(epoch, generation);
    }), 500);
  }

  void Fetch() {
    if (!logged_ || token_.empty() || request_) return;
    dirty_ = false;
    auto request = CefRequest::Create();
    request->SetURL(api_ + "desktop-helper/changes?date=" + feed_.date + "&cursor=" + std::to_string(feed_.cursor));
    request->SetMethod("GET");
    request->SetHeaderByName("Authorization", "Bearer " + token_, true);
    request->SetHeaderByName("Accept", "application/json", true);
    request->SetFlags(UR_FLAG_DISABLE_CACHE | UR_FLAG_STOP_ON_REDIRECT | UR_FLAG_NO_RETRY_ON_5XX);
    const auto epoch = epoch_, generation = ++request_generation_;
    const auto identity = identity_;
    auto client = new FeedRequest;
    client->complete = [weak = this->weak_from_this(), epoch, generation, identity](int status, std::string body) {
      auto self = weak.lock();
      if (!self || self->epoch_ != epoch || self->request_generation_ != generation || self->identity_ != identity) return;
      self->request_ = nullptr; self->request_client_ = nullptr;
      self->next_fetch_ = Clock::now() + std::chrono::seconds(10);
      if (status == 401 || status == 403) {
        self->token_.clear(); self->history_.Clear(); self->pet_.Hide();
        self->next_connect_ = Clock::now() + std::chrono::seconds(60);
        return;
      }
      if (status == 200) self->Changes(body);
      if (self->dirty_) self->Fetch();
    };
    request_client_ = client;
    deadline_ = Clock::now() + std::chrono::seconds(10);
    next_fetch_ = deadline_;
    request_ = CefURLRequest::Create(request, client, CefRequestContext::GetGlobalContext());
    if (!request_) { request_client_ = nullptr; next_fetch_ = Clock::now() + std::chrono::seconds(10); }
  }

  void Changes(const std::string& body) {
    auto value = CefParseJSON(body, JSON_PARSER_RFC);
    if (!value || value->GetType() != VTYPE_DICTIONARY) return;
    auto data = value->GetDictionary();
    int64_t cursor;
    if (!Integer(data, "cursor", cursor) || data->GetType("gap") != VTYPE_BOOL || data->GetType("events") != VTYPE_LIST) return;
    auto events = data->GetList("events");
    if (events->GetSize() > 100) return;
    std::vector<OrderNotification> parsed, fresh;
    for (size_t i = 0; i < events->GetSize(); ++i) {
      if (events->GetType(i) != VTYPE_DICTIONARY) return;
      auto event = events->GetDictionary(i);
      int64_t id;
      if (!Integer(event, "id", id)) return;
      parsed.push_back({id, event->GetString("action"), event->GetString("quano")});
    }
    if (!feed_.Apply(data->GetString("date"), cursor, data->GetBool("gap"), parsed, fresh)) return;
    if (data->GetBool("gap")) history_.Add({0, "gap", ""});
    for (auto& event : fresh) history_.Add(std::move(event));
    if (events->GetSize() == 100) dirty_ = true;
    if (data->GetBool("gap") || !fresh.empty()) { history_.Show(); Present(); }
  }

  void Present() {
    if (hidden_ || !logged_ || !history_.visible()) return;
    const auto event = history_.current();
    const auto text = !event ? std::string("目前沒有訊息") :
      (event->action == "gap" ? "通知紀錄有缺口，請回 ERP 確認今天的詢報價單。" :
      std::string(event->action == "add" ? "新增詢報價：" : "修改詢報價：") + event->order) +
      "\n" + std::to_string(history_.position()) + " / " + std::to_string(history_.size()) + "　↑ 上一則　↓ 下一則";
    pet_.Notify(text, [weak = this->weak_from_this()] { if (auto self = weak.lock()) self->Open(); },
      [weak = this->weak_from_this()] { if (auto self = weak.lock()) self->history_.Hide(); });
  }

  void Open() {
    auto context = context_.lock();
    if (!logged_ || !context || context->closing_in_background || !browser_ || !history_.current()) return;
    if (auto view = CefBrowserView::GetForBrowser(browser_)) {
      if (auto window = view->GetWindow()) {
        if (window->IsMinimized()) window->Restore();
        window->Show(); window->Activate();
      }
    }
    if (history_.current()->action == "gap") { history_.Hide(); pet_.CloseMessage(); return; }
    browser_->GetMainFrame()->ExecuteJavaScript("window.__oaPet&&window.__oaPet.open(" +
      QuoteJavaScript(history_.current()->order) + ");", "", 0);
  }
};
}

}
