#include "common/ini.h"

#include <algorithm>
#include <charconv>
#include <cctype>
#include <fstream>
#include <iterator>
#include "platform/platform.h"

namespace oa {
namespace {

std::string Trim(const std::string& value) {
  const auto begin = value.find_first_not_of(" \t\r\n");
  if (begin == std::string::npos) return {};
  return value.substr(begin, value.find_last_not_of(" \t\r\n") - begin + 1);
}

std::string Lower(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return value;
}

bool Section(const std::string& line, std::string& section) {
  const std::string text = Trim(line);
  if (text.size() >= 2 && text.front() == '[' && text.back() == ']') {
    section = Lower(Trim(text.substr(1, text.size() - 2)));
    return true;
  }
  return false;
}

bool Pair(const std::string& line, std::string& key, std::string& value) {
  const std::string text = Trim(line);
  if (text.empty() || text.front() == ';' || text.front() == '#') return false;
  const auto equal = text.find('=');
  if (equal == std::string::npos) return false;
  key = Lower(Trim(text.substr(0, equal)));
  value = Trim(text.substr(equal + 1));
  return !key.empty();
}

}  // namespace

bool IniFile::Load(const std::filesystem::path& path, std::string& error) {
  lines_.clear();
  std::ifstream input(path, std::ios::binary);
  if (!input) {
    error = "Cannot read Config.ini.";
    return false;
  }
  std::string line;
  while (std::getline(input, line)) {
    if (lines_.empty() && line.starts_with("\xef\xbb\xbf")) line.erase(0, 3);
    if (!line.empty() && line.back() == '\r') line.pop_back();
    if (line.find('\0') != std::string::npos) {
      error = "Config.ini must be UTF-8, not UTF-16. Save it as UTF-8.";
      return false;
    }
    lines_.push_back(line);
  }
  if (input.bad()) {
    error = "Error while reading Config.ini.";
    return false;
  }
  return true;
}

bool IniFile::Save(const std::filesystem::path& path, std::string& error) const {
  std::string contents;
  for (const auto& line : lines_) contents += line + '\n';
  // Close this read handle before committing; CRT readers do not share deletion.
  {
    std::ifstream current(path, std::ios::binary);
    if (current) {
      const std::string existing((std::istreambuf_iterator<char>(current)), std::istreambuf_iterator<char>());
      if (!current.bad() && existing == contents) return true;
    }
  }
  auto temporary = path;
  temporary += ".tmp";
  {
    std::ofstream output(temporary, std::ios::binary | std::ios::trunc);
    if (!output) { error = "Cannot write Config.ini.tmp."; return false; }
    output.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    output.flush();
    if (!output) { error = "Cannot finish writing Config.ini.tmp."; return false; }
  }
  return CommitSettingsFile(temporary, path, error);
}

std::string IniFile::Get(const std::string& section, const std::string& key,
                         const std::string& fallback) const {
  std::string current, candidate, value;
  for (const auto& line : lines_) {
    if (Section(line, current)) continue;
    if (current == Lower(section) && Pair(line, candidate, value) && candidate == Lower(key)) {
      return value;
    }
  }
  return fallback;
}

int IniFile::GetInt(const std::string& section, const std::string& key, int fallback) const {
  const auto text = Get(section, key);
  int value = 0;
  const auto result = std::from_chars(text.data(), text.data() + text.size(), value);
  return result.ec == std::errc() && result.ptr == text.data() + text.size() ? value : fallback;
}

bool IniFile::GetBool(const std::string& section, const std::string& key, bool fallback) const {
  const auto value = Lower(Get(section, key));
  if (value == "y" || value == "yes" || value == "true" || value == "1") return true;
  if (value == "n" || value == "no" || value == "false" || value == "0") return false;
  return fallback;
}

void IniFile::Set(const std::string& section, const std::string& key, const std::string& value) {
  std::string current, candidate, old_value;
  size_t insert_at = lines_.size();
  bool found_section = false;
  for (size_t i = 0; i < lines_.size(); ++i) {
    if (Section(lines_[i], current)) {
      if (found_section && current != Lower(section)) { insert_at = i; break; }
      if (current == Lower(section)) found_section = true;
      continue;
    }
    if (current == Lower(section) && Pair(lines_[i], candidate, old_value) && candidate == Lower(key)) {
      lines_[i] = key + "=" + value;
      return;
    }
  }
  if (!found_section) {
    if (!lines_.empty() && !lines_.back().empty()) lines_.emplace_back();
    lines_.push_back("[" + section + "]");
    lines_.push_back(key + "=" + value);
  } else {
    lines_.insert(lines_.begin() + static_cast<std::ptrdiff_t>(insert_at), key + "=" + value);
  }
}

bool LoadSettings(const std::filesystem::path& path, Settings& settings, std::string& error) {
  IniFile ini;
  std::error_code ec;
  if (!std::filesystem::exists(path, ec)) {
    if (ec) { error = "Cannot inspect the settings file: " + ec.message(); return false; }
    ini.Set("SysSet", "HomeUrl", settings.home_url);
    ini.Set("SysSet", "HomePage", "");
    ini.Set("SysSet", "ClearCache", "Y");
    ini.Set("SysSet", "Locale", "zh-TW");
    ini.Set("SysSet", "ReptoolPath", "prg/Reptool.exe");
    ini.Set("SysSet", "ReptoolConfigIni", "");
    ini.Set("Window", "Width", "1200");
    ini.Set("Window", "Height", "850");
    ini.Set("Window", "Maximized", "N");
    ini.Set("UserSet", "ZoomPercent", "100");
    if (!ini.Save(path, error)) return false;
  } else if (!ini.Load(path, error)) {
    return false;
  }
  settings.home_url = ini.Get("SysSet", "HomeUrl", settings.home_url);
  //2026.10.12 modify by codex, preserve an explicitly allowed empty Mac URL while retaining Windows fallback.
  if (settings.home_url.empty() && !settings.allow_empty_home_url) settings.home_url = "https://oa.lysm.com.tw/";
  if (!settings.home_url.empty() && settings.home_url.find(":") == std::string::npos) settings.home_url = "https://" + settings.home_url;
  const auto home_page = ini.Get("SysSet", "HomePage");
  if (!home_page.empty() && !settings.home_url.empty()) {
    if (!settings.home_url.ends_with('/') && !home_page.starts_with('/')) settings.home_url += '/';
    settings.home_url += home_page;
  }
  settings.locale = ini.Get("SysSet", "Locale", "zh-TW");
  settings.clear_site_data = ini.GetBool("SysSet", "ClearCache", true);
  settings.reptool_path = ini.Get("SysSet", "ReptoolPath", "prg/Reptool.exe");
  if (settings.reptool_path.empty()) settings.reptool_path = "prg/Reptool.exe";
  settings.reptool_config = ini.Get("SysSet", "ReptoolConfigIni");
  settings.width = std::clamp(ini.GetInt("Window", "Width", 1200), 640, 8192);
  settings.height = std::clamp(ini.GetInt("Window", "Height", 850), 480, 8192);
  settings.left = ini.GetInt("Window", "Left", -1);
  settings.top = ini.GetInt("Window", "Top", -1);
  settings.maximized = ini.GetBool("Window", "Maximized", false);
  settings.zoom_percent = std::clamp(ini.GetInt("UserSet", "ZoomPercent", 100), 25, 500);
  return true;
}

bool SaveWindowSettings(const std::filesystem::path& path, int x, int y,
                        int width, int height, bool maximized, std::string& error) {
  IniFile ini;
  if (!ini.Load(path, error)) return false;
  ini.Set("Window", "Left", std::to_string(x));
  ini.Set("Window", "Top", std::to_string(y));
  ini.Set("Window", "Width", std::to_string(width));
  ini.Set("Window", "Height", std::to_string(height));
  ini.Set("Window", "Maximized", maximized ? "Y" : "N");
  return ini.Save(path, error);
}

std::string GetCommandField(const std::string& command, const std::string& key) {
  size_t start = 0;
  while (start < command.size()) {
    const auto end = command.find('|', start);
    const auto field = command.substr(start, end == std::string::npos ? end : end - start);
    const auto equal = field.find('=');
    if (equal != std::string::npos && Lower(field.substr(0, equal)) == Lower(key)) return field.substr(equal + 1);
    if (end == std::string::npos) break;
    start = end + 1;
  }
  return {};
}

std::string QuoteJavaScript(const std::string& value) {
  std::string result = "'";
  constexpr char hex[] = "0123456789abcdef";
  for (unsigned char c : value) {
    if (c == '\'' || c == '\\') { result += '\\'; result += static_cast<char>(c); }
    else if (c < 32) { result += "\\x"; result += hex[c >> 4]; result += hex[c & 15]; }
    else result += static_cast<char>(c);
  }
  return result + "'";
}

std::vector<std::pair<std::string, std::string>> IniFile::SectionValues(const std::string& section) const {
  std::vector<std::pair<std::string, std::string>> values;
  std::vector<std::string> seen;
  std::string current, key, value;
  for (const auto& line : lines_) {
    if (Section(line, current)) continue;
    if (current != Lower(section) || !Pair(line, key, value)) continue;
    if (std::find(seen.begin(), seen.end(), key) != seen.end()) continue;
    seen.push_back(key);
    const auto text = Trim(line);
    values.emplace_back(Trim(text.substr(0, text.find('='))), value);
  }
  return values;
}

bool SaveUserSetting(const std::filesystem::path& path, const std::string& key,
                      const std::string& value, std::string& error) {
  if (Trim(key).empty() || key.front() == ';' || key.front() == '#' ||
      key.find_first_of("[]=\r\n\0", 0, 6) != std::string::npos ||
      value.find_first_of("\r\n\0", 0, 3) != std::string::npos) {
    error = "The user setting cannot be represented as a single INI entry.";
    return false;
  }
  IniFile ini;
  if (!ini.Load(path, error)) return false;
  ini.Set("UserSet", key, value);
  return ini.Save(path, error);
}

std::string UserSettingsScript(const IniFile& ini) {
  std::string script = "var $usr=$usr||{};";
  for (const auto& [key, value] : ini.SectionValues("UserSet")) {
    if (!value.empty()) script += "$usr[" + QuoteJavaScript(key) + "]=" + QuoteJavaScript(value) + ";";
  }
  return script;
}

std::string SerializedUserSettings(const IniFile& ini) {
  std::string result;
  for (const auto& [key, value] : ini.SectionValues("UserSet")) {
    if (!result.empty()) result += '|';
    result += key + "=" + value;
  }
  return result;
}

std::string EncodeCookieValue(const std::string& value) {
  constexpr char hex[] = "0123456789ABCDEF";
  std::string result;
  for (unsigned char c : value) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
        c == '-' || c == '_' || c == '.' || c == '~') result += static_cast<char>(c);
    else { result += '%'; result += hex[c >> 4]; result += hex[c & 15]; }
  }
  return result;
}

bool IsLegacyOpenProtocol(const std::string& url) {
  const auto colon = url.find(':');
  if (colon == std::string::npos || colon <= 4) return false;
  return Lower(url.substr(0, colon)).ends_with("open");
}

std::filesystem::path ResolveApplicationPath(const std::filesystem::path& application,
                                            const std::string& value) {
  const auto path = Utf8Path(value);
  return path.is_absolute() ? path : (application / path).lexically_normal();
}

}  // namespace oa
