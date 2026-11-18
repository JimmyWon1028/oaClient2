#include "app/pet_renderer.h"
#include "include/cef_v8.h"
#include "include/cef_frame.h"
#include "include/cef_process_message.h"

namespace oa {
namespace {
//2026.11.17 by codex, carry notification grants over CEF IPC without console commands or a loopback server.
class PetBridge : public CefV8Handler {
 public:
  bool Execute(const CefString&, CefRefPtr<CefV8Value>, const CefV8ValueList& arguments,
      CefRefPtr<CefV8Value>& result, CefString&) override {
    auto context = CefV8Context::GetCurrentContext();
    if (!context || arguments.size() != 1 || !arguments[0]->IsString()) return false;
    auto browser = context->GetBrowser();
    auto frame = context->GetFrame();
    if (!frame || !frame->IsMain() || browser->IsPopup()) return false;
    const auto data = arguments[0]->GetStringValue();
    if (data.length() > 65536) return false;
    auto message = CefProcessMessage::Create("oa.pet");
    message->GetArgumentList()->SetString(0, data);
    frame->SendProcessMessage(PID_BROWSER, message);
    result = CefV8Value::CreateUndefined();
    return true;
  }
 private:
  IMPLEMENT_REFCOUNTING(PetBridge);
};

class PetRenderer : public CefApp, public CefRenderProcessHandler {
 public:
  CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return this; }
  void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
      CefRefPtr<CefV8Context> context) override {
    if (!frame->IsMain() || browser->IsPopup()) return;
    context->GetGlobal()->SetValue("oaPetSend", CefV8Value::CreateFunction("oaPetSend", new PetBridge),
      static_cast<cef_v8_propertyattribute_t>(V8_PROPERTY_ATTRIBUTE_READONLY | V8_PROPERTY_ATTRIBUTE_DONTDELETE));
  }
 private:
  IMPLEMENT_REFCOUNTING(PetRenderer);
};
}
CefRefPtr<CefApp> CreatePetRenderer() { return new PetRenderer; }
}
