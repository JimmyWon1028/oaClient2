#include <sys/stat.h>
#include <sys/xattr.h>
#include <fstream>
#include "common/ini.h"
#include "platform/platform.h"

//2026.10.12 modify by codex, test native metadata, write denial and cleanup boundaries.
void RunPlatformTests(const std::filesystem::path& root, const std::filesystem::path& config,
    oa::IniFile& ini, std::string& error, void (*Check)(bool, const char*)) {
  chmod(config.c_str(), 0600);
  setxattr(config.c_str(), "tw.com.lysm.oaClient2.test", "synthetic", 9, 0, 0);
  Check(oa::SaveUserSetting(config, "userid", "MAC-METADATA", error), "macOS settings replace succeeds");
  struct stat metadata{};
  stat(config.c_str(), &metadata);
  char attribute[32]{};
  Check((metadata.st_mode & 0777) == 0600 &&
    getxattr(config.c_str(), "tw.com.lysm.oaClient2.test", attribute, sizeof(attribute), 0, 0) == 9,
    "macOS replacement preserves permissions and extended attributes");
  Check(ini.Load(config, error) && ini.Get("Custom", "Note") == "a=b|c", "macOS replacement preserves other settings");
  const auto timestamp = std::filesystem::last_write_time(config);
  Check(ini.Save(config, error) && std::filesystem::last_write_time(config) == timestamp,
    "unchanged macOS INI does not rewrite");
  chmod(config.c_str(), 0400);
  Check(ini.Save(config, error), "unchanged read-only macOS INI succeeds");
  Check(!oa::SaveUserSetting(config, "userid", "DENIED", error) && ini.Load(config, error) &&
    ini.Get("UserSet", "userid") == "MAC-METADATA", "macOS write denial retains original settings");
  stat(config.c_str(), &metadata);
  Check((metadata.st_mode & 0777) == 0400, "macOS save does not remove read-only protection");
  chmod(config.c_str(), 0600);
  oa::AppPaths paths;
  //2026.10.12 modify by codex, exercise blank Mac startup and configured URL reload through the shared INI code.
  oa::Settings mac_settings;
  mac_settings.home_url.clear();
  mac_settings.allow_empty_home_url = true;
  const auto mac_config = root / "MacConfig.ini";
  Check(oa::LoadSettings(mac_config, mac_settings, error) && mac_settings.home_url.empty(),
    "first Mac INI creates an empty HomeUrl");
  oa::IniFile mac_ini;
  Check(mac_ini.Load(mac_config, error) && mac_ini.Get("SysSet", "HomeUrl", "missing").empty() &&
    mac_settings.home_url.empty(), "unconfigured navigation does not store a local page or a default website in INI");
  mac_ini.Set("SysSet", "HomePage", "unused-page");
  Check(mac_ini.Save(mac_config, error) && oa::LoadSettings(mac_config, mac_settings, error) && mac_settings.home_url.empty(),
    "Mac HomePage does not turn an empty server URL into a website");
  mac_ini.Set("SysSet", "HomePage", "");
  mac_ini.Set("SysSet", "HomeUrl", "example.test");
  Check(mac_ini.Save(mac_config, error) && oa::LoadSettings(mac_config, mac_settings, error) &&
    mac_settings.home_url == "https://example.test", "configured Mac URL uses the shared hostname normalization");
  oa::Settings restarted;
  restarted.home_url.clear();
  restarted.allow_empty_home_url = true;
  Check(oa::LoadSettings(mac_config, restarted, error) && restarted.home_url == "https://example.test",
    "configured Mac URL survives a fresh settings instance");
  paths.application = root / "Applications";
  paths.data = root;
  paths.profile = root / "browser-profile";
  //2026.10.12 modify by codex, verify Mac pictures and retained runtime files stay outside profile cleanup.
  Check(oa::PictureDirectory(paths) == root / "picture", "Mac screenshot directory follows data root rather than app directory");
  std::filesystem::create_directories(oa::PictureDirectory(paths));
  std::filesystem::create_directories(root / "logs");
  { std::ofstream file(root / "picture" / "keep.jpg"); file << "synthetic-picture"; }
  { std::ofstream file(root / "logs" / "application.log"); file << "synthetic-log"; }
  std::filesystem::create_directories(paths.profile);
  const auto outside = root / "retained";
  std::filesystem::create_directories(outside);
  { std::ofstream file(outside / "keep"); file << "preserved"; }
  std::filesystem::create_directory_symlink(outside, paths.profile / "linked");
  Check(!oa::ClearBrowserProfile(paths, error) && std::filesystem::exists(outside / "keep"),
    "macOS rejects linked profile descendants and preserves outside files");
  std::filesystem::remove(paths.profile / "linked");
  std::filesystem::remove(paths.profile);
  std::filesystem::create_directory_symlink(outside, paths.profile);
  Check(!oa::ClearBrowserProfile(paths, error) && std::filesystem::exists(outside / "keep"),
    "macOS rejects a linked profile root");
  std::filesystem::remove(paths.profile);
  std::filesystem::create_directories(paths.profile);
  std::filesystem::create_symlink(outside / "keep", paths.profile / "SingletonSocket");
  Check(oa::ClearBrowserProfile(paths, error) && std::filesystem::exists(outside / "keep"),
    "macOS removes Chromium root links without touching their targets");
  Check(std::filesystem::exists(config) && std::filesystem::exists(root / "picture" / "keep.jpg") &&
    std::filesystem::exists(root / "logs" / "application.log"), "profile reset preserves sibling settings, screenshots and logs");
  Check(!oa::LaunchReport("Reptool.exe", "synthetic", config, root, error), "Mac reports Windows Reptool as unsupported");
}
