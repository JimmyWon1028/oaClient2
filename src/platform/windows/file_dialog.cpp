#include <windows.h>
#include <shobjidl.h>
#include <wrl/client.h>
#include <atomic>
#include <memory>
#include <thread>
#include "platform/cef_platform.h"
#include "platform/windows/file_dialog_filter.h"
#include "include/base/cef_logging.h"
#include "include/base/cef_callback.h"
#include "include/base/cef_bind.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

namespace oa {
namespace {

using Microsoft::WRL::ComPtr;

//2026.10.16 by codex, keep COM and its modal loop on an owned STA instead of blocking the CEF UI.
struct FileDialogJob {
  HWND owner = nullptr;
  int browser_id = 0;
  std::atomic<HWND> dialog_window{nullptr};
  bool multiple = false;
  std::wstring title;
  std::wstring initial;
  std::wstring pattern;
  std::atomic<bool> cancel{false};
  std::atomic<bool> done{false};
  std::vector<std::wstring> paths;
  HRESULT result = E_FAIL;
  CefRefPtr<CefFileDialogCallback> callback;
  IFileOpenDialog* active = nullptr;
  std::thread worker;
};

std::vector<std::shared_ptr<FileDialogJob>> jobs;
thread_local FileDialogJob* current_job = nullptr;

//2026.10.16 by codex, expose only the native close message across threads and keep COM on its STA.
class DialogEvents : public IFileDialogEvents {
 public:
  explicit DialogEvents(FileDialogJob& job) : job_(job) {}
  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** output) override {
    if (!output) return E_POINTER;
    *output = nullptr;
    if (iid != IID_IUnknown && iid != IID_IFileDialogEvents) return E_NOINTERFACE;
    *output = static_cast<IFileDialogEvents*>(this);
    AddRef();
    return S_OK;
  }
  ULONG STDMETHODCALLTYPE AddRef() override { return ++references_; }
  ULONG STDMETHODCALLTYPE Release() override {
    const auto remaining = --references_;
    if (!remaining) delete this;
    return remaining;
  }
  HRESULT STDMETHODCALLTYPE OnFolderChange(IFileDialog* dialog) override {
    ComPtr<IOleWindow> window;
    HWND handle = nullptr;
    if (SUCCEEDED(dialog->QueryInterface(IID_PPV_ARGS(&window))) && SUCCEEDED(window->GetWindow(&handle))) {
      job_.dialog_window = handle;
      if (job_.cancel.load()) PostMessageW(handle, WM_CLOSE, 0, 0);
    }
    return S_OK;
  }
  HRESULT STDMETHODCALLTYPE OnFileOk(IFileDialog*) override { return S_OK; }
  HRESULT STDMETHODCALLTYPE OnFolderChanging(IFileDialog*, IShellItem*) override { return S_OK; }
  HRESULT STDMETHODCALLTYPE OnSelectionChange(IFileDialog*) override { return S_OK; }
  HRESULT STDMETHODCALLTYPE OnTypeChange(IFileDialog*) override { return S_OK; }
  HRESULT STDMETHODCALLTYPE OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE* response) override {
    *response = FDESVR_DEFAULT;
    return S_OK;
  }
  HRESULT STDMETHODCALLTYPE OnOverwrite(IFileDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE* response) override {
    *response = FDEOR_DEFAULT;
    return S_OK;
  }
 private:
  std::atomic<ULONG> references_{1};
  FileDialogJob& job_;
};

void CancelJob(const std::shared_ptr<FileDialogJob>& job) {
  job->cancel = true;
  if (const auto window = job->dialog_window.load()) PostMessageW(window, WM_CLOSE, 0, 0);
}

void CALLBACK CheckOwner(HWND, UINT, UINT_PTR, DWORD) {
  if (current_job && current_job->active && (current_job->cancel.load() ||
      !IsWindow(current_job->owner) || !IsWindowVisible(current_job->owner))) {
    current_job->active->Close(HRESULT_FROM_WIN32(ERROR_CANCELLED));
  }
}

void RunDialog(FileDialogJob& job) {
  ComPtr<IFileOpenDialog> dialog;
  job.result = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER,
    IID_PPV_ARGS(&dialog));
  if (FAILED(job.result)) return;
  ComPtr<IFileDialogEvents> events;
  events.Attach(new DialogEvents(job));
  DWORD event_cookie = 0;
  job.result = dialog->Advise(events.Get(), &event_cookie);
  if (FAILED(job.result)) return;
  FILEOPENDIALOGOPTIONS options{};
  job.result = dialog->GetOptions(&options);
  if (FAILED(job.result)) return;
  options |= FOS_FORCEFILESYSTEM | FOS_FILEMUSTEXIST | FOS_PATHMUSTEXIST | FOS_NOCHANGEDIR;
  if (job.multiple) options |= FOS_ALLOWMULTISELECT;
  else options &= ~FOS_ALLOWMULTISELECT;
  const COMDLG_FILTERSPEC filters[] = {{L"Custom Files", job.pattern.c_str()}, {L"All Files", L"*.*"}};
  job.result = dialog->SetOptions(options);
  if (SUCCEEDED(job.result)) job.result = dialog->SetFileTypes(2, filters);
  if (SUCCEEDED(job.result)) job.result = dialog->SetFileTypeIndex(1);
  if (SUCCEEDED(job.result) && !job.title.empty()) job.result = dialog->SetTitle(job.title.c_str());
  if (FAILED(job.result)) return;
  if (!job.initial.empty()) {
    const std::filesystem::path initial(job.initial);
    std::error_code error;
    const bool directory = std::filesystem::is_directory(initial, error);
    const auto folder = directory ? initial : initial.parent_path();
    ComPtr<IShellItem> item;
    if (!folder.empty() && SUCCEEDED(SHCreateItemFromParsingName(folder.c_str(), nullptr, IID_PPV_ARGS(&item)))) {
      dialog->SetFolder(item.Get());
    }
    if (!directory && !initial.filename().empty()) dialog->SetFileName(initial.filename().c_str());
  }
  current_job = &job;
  job.active = dialog.Get();
  const auto timer = SetTimer(nullptr, 0, 50, CheckOwner);
  if (timer && !job.cancel.load() && IsWindow(job.owner) && IsWindowVisible(job.owner)) {
    job.result = dialog->Show(job.owner);
  } else {
    job.result = HRESULT_FROM_WIN32(ERROR_CANCELLED);
  }
  if (timer) KillTimer(nullptr, timer);
  job.active = nullptr;
  job.dialog_window = nullptr;
  dialog->Unadvise(event_cookie);
  current_job = nullptr;
  if (FAILED(job.result) || job.cancel.load()) return;
  ComPtr<IShellItemArray> items;
  job.result = dialog->GetResults(&items);
  DWORD count = 0;
  if (SUCCEEDED(job.result)) job.result = items->GetCount(&count);
  for (DWORD index = 0; SUCCEEDED(job.result) && index < count; ++index) {
    ComPtr<IShellItem> item;
    job.result = items->GetItemAt(index, &item);
    PWSTR path = nullptr;
    if (SUCCEEDED(job.result)) job.result = item->GetDisplayName(SIGDN_FILESYSPATH, &path);
    if (SUCCEEDED(job.result)) job.paths.emplace_back(path);
    CoTaskMemFree(path);
  }
  if (FAILED(job.result)) job.paths.clear();
}

//2026.10.16 by codex, complete once on the CEF UI thread and never post from a late worker.
void PollDialog(std::shared_ptr<FileDialogJob> job, CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFileDialogCallback> callback) {
  CEF_REQUIRE_UI_THREAD();
  if (job->cancel.load() || !browser->IsValid() || !IsWindow(job->owner) || !IsWindowVisible(job->owner)) CancelJob(job);
  if (!job->done.load()) {
    CefPostDelayedTask(TID_UI, base::BindOnce(PollDialog, job, browser, callback), 25);
    return;
  }
  if (job->worker.joinable()) job->worker.join();
  std::erase(jobs, job);
  job->callback = nullptr;
  if (job->cancel.load() || !browser->IsValid() || FAILED(job->result) || job->paths.empty()) {
    LOG(INFO) << "W31_FILE_DIALOG_CANCEL result=" << job->result;
    callback->Cancel();
    return;
  }
  std::vector<CefString> paths;
  for (const auto& path : job->paths) paths.emplace_back(path);
  LOG(INFO) << "W31_FILE_DIALOG_COMPLETE count=" << paths.size();
  callback->Continue(paths);
}

class WindowsFileDialogHandler : public CefDialogHandler {
 public:
  bool OnFileDialog(CefRefPtr<CefBrowser> browser, FileDialogMode mode,
      const CefString& title, const CefString& initial, const std::vector<CefString>& filters,
      const std::vector<CefString>& extensions, const std::vector<CefString>&,
      CefRefPtr<CefFileDialogCallback> callback) override {
    CEF_REQUIRE_UI_THREAD();
    if ((mode != FILE_DIALOG_OPEN && mode != FILE_DIALOG_OPEN_MULTIPLE) || filters.empty()) return false;
    std::vector<std::wstring> expanded;
    for (const auto& extension : extensions) expanded.push_back(extension.ToWString());
    const auto pattern = CombinedFilePattern(filters.size(), expanded);
    //2026.10.16 by codex, defer unresolved MIME types and unsupported filters to CEF.
    if (pattern.empty()) return false;
    const HWND owner = GetAncestor(browser->GetHost()->GetWindowHandle(), GA_ROOT);
    if (!owner || !IsWindow(owner) || !IsWindowVisible(owner)) return false;
    auto job = std::make_shared<FileDialogJob>();
    job->owner = owner;
    job->browser_id = browser->GetIdentifier();
    job->multiple = mode == FILE_DIALOG_OPEN_MULTIPLE;
    job->title = title.ToWString();
    job->initial = initial.ToWString();
    job->pattern = pattern;
    job->callback = callback;
    try {
      jobs.push_back(job);
      job->worker = std::thread([job] {
        const HRESULT initialized = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        if (SUCCEEDED(initialized)) {
          try { RunDialog(*job); } catch (...) { job->result = E_FAIL; job->paths.clear(); }
          CoUninitialize();
        } else {
          job->result = initialized;
        }
        job->done = true;
      });
    } catch (...) {
      std::erase(jobs, job);
      return false;
    }
    LOG(INFO) << "W31_FILE_DIALOG_CUSTOM mode=" << mode << " pattern=" << CefString(pattern).ToString();
    PollDialog(job, browser, callback);
    return true;
  }

 private:
  IMPLEMENT_REFCOUNTING(WindowsFileDialogHandler);
};

}

CefRefPtr<CefDialogHandler> PlatformFileDialogHandler() { return new WindowsFileDialogHandler; }

void ShutdownPlatformFileDialogs() {
  for (const auto& job : jobs) {
    CancelJob(job);
    if (job->callback) job->callback->Cancel();
    job->callback = nullptr;
  }
  for (const auto& job : jobs) if (job->worker.joinable()) job->worker.join();
  jobs.clear();
}

void CancelPlatformFileDialogs(int browser_id) {
  for (const auto& job : jobs) if (job->browser_id == browser_id) CancelJob(job);
}

}
