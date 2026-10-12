#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <utility>

namespace oa {

class IniFile {
 public:
  bool Load(const std::filesystem::path& path, std::string& error);
  bool Save(const std::filesystem::path& path, std::string& error) const;
  std::string Get(const std::string& section, const std::string& key,
                  const std::string& fallback = "") const;
  int GetInt(const std::string& section, const std::string& key, int fallback) const;
  bool GetBool(const std::string& section, const std::string& key, bool fallback) const;
  void Set(const std::string& section, const std::string& key, const std::string& value);
  std::vector<std::pair<std::string, std::string>> SectionValues(const std::string& section) const;

 private:
  std::vector<std::string> lines_;
};

struct Settings {
  std::string home_url = "https://oa.lysm.com.tw/";
  //2026.10.12 modify by codex, allow the Mac entry to keep an unconfigured URL without changing Windows defaults.
  bool allow_empty_home_url = false;
  std::string locale = "zh-TW";
  std::string reptool_path;
  std::string reptool_config;
  bool clear_site_data = true;
  int width = 1200;
  int height = 850;
  int left = -1;
  int top = -1;
  bool maximized = false;
  int zoom_percent = 100;
};

bool LoadSettings(const std::filesystem::path& path, Settings& settings,
                  std::string& error);
bool SaveWindowSettings(const std::filesystem::path& path, int x, int y,
                        int width, int height, bool maximized, std::string& error);
std::string GetCommandField(const std::string& command, const std::string& key);
std::string QuoteJavaScript(const std::string& value);
bool SaveUserSetting(const std::filesystem::path& path, const std::string& key,
                      const std::string& value, std::string& error);
std::string UserSettingsScript(const IniFile& ini);
std::string SerializedUserSettings(const IniFile& ini);
std::string EncodeCookieValue(const std::string& value);
bool IsLegacyOpenProtocol(const std::string& url);
std::filesystem::path ResolveApplicationPath(const std::filesystem::path& application,
                                            const std::string& value);

}  // namespace oa
