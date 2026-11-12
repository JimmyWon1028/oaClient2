#include <windows.h>
#include <filesystem>
#include <fstream>
#include "common/ini.h"
#include "platform/platform.h"
#include "platform/windows/file_dialog_filter.h"

//2026.10.12 modify by codex, retain Windows-only checks outside the shared test source.
void RunPlatformTests(const std::filesystem::path& root, const std::filesystem::path& config,
    oa::IniFile& ini, std::string& error, void (*Check)(bool, const char*)) {
  std::error_code ec;
  //2026.10.30 by codex, do not silently skip startup encoding repair or remove read-only protection.
  const auto readonly_config = root / "ReadonlyLegacy.ini";
  const std::string readonly_contents = "[UserSet]\nreport_font=標楷體\n";
  { std::ofstream output(readonly_config, std::ios::binary); output << readonly_contents; }
  const auto readonly_attributes = GetFileAttributesW(readonly_config.c_str());
  SetFileAttributesW(readonly_config.c_str(), readonly_attributes | FILE_ATTRIBUTE_READONLY);
  oa::Settings readonly_settings;
  Check(!oa::LoadSettings(readonly_config, readonly_settings, error),
    "startup reports a write-denied legacy encoding repair");
  {
    std::ifstream input(readonly_config, std::ios::binary);
    const std::string remaining((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    Check(remaining == readonly_contents &&
      (GetFileAttributesW(readonly_config.c_str()) & FILE_ATTRIBUTE_READONLY) != 0,
      "failed startup repair preserves original bytes and read-only protection");
  }
  SetFileAttributesW(readonly_config.c_str(), readonly_attributes);
  //2026.10.16 by codex, verify complete expansions and fail closed for unknown or wildcard filters.
  Check(oa::CombinedFilePattern(5, {L".jpg", L".png", L".pdf", L".xls", L".xlsx"}) ==
    L"*.jpg;*.png;*.pdf;*.xls;*.xlsx", "file dialog combines every accepted extension");
  Check(oa::CombinedFilePattern(3, {L".png;.jpg;.png", L".pdf", L".xlsx"}) ==
    L"*.png;*.jpg;*.pdf;*.xlsx", "file dialog combines MIME expansion and deduplicates");
  Check(oa::CombinedFilePattern(1, {L".png"}) == L"*.png", "PNG input retains its own restriction");
  Check(oa::CombinedFilePattern(0, {}).empty(), "unrestricted input stays with CEF");
  Check(oa::CombinedFilePattern(2, {L".png"}).empty(), "incomplete expansion defers to CEF");
  Check(oa::CombinedFilePattern(2, {L".png", L""}).empty(), "unknown MIME cannot broaden custom files");
  Check(oa::CombinedFilePattern(1, {L".png;*.*"}).empty(), "wildcards cannot silently broaden custom files");
  Check(oa::CombinedFilePattern(1, {L".png;"}).empty(), "empty expanded suffix cannot broaden custom files");
  //2026.10.13 modify by codex, verify the Windows entry policy preserves blank and existing server settings.
  oa::Settings startup;
  startup.home_url.clear();
  startup.allow_empty_home_url = true;
  const auto startup_config = root / "WindowsStartup.ini";
  oa::IniFile startup_ini;
  Check(oa::LoadSettings(startup_config, startup, error) && startup.home_url.empty(),
    "first Windows INI keeps an unconfigured HomeUrl empty");
  Check(startup_ini.Load(startup_config, error) && startup_ini.Get("SysSet", "HomeUrl", "missing").empty(),
    "Windows welcome navigation does not persist a local data URL");
  startup_ini.Set("SysSet", "HomePage", "unused-page");
  Check(startup_ini.Save(startup_config, error) && oa::LoadSettings(startup_config, startup, error) &&
    startup.home_url.empty(), "Windows HomePage preserves an unconfigured server URL");
  startup_ini.Set("SysSet", "HomePage", "");
  startup_ini.Set("SysSet", "HomeUrl", "example.test");
  Check(startup_ini.Save(startup_config, error) && oa::LoadSettings(startup_config, startup, error) &&
    startup.home_url == "https://example.test", "Windows existing hostname uses shared URL normalization");
  oa::Settings restarted;
  restarted.home_url.clear();
  restarted.allow_empty_home_url = true;
  Check(oa::LoadSettings(startup_config, restarted, error) && restarted.home_url == "https://example.test",
    "Windows existing personal URL survives a fresh settings instance");
  wchar_t executable_path[32768]{};
  GetModuleFileNameW(nullptr, executable_path, 32768);
  const auto receiver = std::filesystem::path(executable_path).parent_path() / "oaClient2_report_receiver.exe";
  const auto report_dir = root / "prg";
  std::filesystem::create_directories(report_dir, ec);
  const auto report_exe = report_dir / "Reptool.exe";
  std::filesystem::copy_file(receiver, report_exe, ec);
  const std::string report_parameters = "cmd=prt|fn=合成報表|text=\"quoted\"|path=C:\\trailing\\";
  Check(!ec && oa::LaunchReport(oa::PathUtf8(report_exe), report_parameters, config, root, error),
    "report launcher starts synthetic receiver through Windows shell");
  const auto received_path = root / "received-report.txt";
  for (int i = 0; i < 200 && !std::filesystem::exists(received_path); ++i) Sleep(10);
  // The receiver publishes the file after writing all arguments.
  std::string received_parameters, received_config, received_directory;
  for (int i = 0; i < 100; ++i) {
    std::ifstream input(received_path, std::ios::binary);
    if (std::getline(input, received_parameters) && std::getline(input, received_config) &&
        std::getline(input, received_directory)) break;
    Sleep(10);
  }
  Check(received_parameters == report_parameters && received_config == oa::PathUtf8(config),
    "Reptool receives exactly two Unicode arguments including quotes and trailing backslash");
  Check(oa::Utf8Path(received_directory) == root, "Reptool working directory is the main application directory");
  HANDLE reader = CreateFileW(config.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
  Check(reader != INVALID_HANDLE_VALUE, "reader holds INI without allowing deletion");
  BY_HANDLE_FILE_INFORMATION before{}, after{};
  GetFileInformationByHandle(reader, &before);
  Check(ini.Load(config, error) && ini.Save(config, error), "unchanged INI succeeds while replacement is blocked");
  Check(oa::SaveUserSetting(config, "userid", "SYNC-LOCK-TEST", error),
    "changed INI saves when deletion is blocked but writing is allowed");
  GetFileInformationByHandle(reader, &after);
  Check(before.nFileIndexHigh == after.nFileIndexHigh && before.nFileIndexLow == after.nFileIndexLow,
    "in-place fallback retains existing file identity");
  Check(ini.Load(config, error) && ini.Get("UserSet", "userid") == "SYNC-LOCK-TEST" &&
    ini.Get("Custom", "Note") == "a=b|c" && ini.GetInt("UserSet", "ZoomPercent", 0) == 125,
    "fallback preserves other user settings and complete new value");
  Check(oa::SaveUserSetting(config, "userid", "S", error) && ini.Load(config, error) &&
    ini.Get("UserSet", "userid") == "S", "shorter fallback save truncates previous tail correctly");
  CloseHandle(reader);
  const auto original_attributes = GetFileAttributesW(config.c_str());
  SetFileAttributesW(config.c_str(), original_attributes | FILE_ATTRIBUTE_READONLY);
  Check(ini.Save(config, error), "unchanged read-only INI does not need replacement");
  Check(!oa::SaveUserSetting(config, "userid", "DENIED", error) &&
    ini.Load(config, error) && ini.Get("UserSet", "userid") == "S",
    "genuine write denial preserves original contents and reports failure");
  Check((GetFileAttributesW(config.c_str()) & FILE_ATTRIBUTE_READONLY) != 0,
    "save does not remove read-only protection");
  SetFileAttributesW(config.c_str(), original_attributes);
}
