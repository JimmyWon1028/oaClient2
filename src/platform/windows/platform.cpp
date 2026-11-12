#include "platform/platform.h"

#include <winsock2.h>
#include <windows.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <dwmapi.h>
#include <objidl.h>
#include <gdiplus.h>
#include <shlobj.h>
#include <shellapi.h>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <vector>
#include <sstream>
#include <iterator>
#include "platform/windows/resources.h"

namespace oa {
namespace {

std::wstring Wide(const std::string& text) {
  if (text.empty()) return {};
  const int length = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(),
                                        static_cast<int>(text.size()), nullptr, 0);
  if (length <= 0) return {};
  std::wstring result(length, L'\0');
  MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(), static_cast<int>(text.size()),
                      result.data(), length);
  return result;
}

bool IsReparsePoint(const std::filesystem::path& path) {
  const DWORD attributes = GetFileAttributesW(path.c_str());
  return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_REPARSE_POINT);
}

bool RejectReparseTree(const std::filesystem::path& path, std::string& error) {
  if (IsReparsePoint(path)) { error = "瀏覽器資料目錄含有重新解析點，為保護其他資料，已停止清理。"; return false; }
  std::error_code ec;
  std::filesystem::recursive_directory_iterator it(path, ec), end;
  while (!ec && it != end) {
    if (IsReparsePoint(it->path())) {
      error = "瀏覽器資料目錄含有重新解析點，為保護其他資料，已停止清理。";
      return false;
    }
    it.increment(ec);
  }
  if (ec) { error = "無法檢查瀏覽器資料目錄，錯誤代碼：" + std::to_string(ec.value()); return false; }
  return true;
}

std::wstring QuoteArgument(const std::wstring& value) {
  std::wstring result = L"\"";
  size_t backslashes = 0;
  for (wchar_t c : value) {
    if (c == L'\\') { ++backslashes; continue; }
    result.append(c == L'"' ? backslashes * 2 + 1 : backslashes, L'\\');
    backslashes = 0;
    result += c;
  }
  result.append(backslashes * 2, L'\\');
  return result + L"\"";
}

}  // namespace

std::filesystem::path Utf8Path(const std::string& value) { return std::filesystem::path(Wide(value)); }

std::string PathUtf8(const std::filesystem::path& value) {
  const auto wide = value.wstring();
  const int length = WideCharToMultiByte(CP_UTF8, 0, wide.data(), static_cast<int>(wide.size()),
                                        nullptr, 0, nullptr, nullptr);
  std::string result(length, '\0');
  if (length) WideCharToMultiByte(CP_UTF8, 0, wide.data(), static_cast<int>(wide.size()),
                                 result.data(), length, nullptr, nullptr);
  return result;
}

//2026.10.12 modify by codex, preserve the Windows executable-side screenshot directory.
std::filesystem::path PictureDirectory(const AppPaths& paths) { return paths.application / L"picture"; }

bool GetAppPaths(AppPaths& paths, std::string& error) {
  std::wstring executable(32768, L'\0');
  const DWORD length = GetModuleFileNameW(nullptr, executable.data(), static_cast<DWORD>(executable.size()));
  if (!length || length >= executable.size()) { error = "無法取得 oaClient2.exe 的所在位置。"; return false; }
  executable.resize(length);
  paths.application = std::filesystem::path(executable).parent_path();
  PWSTR local = nullptr;
  if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &local))) {
    error = "無法取得本機應用程式資料目錄（LocalAppData）。";
    return false;
  }
  paths.data = std::filesystem::path(local) / L"oaClient2" / L"data";
  CoTaskMemFree(local);
  paths.config = paths.application / L"Config.ini";
  paths.profile = paths.data / L"browser-profile";
  paths.log = paths.data / L"application.log";
  std::error_code ec;
  std::filesystem::create_directories(paths.data, ec);
  if (ec || IsReparsePoint(paths.data) || IsReparsePoint(paths.data.parent_path())) {
    error = "無法使用本機應用程式資料目錄，或該目錄含有重新解析點。";
    return false;
  }
  // Preserve prototype settings when moving to the executable-side INI.
  const auto previous = paths.data / L"Config.ini";
  if (!std::filesystem::exists(paths.config, ec) && std::filesystem::is_regular_file(previous, ec)) {
    std::filesystem::copy_file(previous, paths.config, std::filesystem::copy_options::none, ec);
    if (ec) { error = "無法將設定檔 Config.ini 移轉至 oaClient2.exe 所在目錄，錯誤代碼：" + std::to_string(ec.value()); return false; }
  }
  return true;
}

std::vector<char> ReadApplicationImage(const AppPaths& paths, const std::string& name) {
  static const struct { const char* name; int id; } images[] = {
    {"oaClient-16.png", IDR_PNG_OACLIENT_16},
    {"oaClient-32.png", IDR_PNG_OACLIENT_32},
    {"oaClient-256.png", IDR_PNG_OACLIENT_256},
    {"toolbar-console.png", IDR_PNG_CONSOLE},
    {"toolbar-home.png", IDR_PNG_HOME},
    {"toolbar-server.png", IDR_PNG_SERVER},
    {"toolbar-zoom-in.png", IDR_PNG_ZOOM_IN},
    {"toolbar-zoom-out.png", IDR_PNG_ZOOM_OUT}
  };
  int id = 0;
  for (const auto& image : images) {
    if (name == image.name) { id = image.id; break; }
  }
  if (!id) { AppendLog(paths, "IMAGE_RESOURCE_UNKNOWN " + name); return {}; }
  // Read only resources; never execute the launcher or resolve its imports.
  const auto executable = paths.application / L"oaClient2.exe";
  HMODULE module = LoadLibraryExW(executable.c_str(), nullptr,
    LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE);
  std::vector<char> bytes;
  if (module) {
    HRSRC resource = FindResourceW(module, MAKEINTRESOURCEW(id), MAKEINTRESOURCEW(10));
    if (resource) {
      const DWORD size = SizeofResource(module, resource);
      HGLOBAL loaded = LoadResource(module, resource);
      const auto data = static_cast<const char*>(loaded ? LockResource(loaded) : nullptr);
      if (data && size) bytes.assign(data, data + size);
    }
    FreeLibrary(module);
  }
  if (bytes.empty()) AppendLog(paths, "IMAGE_RESOURCE_MISSING " + name);
  return bytes;
}

bool ClearBrowserProfile(const AppPaths& paths, std::string& error) {
  std::error_code ec;
  const auto root = std::filesystem::weakly_canonical(paths.data, ec);
  if (ec || !root.is_absolute() || paths.profile.lexically_normal() != (paths.data / L"browser-profile").lexically_normal()) {
    error = "瀏覽器資料路徑不是 oaClient2 專用目錄，已停止清理。";
    return false;
  }
  if (!std::filesystem::exists(paths.profile, ec)) {
    if (ec) { error = "無法檢查瀏覽器資料目錄，錯誤代碼：" + std::to_string(ec.value()); return false; }
    return true;
  }
  const auto target = std::filesystem::weakly_canonical(paths.profile, ec);
  if (ec || target.parent_path() != root || target.filename() != L"browser-profile") {
    AppendLog(paths, "PROFILE_PATH_REJECTED root=" + PathUtf8(root) + " target=" + PathUtf8(target) +
      " error=" + ec.message());
    error = "瀏覽器資料的實際位置超出 oaClient2 專用資料目錄，已停止清理。";
    return false;
  }
  if (!RejectReparseTree(target, error)) return false;
  std::filesystem::remove_all(target, ec);
  if (ec) { error = "無法清除網站資料，請關閉其他 oaClient2 程式後再試一次。錯誤代碼：" + std::to_string(ec.value()); return false; }
  return true;
}

bool CommitSettingsFile(const std::filesystem::path& from, const std::filesystem::path& to,
                        std::string& error) {
  const auto attributes = GetFileAttributesW(to.c_str());
  if (attributes == INVALID_FILE_ATTRIBUTES) {
    if (MoveFileExW(from.c_str(), to.c_str(), MOVEFILE_WRITE_THROUGH)) return true;
  } else {
    // Retain the existing file's ACLs and streams, including sync-provider metadata.
    if (ReplaceFileW(to.c_str(), from.c_str(), nullptr, 0, nullptr, nullptr)) return true;
  }
  const DWORD replace_error = GetLastError();
  if (replace_error != ERROR_ACCESS_DENIED && replace_error != ERROR_SHARING_VIOLATION &&
      replace_error != ERROR_LOCK_VIOLATION && replace_error != ERROR_UNABLE_TO_REMOVE_REPLACED) {
    error = "無法儲存設定檔 Config.ini，Windows 錯誤代碼：" + std::to_string(replace_error);
    return false;
  }

  // A sync client/editor may permit writing but deny deletion/renaming. Open the
  // existing file without truncation or attribute changes and exclude other writers.
  HANDLE file = CreateFileW(to.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (file == INVALID_HANDLE_VALUE) {
    error = "無法寫入設定檔 Config.ini，Windows 錯誤代碼：" + std::to_string(GetLastError());
    return false;
  }
  std::ifstream input(from, std::ios::binary);
  const std::string replacement((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
  LARGE_INTEGER size{};
  DWORD read = 0;
  bool ready = input.is_open() && !input.bad() && GetFileSizeEx(file, &size) &&
    size.QuadPart >= 0 && size.QuadPart <= MAXDWORD && replacement.size() <= MAXDWORD;
  std::string original;
  if (ready) {
    original.resize(static_cast<size_t>(size.QuadPart));
    ready = original.empty() || (ReadFile(file, original.data(), static_cast<DWORD>(original.size()),
      &read, nullptr) && read == original.size());
  }
  auto write = [file](const std::string& contents) {
    LARGE_INTEGER start{};
    if (!SetFilePointerEx(file, start, nullptr, FILE_BEGIN)) return false;
    DWORD written = 0;
    if (!contents.empty() && (!WriteFile(file, contents.data(), static_cast<DWORD>(contents.size()),
        &written, nullptr) || written != contents.size())) return false;
    return SetEndOfFile(file) && FlushFileBuffers(file);
  };
  bool success = false;
  if (ready) {
    success = write(replacement);
    if (!success) {
      const auto write_error = GetLastError();
      const bool restored = write(original);
      error = "無法完成設定檔 Config.ini 的儲存，Windows 錯誤代碼：" + std::to_string(write_error) +
        (restored ? "；已還原原始內容。" : "；已保留暫存檔供復原使用。");
    }
  } else error = "儲存前無法安全讀取設定檔 Config.ini，原始檔案未變更。";
  CloseHandle(file);
  input.close();
  if (success) DeleteFileW(from.c_str());
  return success;
}

bool OpenConfiguration(const std::filesystem::path& path, std::string& error) {
  const auto result = reinterpret_cast<INT_PTR>(ShellExecuteW(nullptr, L"open", L"notepad.exe",
    QuoteArgument(path.wstring()).c_str(), nullptr, SW_SHOWNORMAL));
  if (result > 32) return true;
  error = "無法開啟設定檔 Config.ini，Windows 殼層錯誤代碼：" + std::to_string(result);
  return false;
}

bool OpenDirectory(const std::filesystem::path& path, std::string& error) {
  const auto result = reinterpret_cast<INT_PTR>(ShellExecuteW(nullptr, L"open", path.c_str(),
    nullptr, nullptr, SW_SHOWNORMAL));
  if (result > 32) return true;
  error = "無法開啟資料夾，Windows 殼層錯誤代碼：" + std::to_string(result);
  return false;
}

void ResizeBrowserChild(void* child, void* parent, int screen_x, int screen_y,
                        int width, int height) {
  const HWND handle = static_cast<HWND>(child);
  const HWND owner = static_cast<HWND>(parent);
  if (!IsWindow(handle) || !IsWindow(owner) || width <= 0 || height <= 0) return;
  POINT point{screen_x, screen_y};
  ScreenToClient(owner, &point);
  SetWindowPos(handle, nullptr, point.x, point.y, width, height, SWP_NOZORDER | SWP_NOACTIVATE);
}

bool AttachConsoleWindow(void* child, void* parent, std::string& error) {
  const HWND handle = static_cast<HWND>(child), owner = static_cast<HWND>(parent);
  if (!IsWindow(handle) || !IsWindow(owner)) { error = "主視窗或主控台（Console）視窗無效。"; return false; }
  auto style = GetWindowLongPtrW(handle, GWL_STYLE);
  style &= ~(WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
  style |= WS_CHILD | WS_CLIPSIBLINGS;
  SetWindowLongPtrW(handle, GWL_STYLE, style);
  SetLastError(0);
  if (!SetParent(handle, owner) && GetLastError()) {
    error = "無法嵌入主控台（Console）視窗，Windows 錯誤代碼：" + std::to_string(GetLastError());
    return false;
  }
  SetWindowPos(handle, nullptr, 0, 0, 1, 1, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
  return true;
}

namespace {
struct UrlDialogData { std::wstring text; HFONT font = nullptr; };
INT_PTR CALLBACK UrlDialogProc(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam) {
  if (message == WM_INITDIALOG) {
    auto data = reinterpret_cast<UrlDialogData*>(lparam);
    SetWindowLongPtrW(dialog, DWLP_USER, lparam);
    SetDlgItemTextW(dialog, IDC_SERVER_URL, data->text.c_str());
    SendDlgItemMessageW(dialog, IDC_SERVER_URL, EM_SETLIMITTEXT, 8192, 0);
    const int dpi = static_cast<int>(GetDpiForWindow(dialog));
    auto px = [dpi](int value) { return MulDiv(value, dpi, 96); };
    data->font = CreateFontW(-px(18), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
      CHINESEBIG5_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
      DEFAULT_PITCH, L"Microsoft JhengHei");
    for (int id : {IDC_SERVER_LABEL, IDC_SERVER_URL, IDOK}) {
      SendDlgItemMessageW(dialog, id, WM_SETFONT, reinterpret_cast<WPARAM>(data->font), TRUE);
    }
    SetWindowPos(dialog, nullptr, 0, 0, px(580), px(200), SWP_NOMOVE | SWP_NOZORDER);
    MoveWindow(GetDlgItem(dialog, IDC_SERVER_LABEL), px(50), px(20), px(480), px(24), TRUE);
    MoveWindow(GetDlgItem(dialog, IDC_SERVER_URL), px(50), px(50), px(480), px(30), TRUE);
    MoveWindow(GetDlgItem(dialog, IDOK), px(252), px(94), px(76), px(34), TRUE);
    RECT bounds{}, parent{};
    GetWindowRect(dialog, &bounds);
    HWND owner = GetWindow(dialog, GW_OWNER);
    if (owner) GetWindowRect(owner, &parent);
    else SystemParametersInfoW(SPI_GETWORKAREA, 0, &parent, 0);
    SetWindowPos(dialog, nullptr, parent.left + ((parent.right - parent.left) - (bounds.right - bounds.left)) / 2,
      parent.top + ((parent.bottom - parent.top) - (bounds.bottom - bounds.top)) / 2, 0, 0,
      SWP_NOSIZE | SWP_NOZORDER);
    SetFocus(GetDlgItem(dialog, IDC_SERVER_URL));
    SendDlgItemMessageW(dialog, IDC_SERVER_URL, EM_SETSEL, 0, -1);
    return FALSE;
  }
  if (message == WM_CTLCOLORSTATIC) {
    SetTextColor(reinterpret_cast<HDC>(wparam), RGB(0, 0, 128));
    SetBkColor(reinterpret_cast<HDC>(wparam), GetSysColor(COLOR_3DFACE));
    return reinterpret_cast<INT_PTR>(GetSysColorBrush(COLOR_3DFACE));
  }
  if (message == WM_COMMAND && LOWORD(wparam) == IDOK) {
    auto data = reinterpret_cast<UrlDialogData*>(GetWindowLongPtrW(dialog, DWLP_USER));
    const int length = GetWindowTextLengthW(GetDlgItem(dialog, IDC_SERVER_URL));
    std::vector<wchar_t> text(length + 1);
    GetDlgItemTextW(dialog, IDC_SERVER_URL, text.data(), static_cast<int>(text.size()));
    data->text = text.data();
    EndDialog(dialog, IDOK);
    return TRUE;
  }
  if (message == WM_CLOSE || (message == WM_COMMAND && LOWORD(wparam) == IDCANCEL)) {
    EndDialog(dialog, IDCANCEL);
    return TRUE;
  }
  if (message == WM_DESTROY) {
    auto data = reinterpret_cast<UrlDialogData*>(GetWindowLongPtrW(dialog, DWLP_USER));
    if (data && data->font) { DeleteObject(data->font); data->font = nullptr; }
  }
  return FALSE;
}
}

bool PromptServerUrl(void* owner, const std::string& current, std::string& value) {
  HMODULE module = nullptr;
  GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
    reinterpret_cast<LPCWSTR>(&UrlDialogProc), &module);
  UrlDialogData data{Wide(current)};
  const auto result = DialogBoxParamW(module, MAKEINTRESOURCEW(IDD_SERVER_URL),
    static_cast<HWND>(owner), UrlDialogProc, reinterpret_cast<LPARAM>(&data));
  if (result != IDOK) return false;
  value = PathUtf8(std::filesystem::path(data.text));
  return true;
}

bool CaptureWindow(void* window, const std::filesystem::path& directory,
                    std::filesystem::path& output, std::string& error) {
  const HWND handle = static_cast<HWND>(window);
  if (!IsWindow(handle) || IsIconic(handle) || GetAncestor(GetForegroundWindow(), GA_ROOT) != handle) {
    error = "請先將 oaClient2 視窗切到前景再截圖。";
    return false;
  }
  RECT bounds{};
  if (FAILED(DwmGetWindowAttribute(handle, DWMWA_EXTENDED_FRAME_BOUNDS, &bounds, sizeof(bounds))) &&
      !GetWindowRect(handle, &bounds)) { error = "無法取得 oaClient2 視窗的位置。"; return false; }
  const int width = bounds.right - bounds.left;
  const int height = bounds.bottom - bounds.top;
  if (width <= 0 || height <= 0) { error = "截圖範圍無效。"; return false; }
  std::error_code ec;
  std::filesystem::create_directories(directory, ec);
  if (ec) { error = "無法建立截圖資料夾 picture，錯誤代碼：" + std::to_string(ec.value()); return false; }
  HDC screen = GetDC(nullptr);
  HDC memory = screen ? CreateCompatibleDC(screen) : nullptr;
  HBITMAP bitmap = memory ? CreateCompatibleBitmap(screen, width, height) : nullptr;
  if (!bitmap) {
    if (memory) DeleteDC(memory);
    if (screen) ReleaseDC(nullptr, screen);
    error = "無法建立視窗截圖所需的影像資源。";
    return false;
  }
  HGDIOBJ previous = SelectObject(memory, bitmap);
  const bool captured = BitBlt(memory, 0, 0, width, height, screen, bounds.left, bounds.top, SRCCOPY | CAPTUREBLT);
  SelectObject(memory, previous);
  DeleteDC(memory);
  ReleaseDC(nullptr, screen);
  bool saved = false;
  Gdiplus::GdiplusStartupInput startup;
  ULONG_PTR token = 0;
  if (captured && Gdiplus::GdiplusStartup(&token, &startup, nullptr) == Gdiplus::Ok) {
    {
      Gdiplus::Bitmap image(bitmap, nullptr);
      UINT count = 0, bytes = 0;
      Gdiplus::GetImageEncodersSize(&count, &bytes);
      std::vector<unsigned char> buffer(bytes);
      auto encoders = reinterpret_cast<Gdiplus::ImageCodecInfo*>(buffer.data());
      if (bytes && Gdiplus::GetImageEncoders(count, bytes, encoders) == Gdiplus::Ok) {
        SYSTEMTIME time{};
        GetLocalTime(&time);
        std::wostringstream name;
        name << L"Snapshot" << std::setfill(L'0') << std::setw(4) << time.wYear
             << std::setw(2) << time.wMonth << std::setw(2) << time.wDay
             << std::setw(2) << time.wHour << std::setw(2) << time.wMinute
             << std::setw(2) << time.wSecond << L"-" << std::setw(3) << time.wMilliseconds << L".jpg";
        output = directory / name.str();
        for (UINT i = 0; i < count; ++i) {
          if (wcscmp(encoders[i].MimeType, L"image/jpeg") == 0) {
            saved = image.Save(output.c_str(), &encoders[i].Clsid, nullptr) == Gdiplus::Ok;
            break;
          }
        }
      }
    }
    Gdiplus::GdiplusShutdown(token);
  }
  DeleteObject(bitmap);
  if (!saved) error = "無法將視窗截圖儲存為 JPG 圖片。";
  return saved;
}

void ShowSnapshotResult(void* window, const std::filesystem::path& path) {
  const std::wstring message = L"截圖完成，存放於：\n" + path.wstring() + L"\n\n是否開啟所在資料夾？";
  if (MessageBoxW(static_cast<HWND>(window), message.c_str(), L"oaClient2 截圖", MB_YESNO | MB_ICONINFORMATION) == IDYES) {
    const auto arguments = L"/select," + QuoteArgument(path.wstring());
    ShellExecuteW(static_cast<HWND>(window), L"open", L"explorer.exe", arguments.c_str(), nullptr, SW_SHOWNORMAL);
  }
}

void ShowNetworkInfo(void* window) {
  ULONG bytes = 16384;
  std::vector<unsigned char> buffer(bytes);
  ULONG result = ERROR_BUFFER_OVERFLOW;
  for (int attempt = 0; attempt < 3 && result == ERROR_BUFFER_OVERFLOW; ++attempt) {
    buffer.resize(bytes);
    result = GetAdaptersAddresses(AF_INET, GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST |
      GAA_FLAG_SKIP_DNS_SERVER, nullptr, reinterpret_cast<IP_ADAPTER_ADDRESSES*>(buffer.data()), &bytes);
  }
  std::wostringstream message;
  if (result == NO_ERROR) {
    for (auto adapter = reinterpret_cast<IP_ADAPTER_ADDRESSES*>(buffer.data()); adapter; adapter = adapter->Next) {
      if (adapter->OperStatus != IfOperStatusUp || adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK) continue;
      message << adapter->FriendlyName << L"\nMAC: " << std::uppercase << std::hex << std::setfill(L'0');
      for (ULONG i = 0; i < adapter->PhysicalAddressLength; ++i) {
        if (i) message << L'-';
        message << std::setw(2) << static_cast<unsigned int>(adapter->PhysicalAddress[i]);
      }
      message << std::dec << L"\n";
      for (auto address = adapter->FirstUnicastAddress; address; address = address->Next) {
        if (address->Address.lpSockaddr->sa_family != AF_INET) continue;
        wchar_t ip[INET_ADDRSTRLEN]{};
        const auto ipv4 = reinterpret_cast<sockaddr_in*>(address->Address.lpSockaddr);
        if (InetNtopW(AF_INET, &ipv4->sin_addr, ip, INET_ADDRSTRLEN)) message << L"IP: " << ip << L"\n";
      }
      message << L"\n";
    }
  }
  const auto text = message.str().empty() ? L"目前沒有可用的 IPv4 網路介面。" : message.str();
  MessageBoxW(static_cast<HWND>(window), text.c_str(), L"oaClient2 網路 IP / MAC", MB_OK | MB_ICONINFORMATION);
}

bool LaunchReport(const std::string& executable, const std::string& parameters,
                  const std::filesystem::path& config,
                  const std::filesystem::path& working_directory, std::string& error) {
  const auto path = Utf8Path(executable);
  std::error_code ec;
  if (path.empty() || !path.is_absolute() || !std::filesystem::is_regular_file(path, ec)) {
    error = "找不到報表程式 Reptool，請檢查設定檔 Config.ini 的 ReptoolPath 是否指向現有的程式檔案。";
    return false;
  }
  if (!std::filesystem::is_regular_file(config, ec)) {
    error = "報表程式 Reptool 的設定檔不存在。";
    return false;
  }
  const std::wstring arguments = QuoteArgument(Wide(parameters)) + L" " + QuoteArgument(config.wstring());
  const auto result = reinterpret_cast<INT_PTR>(ShellExecuteW(nullptr, L"open", path.c_str(),
    arguments.c_str(), working_directory.c_str(), SW_SHOWNORMAL));
  if (result > 32) return true;
  error = "無法啟動報表程式 Reptool，Windows 殼層錯誤代碼：" + std::to_string(result);
  return false;
}

void ShowError(const std::string& message) {
  MessageBoxW(nullptr, Wide(message).c_str(), L"oaClient2", MB_OK | MB_ICONERROR);
}

void AppendLog(const AppPaths& paths, const std::string& message) {
  std::ofstream log(paths.log, std::ios::app);
  if (!log) return;
  const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::tm utc{};
  gmtime_s(&utc, &now);
  log << std::put_time(&utc, "%Y-%m-%dT%H:%M:%SZ") << " " << message << '\n';
}

}  // namespace oa
