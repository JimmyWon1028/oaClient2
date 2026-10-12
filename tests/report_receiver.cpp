#include <windows.h>
#include <shellapi.h>
#include <filesystem>
#include <fstream>
#include <string>

namespace {
std::string Utf8(const std::wstring& text) {
  const auto length = WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
    nullptr, 0, nullptr, nullptr);
  std::string result(length, '\0');
  WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
    result.data(), length, nullptr, nullptr);
  return result;
}
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
  int count = 0;
  auto arguments = CommandLineToArgvW(GetCommandLineW(), &count);
  if (!arguments || count != 3) { if (arguments) LocalFree(arguments); return 1; }
  const auto output = std::filesystem::path(arguments[2]).parent_path() / L"received-report.txt";
  std::ofstream file(output, std::ios::binary);
  file << Utf8(arguments[1]) << '\n' << Utf8(arguments[2]) << '\n'
       << Utf8(std::filesystem::current_path().wstring()) << '\n';
  LocalFree(arguments);
  return file ? 0 : 2;
}
