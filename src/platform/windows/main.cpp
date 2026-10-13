#include <windows.h>
#include <filesystem>
#include <memory>
#include "include/cef_command_line.h"
#include "include/cef_version_info.h"
#include "include/wrapper/cef_library_loader.h"
#include "include/base/cef_logging.h"
#include "app/app.h"

namespace {

int RunMain(HINSTANCE instance) {
  CefMainArgs args(instance);
  const int child_result = CefExecuteProcess(args, nullptr, nullptr);
  if (child_result >= 0) return child_result;

  const HANDLE mutex = CreateMutexW(nullptr, FALSE, L"Local\\oaClient2.Windows.Profile");
  if (!mutex) { oa::ShowError("Cannot lock the oaClient2 browser profile."); return 1; }
  const DWORD lock_result = WaitForSingleObject(mutex, 0);
  if (lock_result != WAIT_OBJECT_0 && lock_result != WAIT_ABANDONED) {
    CloseHandle(mutex);
    oa::ShowError("oaClient2 is already running. Close it before opening a new instance.");
    return 0;
  }

  auto context = std::make_shared<oa::AppContext>();
  //2026.10.13 modify by codex, opt Windows into the shared welcome, zoom and background logout policies.
  context->settings.home_url.clear();
  context->settings.allow_empty_home_url = true;
  context->hide_zoom_bubble = true;
  context->background_logout_close = true;
  std::string error;
  int result = 1;
  if (oa::GetAppPaths(context->paths, error) &&
      oa::LoadSettings(context->paths.config, context->settings, error)) {
    CefRefPtr<CefCommandLine> command = CefCommandLine::CreateCommandLine();
    command->InitFromString(GetCommandLineW());
    if (command->HasSwitch("url")) context->settings.home_url = command->GetSwitchValue("url").ToString();
    oa::AppendLog(context->paths, "START version=0.1.6");
    if (context->settings.clear_site_data && !oa::ClearBrowserProfile(context->paths, error)) {
      oa::ShowError(error);
    } else {
      oa::AppendLog(context->paths, context->settings.clear_site_data ? "SITE_DATA_CLEARED" : "SITE_DATA_RETAINED_BY_INI");
      CefSettings settings;
      CefString(&settings.root_cache_path) = oa::PathUtf8(context->paths.profile);
      CefString(&settings.cache_path) = oa::PathUtf8(context->paths.profile / L"Default");
      CefString(&settings.locale) = context->settings.locale;
      CefString(&settings.log_file) = oa::PathUtf8(context->paths.data / L"cef.log");
      settings.persist_session_cookies = 0;
      settings.no_sandbox = 1;
      CefString(&settings.resources_dir_path) = oa::PathUtf8(context->paths.application / L"cef");
      CefString(&settings.locales_dir_path) = oa::PathUtf8(context->paths.application / L"cef" / L"locales");
      CefRefPtr<oa::App> app = new oa::App(context);
      if (CefInitialize(args, settings, app, nullptr)) {
        CefRunMessageLoop();
        CefShutdown();
        oa::AppendLog(context->paths, "SHUTDOWN_COMPLETE");
        result = 0;
      } else {
        result = CefGetExitCode();
        oa::AppendLog(context->paths, "INITIALIZE_EXIT code=" + std::to_string(result));
      }
    }
  } else {
    oa::ShowError(error);
  }
  ReleaseMutex(mutex);
  CloseHandle(mutex);
  return result;
}

}  // namespace

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, LPWSTR, int) {
  cef_version_info_t version_info = {};
  CEF_POPULATE_VERSION_INFO(&version_info);
  CefScopedLibraryLoader library_loader;
  {
    cef::logging::ScopedEarlySupport early_logging({});
    if (!library_loader.LoadInSubProcessAssert(&version_info)) {
      std::wstring executable(32768, L'\0');
      const DWORD length = GetModuleFileNameW(nullptr, executable.data(),
        static_cast<DWORD>(executable.size()));
      if (!length || length >= executable.size()) return 1;
      executable.resize(length);
      const auto library = std::filesystem::path(executable).parent_path() / L"cef" / L"libcef.dll";
      if (!library_loader.LoadInMainAssert(library.c_str(), nullptr, true, &version_info)) return 1;
    }
  }
  return RunMain(instance);
}
