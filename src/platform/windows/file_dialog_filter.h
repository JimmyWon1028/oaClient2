#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace oa {

//2026.10.16 by codex, combine complete CEF expansions without broadening unknown filters.
inline std::wstring CombinedFilePattern(size_t filter_count, const std::vector<std::wstring>& expansions) {
  if (!filter_count || filter_count != expansions.size()) return {};
  std::vector<std::wstring> unique;
  std::wstring pattern;
  for (const auto& expansion : expansions) {
    size_t start = 0;
    do {
      const auto end = expansion.find(L';', start);
      auto extension = expansion.substr(start, end == std::wstring::npos ? end : end - start);
      if (extension.size() < 2 || extension.front() != L'.' ||
          extension.find_first_of(L"*?\\/:\"<>| \t\r\n") != std::wstring::npos || extension.back() == L'.') return {};
      if (std::find(unique.begin(), unique.end(), extension) == unique.end()) {
        unique.push_back(extension);
        if (!pattern.empty()) pattern += L';';
        pattern += L'*' + extension;
      }
      if (end == std::wstring::npos) break;
      start = end + 1;
    } while (true);
  }
  return pattern;
}

}
