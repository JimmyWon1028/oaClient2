#pragma once

namespace oa {

//2026.10.13 modify by codex, reserve only the requested browser shortcuts for website keyboard handlers.
inline bool IsWebsiteShortcut(int key_code, bool shift, bool control, bool alt, bool command) {
  if (!shift && !control && !alt && !command) {
    return key_code == 0x70 || key_code == 0x71 || key_code == 0x72 ||
      key_code == 0x73 || key_code == 0x78;
  }
  if (alt && !shift && !control && !command) return key_code == 'W';
  if (shift && !control && !alt && !command) return key_code == 'F';
  if (!shift && !alt && (control != command)) {
    return key_code == 'F' || key_code == 'E' || key_code == 'S' || key_code == 'N';
  }
  return false;
}

}  // namespace oa
