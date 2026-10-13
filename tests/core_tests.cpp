#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "common/ini.h"
#include "common/logout.h"
#include "common/keyboard.h"
#include "platform/platform.h"

//2026.10.12 modify by codex, reuse shared cases and delegate native-only checks.
void RunPlatformTests(const std::filesystem::path&, const std::filesystem::path&,
    oa::IniFile&, std::string&, void (*)(bool, const char*));

namespace {
int failures = 0;
int checks = 0;
void Check(bool condition, const char* label) {
  ++checks;
  std::cout << (condition ? "PASS " : "FAIL ") << label << '\n';
  if (!condition) ++failures;
}
}

int main() {
  //2026.10.13 modify by codex, verify the exact browser shortcut policy and preserve unrelated combinations.
  for (int key : {0x70, 0x71, 0x72, 0x73, 0x78}) {
    Check(oa::IsWebsiteShortcut(key, false, false, false, false), "requested plain function key belongs to website");
    Check(!oa::IsWebsiteShortcut(key, true, false, false, false), "modified function key is not added to policy");
  }
  for (int key : {'F', 'E', 'S', 'N'}) {
    Check(oa::IsWebsiteShortcut(key, false, true, false, false), "Ctrl website shortcut matches");
    Check(oa::IsWebsiteShortcut(key, false, false, false, true), "Command website shortcut matches");
    Check(!oa::IsWebsiteShortcut(key, true, true, false, false), "Ctrl Shift variant remains unchanged");
  }
  Check(oa::IsWebsiteShortcut('W', false, false, true, false), "Alt W belongs to website");
  Check(oa::IsWebsiteShortcut('F', true, false, false, false), "Shift F belongs to website");
  Check(!oa::IsWebsiteShortcut('W', false, true, false, false), "Ctrl W remains unchanged");
  //2026.10.13 modify by codex, reserve only Windows Ctrl W and preserve all other close chords.
  Check(oa::IsWebsiteShortcut('W', false, true, false, false, true), "Windows Ctrl W belongs to website");
  Check(!oa::IsWebsiteShortcut('W', false, false, false, true, true), "Command W remains unchanged");
  Check(!oa::IsWebsiteShortcut('W', true, true, false, false, true), "Ctrl Shift W remains unchanged");
  Check(!oa::IsWebsiteShortcut('W', false, true, true, false, true), "Ctrl Alt W remains unchanged");
  Check(!oa::IsWebsiteShortcut('W', false, true, false, true, true), "mixed Ctrl Command W remains unchanged");
  for (int key : {'P', 'C', 'V', 'A', 'L'}) {
    Check(!oa::IsWebsiteShortcut(key, false, true, false, false), "unlisted Ctrl combination remains unchanged");
  }
  for (int key : {0x74, 0x77, 0x7B}) {
    Check(!oa::IsWebsiteShortcut(key, false, false, false, false), "reload and existing app keys remain unchanged");
  }
  Check(!oa::IsWebsiteShortcut('F', false, false, false, false), "plain typing remains unchanged");
  Check(!oa::IsWebsiteShortcut('E', false, true, true, false), "Ctrl Alt variant remains unchanged");
  Check(!oa::IsWebsiteShortcut('N', false, true, false, true), "mixed Ctrl Command is not a requested chord");
  const auto temporary = std::filesystem::canonical(std::filesystem::temp_directory_path());
  const auto root = temporary / ("oaClient2-core-tests-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
  std::error_code ec;
  std::filesystem::create_directories(root, ec);
  if (ec) return 2;
  const auto config = root / "Config.ini";
  std::string error;
  oa::Settings settings;
  Check(oa::LoadSettings(config, settings, error), "first launch creates INI");
  Check(settings.clear_site_data, "clear all website data defaults to enabled");
  Check(settings.home_url == "https://oa.lysm.com.tw/", "default OA URL");
  Check(settings.zoom_percent == 100, "default zoom is 100 percent");
  {
    std::ofstream output(config, std::ios::binary);
    output << "\xef\xbb\xbf; keep this comment\r\n[sysset]\r\nHomeUrl=example.test\r\n"
              "ClearCache=N\r\nReptoolPath=C:\\報表\\Reptool.exe\r\n[Custom]\r\nNote=a=b|c\r\n"
              "[UserSet]\r\nZoomPercent=125\r\n[Window]\r\nWidth=bad\r\nHeight=200\r\nMaximized=YES\r\n";
  }
  Check(oa::LoadSettings(config, settings, error), "UTF-8 BOM and CRLF INI loads");
  Check(settings.home_url == "https://example.test", "hostname receives HTTPS scheme");
  Check(!settings.clear_site_data, "manual INI clear option applies");
  Check(settings.width == 1200 && settings.height == 480, "invalid dimensions fall back or clamp");
  Check(settings.maximized, "case insensitive boolean settings");
  Check(settings.reptool_path == "C:\\報表\\Reptool.exe", "Unicode path preserved");
  Check(settings.zoom_percent == 125, "manual INI zoom percentage loads");
  Check(oa::SaveWindowSettings(config, 10, 20, 1000, 700, false, error), "window settings save");
  oa::IniFile ini;
  Check(ini.Load(config, error), "saved INI reloads");
  Check(ini.Get("Custom", "Note") == "a=b|c", "unknown settings preserved");
  Check(ini.Get("SysSet", "HomeUrl") == "example.test", "manual URL is not replaced by window save");
  Check(ini.GetInt("UserSet", "ZoomPercent", 0) == 125, "window save preserves zoom preference");
  Check(ini.GetInt("Window", "Left", 0) == 10, "window position saved");
  Check(ini.GetBool("Window", "Maximized", true) == false, "window state saved");
  {
    std::ifstream input(config, std::ios::binary);
    std::string text((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    Check(text.find("; keep this comment") != std::string::npos, "INI comments preserved");
  }
  const std::string command = "cmd=prt|fn=report|button=printButton|value=a=b";
  Check(oa::GetCommandField(command, "CMD") == "prt", "legacy command parsing is case insensitive");
  Check(oa::GetCommandField(command, "value") == "a=b", "equals in parameter values retained");
  Check(oa::QuoteJavaScript("a'\\\nb") == "'a\\'\\\\\\x0ab'", "JavaScript string data escaped");
  Check(oa::SaveUserSetting(config, "userid", "SYNTHETIC-USER", error), "legacy userid preference saves");
  Check(oa::SaveUserSetting(config, "last_select_database", "測試公司", error), "company preference saves");
  Check(oa::SaveUserSetting(config, "future_Preference", "a=b'\\中文", error), "arbitrary preference and special characters save");
  Check(ini.Load(config, error) && ini.Get("UserSet", "userid") == "SYNTHETIC-USER", "userid survives INI reload");
  const auto serialized = oa::SerializedUserSettings(ini);
  Check(serialized.find("last_select_database=測試公司") != std::string::npos &&
    serialized.find("future_Preference=a=b'\\中文") != std::string::npos, "legacy serialization preserves key case and equals in values");
  const auto user_script = oa::UserSettingsScript(ini);
  Check(user_script.find("$usr['future_Preference']='a=b\\'\\\\中文';") != std::string::npos,
    "web restore escapes preference data without changing key case");
  Check(oa::SaveUserSetting(config, "userid", "", error) && ini.Load(config, error) &&
    ini.Get("UserSet", "userid", "missing").empty(), "empty preference overwrites previous userid");
  Check(oa::SerializedUserSettings(ini).find("userid=|") != std::string::npos &&
    oa::UserSettingsScript(ini).find("$usr['userid']") == std::string::npos, "empty serialization and legacy empty-value restore behavior");
  Check(!oa::SaveUserSetting(config, "bad\n[SysSet]", "value", error) &&
    !oa::SaveUserSetting(config, "userid", "value\nHomeUrl=bad", error), "malformed preference cannot add INI lines");
  Check(ini.Load(config, error) && ini.Get("Custom", "Note") == "a=b|c" &&
    ini.Get("SysSet", "HomeUrl") == "example.test" && ini.GetInt("UserSet", "ZoomPercent", 0) == 125,
    "saving preferences preserves other sections and zoom");
  Check(oa::EncodeCookieValue("測試;= %") == "%E6%B8%AC%E8%A9%A6%3B%3D%20%25", "preference cookies use UTF-8 percent encoding");
  Check(oa::IsLegacyOpenProtocol("hcopen:///C:/file%20name.xlsx") &&
    oa::IsLegacyOpenProtocol("HCOPEN:///file") && oa::IsLegacyOpenProtocol("otheropen:///file"),
    "legacy open-suffix protocols accepted case insensitively");
  Check(!oa::IsLegacyOpenProtocol("open:///file") && !oa::IsLegacyOpenProtocol("https://host/hcopen") &&
    !oa::IsLegacyOpenProtocol("hcopen") && !oa::IsLegacyOpenProtocol("mailto:user@example.test"),
    "other protocols follow legacy refusal rule");
  Check(oa::ResolveApplicationPath(root, "prg/Reptool.exe") == root / "prg" / "Reptool.exe" &&
    oa::ResolveApplicationPath(root, oa::PathUtf8(config)) == config, "Reptool paths resolve against application directory");
  using Action = oa::LogoutFlow::Action;
  oa::LogoutFlow not_ready;
  Check(not_ready.Begin(false) == Action::Close, "not-ready browser closes without logout");
  oa::LogoutFlow already_out;
  already_out.Begin(true); already_out.ReceiveState(0);
  Check(already_out.Tick() == Action::Close && !already_out.logout_sent(), "logged-out page is not logged out again");
  oa::LogoutFlow logged_in;
  Check(logged_in.Begin(true) == Action::Probe && logged_in.Begin(true) == Action::Wait,
    "repeated close does not start parallel logout");
  logged_in.ReceiveState(1);
  Check(logged_in.Tick() == Action::Logout && logged_in.Tick() == Action::Probe, "logged-in page sends logout once then polls");
  logged_in.ReceiveState(0);
  Check(logged_in.Tick() == Action::Close && !logged_in.timed_out(), "logout acknowledgement permits close");
  oa::LogoutFlow unknown;
  unknown.Begin(true);
  Check(unknown.Tick() == Action::Close && !unknown.logout_sent(), "missing login-state function does not block close");
  oa::LogoutFlow timeout;
  timeout.Begin(true); timeout.ReceiveState(1); timeout.Tick();
  for (int i = 0; i < 19; ++i) timeout.Tick();
  Check(!timeout.complete() && timeout.Tick() == Action::Close && timeout.timed_out(), "logout wait is bounded to twenty polls");
  //2026.10.12 modify by codex, verify early acknowledgement, a fixed deadline and repeated-close behavior.
  using Clock = oa::LogoutFlow::Clock;
  const auto start = Clock::time_point{};
  oa::LogoutFlow background;
  Check(background.Begin(true, oa::LogoutFlow::Mode::BackgroundGrace, start) == Action::Logout,
    "background close dispatches logout immediately");
  Check(background.Begin(true, oa::LogoutFlow::Mode::BackgroundGrace, start + std::chrono::seconds(2)) == Action::Wait,
    "repeated background close does not resend logout or reset its deadline");
  Check(background.Tick(start + std::chrono::milliseconds(2999)) == Action::Probe && !background.complete(),
    "missing logout acknowledgement keeps background close alive before three seconds");
  Check(background.Tick(start + std::chrono::seconds(3)) == Action::Close && background.timed_out(),
    "background close completes at three seconds without an acknowledgement");
  oa::LogoutFlow early;
  early.Begin(true, oa::LogoutFlow::Mode::BackgroundGrace, start);
  early.ReceiveState(1);
  Check(!early.complete() && early.Tick(start + std::chrono::milliseconds(500)) == Action::Probe,
    "logged-in state does not prematurely finish background close");
  early.ReceiveState(0);
  Check(early.complete() && early.Tick(start + std::chrono::milliseconds(600)) == Action::Close && !early.timed_out(),
    "logout acknowledgement completes background close immediately before the deadline");
  oa::LogoutFlow unready_background;
  Check(unready_background.Begin(false, oa::LogoutFlow::Mode::BackgroundGrace, start) == Action::Logout &&
    unready_background.Tick(start + std::chrono::seconds(3)) == Action::Close,
    "an unready background page still has a bounded three-second close");
  RunPlatformTests(root, config, ini, error, Check);
  oa::AppPaths paths;
  paths.data = root;
  paths.profile = root / "browser-profile";
  std::filesystem::create_directories(paths.profile / "Default", ec);
  { std::ofstream output(paths.profile / "Default" / "Cookies"); output << "synthetic"; }
  Check(oa::ClearBrowserProfile(paths, error), "dedicated profile reset succeeds");
  Check(!std::filesystem::exists(paths.profile), "website profile completely removed");
  Check(std::filesystem::exists(config), "profile reset preserves Config.ini");
  Check(oa::ClearBrowserProfile(paths, error), "missing profile reset succeeds");
  paths.profile = root / "outside";
  std::filesystem::create_directories(paths.profile, ec);
  Check(!oa::ClearBrowserProfile(paths, error), "wrong cleanup target rejected");
  Check(std::filesystem::exists(paths.profile), "rejected target remains untouched");
  {
    std::ofstream output(config, std::ios::binary | std::ios::trunc);
    output.write("\xff\xfe[\0S\0]", 7);
  }
  Check(!ini.Load(config, error), "UTF-16 INI gives explicit format error");
  if (root.is_absolute() && root.parent_path() == temporary &&
      root.filename().wstring().starts_with(L"oaClient2-core-tests-")) {
    std::filesystem::remove_all(root, ec);
  }
  std::cout << checks << " checks, " << failures << " failures\n";
  return failures ? 1 : 0;
}
