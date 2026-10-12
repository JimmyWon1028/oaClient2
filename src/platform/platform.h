#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace oa {

struct AppPaths {
  std::filesystem::path application;
  std::filesystem::path data;
  std::filesystem::path config;
  std::filesystem::path profile;
  std::filesystem::path log;
};

bool GetAppPaths(AppPaths& paths, std::string& error);
//2026.10.12 modify by codex, let each platform select its screenshot directory.
std::filesystem::path PictureDirectory(const AppPaths& paths);
std::vector<char> ReadApplicationImage(const AppPaths& paths, const std::string& name);
bool ClearBrowserProfile(const AppPaths& paths, std::string& error);
bool CommitSettingsFile(const std::filesystem::path& from, const std::filesystem::path& to,
                        std::string& error);
bool OpenConfiguration(const std::filesystem::path& path, std::string& error);
bool OpenDirectory(const std::filesystem::path& path, std::string& error);
bool CaptureWindow(void* window, const std::filesystem::path& directory,
                    std::filesystem::path& output, std::string& error);
void ShowNetworkInfo(void* window);
void ShowSnapshotResult(void* window, const std::filesystem::path& path);
void ResizeBrowserChild(void* child, void* parent, int screen_x, int screen_y,
                        int width, int height);
bool AttachConsoleWindow(void* child, void* parent, std::string& error);
bool PromptServerUrl(void* owner, const std::string& current, std::string& value);
bool LaunchReport(const std::string& executable, const std::string& parameters,
                  const std::filesystem::path& config,
                  const std::filesystem::path& working_directory, std::string& error);
void ShowError(const std::string& message);
void AppendLog(const AppPaths& paths, const std::string& message);
std::filesystem::path Utf8Path(const std::string& value);
std::string PathUtf8(const std::filesystem::path& value);

}  // namespace oa
