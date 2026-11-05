/*
 * AutoHideCN - simplified Chinese desktop icon auto-hide utility.
 * v1.4.1: validated desktop double-clicks, event-driven visibility and DPI-aware settings.
 * Pure Win32 / no CRT build for a portable Windows x64 EXE.
 * Independent implementation; no original SoftwareOK code or resources.
 * Compiles with clang -target x86_64-pc-windows-msvc and lld-link.
 */

typedef unsigned char BYTE;
typedef unsigned short WORD, WCHAR, ATOM;
typedef unsigned int UINT, DWORD, COLORREF;
typedef int BOOL, INT, LONG;
typedef long long LONGLONG, INT_PTR, LPARAM, LRESULT;
typedef unsigned long long ULONGLONG, UINT_PTR, ULONG_PTR, WPARAM;
typedef void *PVOID, *HANDLE, *HINSTANCE, *HMODULE, *HWND, *HICON, *HCURSOR,
             *HBRUSH, *HDC, *HFONT, *HMENU, *HHOOK, *HKEY, *HGDIOBJ;
typedef const WCHAR *LPCWSTR;
typedef WCHAR *LPWSTR;
#define API __declspec(dllimport)
#define COUNT(a) (sizeof(a)/sizeof((a)[0]))
#define LOWORD(x) ((WORD)((UINT_PTR)(x) & 65535u))
#define RGBW(r,g,b) ((COLORREF)((r)|((g)<<8)|((b)<<16)))
#define FALSE 0
#define TRUE 1
#define WM_NULL 0x0000u
#define WM_CREATE 0x0001u
#define WM_DESTROY 0x0002u
#define WM_CLOSE 0x0010u
#define WM_ENDSESSION 0x0016u
#define WM_QUERYENDSESSION 0x0011u
#define WM_DPICHANGED 0x02e0u
#define WM_MOUSEMOVE 0x0200u
#define WM_MOUSELEAVE 0x02a3u
#define WM_LBUTTONUP 0x0202u
#define WM_SETFOCUS 0x0007u
#define WM_KILLFOCUS 0x0008u
#define WM_CHAR 0x0102u
#define WM_KEYDOWN 0x0100u
#define WM_PASTE 0x0302u
#define WM_SETTEXT 0x000cu
#define WM_GETDLGCODE 0x0087u
#define WM_CTLCOLOREDIT 0x0133u
#define WM_ERASEBKGND 0x0014u
#define WM_PAINT 0x000fu
#define WM_DRAWITEM 0x002bu
#define WM_COMMAND 0x0111u
#define WM_TIMER 0x0113u
#define WM_SETFONT 0x0030u
#define WM_LBUTTONDOWN 0x0201u
#define WM_LBUTTONDBLCLK 0x0203u
#define WM_RBUTTONDOWN 0x0204u
#define WM_RBUTTONUP 0x0205u
#define WM_MBUTTONDOWN 0x0207u
#define WM_CONTEXTMENU 0x007bu
#define WM_USER 0x0400u
#define WM_APP 0x8000u
#define WS_CHILD 0x40000000u
#define WS_VISIBLE 0x10000000u
#define WS_CAPTION 0x00c00000u
#define WS_SYSMENU 0x00080000u
#define WS_MINIMIZEBOX 0x00020000u
#define WS_TABSTOP 0x00010000u
#define WS_VSCROLL 0x00200000u
#define WS_EX_CLIENTEDGE 0x00000200u
#define SS_LEFT 0
#define BS_PUSHBUTTON 0
#define BS_DEFPUSHBUTTON 1
#define ES_NUMBER 0x2000u
#define ES_AUTOHSCROLL 0x0080u
#define EM_SETLIMITTEXT 0x00c5u
#define EM_SETSEL 0x00b1u
#define EN_SETFOCUS 0x0100u
#define EN_KILLFOCUS 0x0200u
#define BS_OWNERDRAW 0x0000000bu
#define BN_CLICKED 0u
#define ODS_SELECTED 0x0001u
#define ODS_FOCUS 0x0010u
#define DT_LEFT 0x0000u
#define DT_CENTER 0x0001u
#define DT_VCENTER 0x0004u
#define DT_SINGLELINE 0x0020u
#define DT_NOPREFIX 0x0800u
#define TRANSPARENT 1
#define PS_SOLID 0
#define SW_HIDE 0
#define SW_SHOWNORMAL 1
#define SW_SHOWNA 8
#define SWP_NOSIZE 0x0001u
#define SWP_NOMOVE 0x0002u
#define SWP_NOACTIVATE 0x0010u
#define MB_OK 0
#define MB_ICONWARNING 0x30u
#define MB_ICONINFORMATION 0x40u
#define MF_STRING 0u
#define MF_SEPARATOR 0x0800u
#define MF_CHECKED 0x0008u
#define TPM_RIGHTBUTTON 0x0002u
#define TPM_NONOTIFY 0x0080u
#define TPM_RETURNCMD 0x0100u
#define NIF_MESSAGE 1u
#define NIF_ICON 2u
#define NIF_TIP 4u
#define NIM_ADD 0u
#define NIM_MODIFY 1u
#define NIM_DELETE 2u
#define NIM_SETVERSION 4u
#define NOTIFYICON_VERSION_4 4u
#define NIN_SELECT WM_USER
#define ERROR_SUCCESS 0u
#define ERROR_FILE_NOT_FOUND 2u
#define ERROR_ALREADY_EXISTS 183u
#define INVALID_FILE_ATTRIBUTES 0xffffffffu
#define REG_SZ 1u
#define KEY_QUERY_VALUE 0x0001u
#define KEY_SET_VALUE 0x0002u
#define GA_ROOT 2u
#define HC_ACTION 0
#define WH_MOUSE_LL 14
#define LOGPIXELSX 88
#define FW_NORMAL 400
#define FW_SEMIBOLD 600
#define DEFAULT_CHARSET 1
#define CLEARTYPE_QUALITY 5
#define FF_SWISS 32
#define COLOR_WINDOW 5
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define SM_CXDOUBLECLK 36
#define SM_CYDOUBLECLK 37
#define SM_CXDRAG 68
#define SM_CYDRAG 69
#define GWLP_WNDPROC (-4)
#define TME_LEAVE 0x00000002u
#define EVENT_OBJECT_CREATE 0x8000u
#define EVENT_OBJECT_DESTROY 0x8001u
#define EVENT_OBJECT_SHOW 0x8002u
#define EVENT_OBJECT_HIDE 0x8003u
#define OBJID_WINDOW 0
#define WINEVENT_SKIPOWNPROCESS 2u
#define LVM_HITTEST 0x1012u
#define SMTO_BLOCK 1u
#define SMTO_ABORTIFHUNG 2u
#define PROCESS_VM_OPERATION 8u
#define PROCESS_VM_READ 16u
#define PROCESS_VM_WRITE 32u
#define MEM_COMMIT 0x1000u
#define MEM_RESERVE 0x2000u
#define MEM_RELEASE 0x8000u
#define PAGE_READWRITE 4u
#define CF_UNICODETEXT 13u
#define HKEY_CURRENT_USER ((HKEY)(INT_PTR)(LONG)0x80000001u)
#define HWND_TOPMOST ((HWND)(INT_PTR)-1)
#define HWND_NOTOPMOST ((HWND)(INT_PTR)-2)
#define IDC_ARROW ((LPCWSTR)(UINT_PTR)32512)
#define IDI_APPLICATION ((LPCWSTR)(UINT_PTR)32512)

typedef struct { LONG x, y; } POINT;
typedef struct { LONG left, top, right, bottom; } RECT;
typedef struct {
    HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam;
    DWORD time; POINT pt; DWORD lPrivate;
} MSG;
typedef LRESULT (*WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef struct {
    UINT cbSize, style; WNDPROC lpfnWndProc;
    INT cbClsExtra, cbWndExtra; HINSTANCE hInstance;
    HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground;
    LPCWSTR lpszMenuName, lpszClassName; HICON hIconSm;
} WNDCLASSEXW;
typedef struct {
    DWORD cbSize; HWND hWnd; UINT uID, uFlags, uCallbackMessage; HICON hIcon;
    WCHAR szTip[128]; DWORD dwState, dwStateMask; WCHAR szInfo[256];
    UINT uVersion; WCHAR szInfoTitle[64]; DWORD dwInfoFlags;
    BYTE guidItem[16]; HICON hBalloonIcon;
} NOTIFYICONDATAW;
typedef struct { POINT pt; DWORD mouseData, flags, time; ULONG_PTR dwExtraInfo; } MSLLHOOKSTRUCT;
typedef struct {
    HDC hdc; BOOL fErase; RECT rcPaint; BOOL fRestore; BOOL fIncUpdate; BYTE rgbReserved[32];
} PAINTSTRUCT;
typedef struct {
    UINT CtlType, CtlID, itemID, itemAction, itemState;
    HWND hwndItem; HDC hDC; RECT rcItem; ULONG_PTR itemData;
} DRAWITEMSTRUCT;
typedef struct { DWORD cbSize, dwFlags; HWND hwndTrack; DWORD dwHoverTime; } TRACKMOUSEEVENT;
typedef struct { POINT pt; UINT flags; int iItem, iSubItem, iGroup; } LVHITTESTINFO;
typedef struct { DWORD attributes; DWORD creation[2],access[2],write[2],size_high,size_low; } FILE_ATTRIBUTES;

_Static_assert(sizeof(WCHAR)==2, "Windows requires 16-bit WCHAR");
_Static_assert(sizeof(MSG)==48, "MSG layout mismatch");
_Static_assert(sizeof(WNDCLASSEXW)==80, "WNDCLASSEXW layout mismatch");
_Static_assert(sizeof(NOTIFYICONDATAW)==976, "NOTIFYICONDATAW layout mismatch");
_Static_assert(sizeof(MSLLHOOKSTRUCT)==32, "MSLLHOOKSTRUCT layout mismatch");
_Static_assert(sizeof(PAINTSTRUCT)==72, "PAINTSTRUCT layout mismatch");
_Static_assert(sizeof(DRAWITEMSTRUCT)==64, "DRAWITEMSTRUCT layout mismatch");

/* Imports are supplied by the Windows OS; no C/C++ runtime required. */
API HMODULE GetModuleHandleW(LPCWSTR);
API DWORD GetModuleFileNameW(HMODULE, LPWSTR, DWORD);
API DWORD GetEnvironmentVariableW(LPCWSTR, LPWSTR, DWORD);
API DWORD GetFileAttributesW(LPCWSTR);
API BOOL GetFileAttributesExW(LPCWSTR,int,FILE_ATTRIBUTES*);
API BOOL CreateDirectoryW(LPCWSTR, void*);
API BOOL CopyFileW(LPCWSTR, LPCWSTR, BOOL);
API BOOL MoveFileExW(LPCWSTR,LPCWSTR,DWORD);
API BOOL DeleteFileW(LPCWSTR);
API BOOL SetFileAttributesW(LPCWSTR,DWORD);
API UINT GetPrivateProfileStringW(LPCWSTR,LPCWSTR,LPCWSTR,LPWSTR,DWORD,LPCWSTR);
API HANDLE OpenProcess(DWORD,BOOL,DWORD);
API PVOID VirtualAllocEx(HANDLE,PVOID,ULONGLONG,DWORD,DWORD);
API BOOL VirtualFreeEx(HANDLE,PVOID,ULONGLONG,DWORD);
API BOOL WriteProcessMemory(HANDLE,PVOID,const void*,ULONGLONG,ULONGLONG*);
API BOOL ReadProcessMemory(HANDLE,const void*,PVOID,ULONGLONG,ULONGLONG*);
API PVOID GlobalLock(HANDLE);
API BOOL GlobalUnlock(HANDLE);
API UINT GetPrivateProfileIntW(LPCWSTR, LPCWSTR, INT, LPCWSTR);
API BOOL WritePrivateProfileStringW(LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR);
API HANDLE CreateMutexW(void*, BOOL, LPCWSTR);
API DWORD GetLastError(void);
API BOOL CloseHandle(HANDLE);
API ULONGLONG GetTickCount64(void);
API void *GetProcAddress(HMODULE, const char*);
API void ExitProcess(UINT);
API BOOL SetProcessDPIAware(void);
API UINT GetDoubleClickTime(void);
API BOOL ScreenToClient(HWND,POINT*);
API LRESULT SendMessageTimeoutW(HWND,UINT,WPARAM,LPARAM,UINT,UINT,ULONG_PTR*);
API HANDLE SetWinEventHook(DWORD,DWORD,HMODULE,void (*)(HANDLE,DWORD,HWND,LONG,LONG,DWORD,DWORD),DWORD,DWORD,DWORD);
API BOOL UnhookWinEvent(HANDLE);
API LONGLONG SetWindowLongPtrW(HWND,int,LONGLONG);
API LRESULT CallWindowProcW(WNDPROC,HWND,UINT,WPARAM,LPARAM);
API BOOL TrackMouseEvent(TRACKMOUSEEVENT*);
API HWND GetFocus(void);
API BOOL IsDialogMessageW(HWND,MSG*);
API BOOL OpenClipboard(HWND);
API HANDLE GetClipboardData(UINT);
API BOOL CloseClipboard(void);
API int GetSystemMetrics(int);
API HCURSOR LoadCursorW(HINSTANCE,LPCWSTR);
API HICON LoadIconW(HINSTANCE,LPCWSTR);
API ATOM RegisterClassExW(const WNDCLASSEXW*);
API HWND CreateWindowExW(DWORD,LPCWSTR,LPCWSTR,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,void*);
API BOOL AdjustWindowRectEx(RECT*,DWORD,BOOL,DWORD);
API BOOL ShowWindow(HWND,int);
API BOOL UpdateWindow(HWND);
API BOOL SetForegroundWindow(HWND);
API BOOL SetWindowPos(HWND,HWND,int,int,int,int,UINT);
API BOOL IsWindow(HWND);
API BOOL IsWindowVisible(HWND);
API HWND FindWindowW(LPCWSTR,LPCWSTR);
API HWND FindWindowExW(HWND,HWND,LPCWSTR,LPCWSTR);
API BOOL EnumWindows(BOOL (*)(HWND,LPARAM),LPARAM);
API BOOL EnumChildWindows(HWND,BOOL (*)(HWND,LPARAM),LPARAM);
API HWND GetAncestor(HWND,UINT);
API int GetClassNameW(HWND,LPWSTR,int);
API HWND WindowFromPoint(POINT);
API DWORD GetWindowThreadProcessId(HWND,DWORD*);
API LRESULT DefWindowProcW(HWND,UINT,WPARAM,LPARAM);
API BOOL DestroyWindow(HWND);
API int GetMessageW(MSG*,HWND,UINT,UINT);
API BOOL TranslateMessage(const MSG*);
API LRESULT DispatchMessageW(const MSG*);
API void PostQuitMessage(int);
API BOOL PostMessageW(HWND,UINT,WPARAM,LPARAM);
API LRESULT SendMessageW(HWND,UINT,WPARAM,LPARAM);
API LRESULT SetTimer(HWND,UINT_PTR,UINT,void*);
API BOOL KillTimer(HWND,UINT_PTR);
API BOOL GetClientRect(HWND,RECT*);
API BOOL FillRect(HDC,const RECT*,HBRUSH);
API HDC BeginPaint(HWND,PAINTSTRUCT*);
API BOOL EndPaint(HWND,const PAINTSTRUCT*);
API int DrawTextW(HDC,LPCWSTR,int,RECT*,UINT);
API int GetDlgCtrlID(HWND);
API BOOL InvalidateRect(HWND,const RECT*,BOOL);
API BOOL DrawFocusRect(HDC,const RECT*);
API HDC GetDC(HWND);
API int ReleaseDC(HWND,HDC);
API int GetDeviceCaps(HDC,int);
API int MulDiv(int,int,int);
API BOOL SetWindowTextW(HWND,LPCWSTR);
API int GetWindowTextW(HWND,LPWSTR,int);
API HWND SetFocus(HWND);
API int MessageBoxW(HWND,LPCWSTR,LPCWSTR,UINT);
API BOOL GetCursorPos(POINT*);
API HMENU CreatePopupMenu(void);
API BOOL AppendMenuW(HMENU,UINT,UINT_PTR,LPCWSTR);
API UINT TrackPopupMenu(HMENU,UINT,int,int,int,HWND,const RECT*);
API BOOL DestroyMenu(HMENU);
API HHOOK SetWindowsHookExW(int,LRESULT (*)(int,WPARAM,LPARAM),HINSTANCE,DWORD);
API LRESULT CallNextHookEx(HHOOK,int,WPARAM,LPARAM);
API BOOL UnhookWindowsHookEx(HHOOK);
API UINT RegisterWindowMessageW(LPCWSTR);
API BOOL Shell_NotifyIconW(DWORD,NOTIFYICONDATAW*);
API HFONT CreateFontW(int,int,int,int,int,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,LPCWSTR);
API HBRUSH CreateSolidBrush(COLORREF);
API BOOL DeleteObject(HGDIOBJ);
API COLORREF SetBkColor(HDC,COLORREF);
API COLORREF SetTextColor(HDC,COLORREF);
API int SetBkMode(HDC,int);
API HGDIOBJ SelectObject(HDC,HGDIOBJ);
API HGDIOBJ CreatePen(int,int,COLORREF);
API BOOL RoundRect(HDC,int,int,int,int,int,int);
API BOOL Ellipse(HDC,int,int,int,int);
API BOOL MoveToEx(HDC,int,int,POINT*);
API BOOL LineTo(HDC,int,int);
API long DwmSetWindowAttribute(HWND,DWORD,const void*,DWORD);
API LONG RegOpenKeyExW(HKEY,LPCWSTR,DWORD,DWORD,HKEY*);
API LONG RegQueryValueExW(HKEY,LPCWSTR,DWORD*,DWORD*,BYTE*,DWORD*);
API LONG RegCreateKeyExW(HKEY,LPCWSTR,DWORD,LPWSTR,DWORD,DWORD,void*,HKEY*,DWORD*);
API LONG RegSetValueExW(HKEY,LPCWSTR,DWORD,DWORD,const BYTE*,DWORD);
API LONG RegDeleteValueW(HKEY,LPCWSTR);
API LONG RegCloseKey(HKEY);

static const WCHAR app_name[] = L"桌面图标自动隐藏";
static const WCHAR window_class[] = L"AutoHideCN.MainWindow.3";
static const WCHAR config_section[] = L"Config";
static const WCHAR run_path[] = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
static const WCHAR run_name[] = L"AutoHideCN";
enum {
  ID_ENABLED=101, ID_SECONDS, ID_DBLCLICK,
  ID_STARTUP, ID_MINIMIZED, ID_TOPMOST,
  ID_APPLY,
  ID_TRAY_OPEN=300, ID_TRAY_HIDE, ID_TRAY_SHOW, ID_TRAY_PAUSE, ID_TRAY_EXIT
};
enum { MSG_TRAY=WM_APP+1, MSG_MOUSE=WM_APP+2, MSG_SHOW=WM_APP+3, MSG_DESKTOP=WM_APP+4,
       TIMER_HIDE=1, TIMER_RECOVER=2, TIMER_NOTICE=3, TIMER_TRAY=4, TIMER_TOGGLE=5 };
static HINSTANCE instance;
static HANDLE mutex;
static HWND main_window, desktop_list, desktop_root, desktop_view, seconds_edit, save_button;
static HWND enabled_switch, dblclick_switch;
static HWND startup_switch, minimized_switch, topmost_switch;
static HHOOK mouse_hook;
static HICON app_icon;
static HFONT regular_font,section_font,small_font,button_font;
static HBRUSH white_brush;
static WNDPROC button_proc,edit_proc;
static BOOL ui_check_state[256],ui_hover[256];
static HANDLE visibility_hook,desktop_process;
static PVOID remote_hit;
static BOOL remote_timeout,paused,tray_registered,shutting_down;
static UINT taskbar_created, dpi=96;
static WCHAR ini_file[1024];
static BOOL enabled=1,double_click_toggle=1;
static BOOL start_minimized=0,always_on_top=0;
static BOOL hidden=0,owned_hidden=0,known_desktop=0;
static ULONGLONG last_reveal=0;
static WCHAR ui_notice[120];
static BOOL notice_error;
static BOOL click_pending,click_released,click_burst,click_ready,left_down;
static BOOL toggle_pending,toggle_show;
static HWND toggle_list;
static POINT toggle_point;
static DWORD click_time;
static POINT click_point;
static int seconds=5;
static void restart_countdown(void);
static void refresh_desktop(void);
static void notice(LPCWSTR,BOOL);
static void sync_mouse_hook(void);
static int parse_seconds(const WCHAR*);
static void visibility_event(HANDLE,DWORD,HWND,LONG,LONG,DWORD,DWORD);

static UINT wlen(const WCHAR *s) { UINT n=0; if(s) while(s[n]) n++; return n; }
static BOOL weq(const WCHAR*a,const WCHAR*b) { UINT n=0; if(!a || !b) return a==b; for(;;n++){ if(a[n]!=b[n]) return 0; if(!a[n])return 1;} }
static void wcopy(WCHAR *d,UINT cap,const WCHAR*s) { UINT i=0; if(!cap)return; if(s)for(;i+1<cap && s[i];i++)d[i]=s[i]; d[i]=0; }
static void wappend(WCHAR*d,UINT cap,const WCHAR*s) { UINT n=wlen(d); if(n<cap)wcopy(d+n,cap-n,s); }
static void wnum(WCHAR*d,UINT cap,unsigned value) {
  WCHAR b[22]; UINT i=0,j=0; do{ b[i++]=(WCHAR)(L'0'+value%10);value/=10;}while(value && i<COUNT(b));
  if(cap==0)return;
  while(i && j+1<cap)d[j++]=b[--i];
  d[j]=0;
}
static void path_append(WCHAR *p,UINT cap,const WCHAR*name) {
  UINT n=wlen(p); if(n && p[n-1]!=L'\\' && p[n-1]!=L'/')wappend(p,cap,L"\\");wappend(p,cap,name);
}
static void exe_folder(WCHAR*out,UINT cap) {
  UINT n=GetModuleFileNameW(0,out,cap),i;
  if(!n || n>=cap){wcopy(out,cap,L".");return;}
  for(i=n;i>0;i--){if(out[i-1]==L'\\' || out[i-1]==L'/'){out[i-1]=0;return;}}
  wcopy(out,cap,L".");
}
static void appdata_file(WCHAR*out,UINT cap,BOOL create) {
  WCHAR folder[1024];DWORD n=GetEnvironmentVariableW(L"APPDATA",folder,COUNT(folder));
  if(!n || n>=COUNT(folder)){exe_folder(folder,COUNT(folder));}
  else {path_append(folder,COUNT(folder),L"AutoHideCN");if(create)CreateDirectoryW(folder,0);}
  wcopy(out,cap,folder);path_append(out,cap,L"AutoHideCN.ini");
}
static void locate_settings(void) {
  static WCHAR portable[1024],roaming[1024];
  FILE_ATTRIBUTES local_info={0},roaming_info={0};BOOL local_exists,roaming_exists,local_valid,roaming_valid;
  WCHAR value[32];
  exe_folder(portable,COUNT(portable));path_append(portable,COUNT(portable),L"AutoHideCN.ini");
  appdata_file(roaming,COUNT(roaming),0);
  local_exists=GetFileAttributesExW(portable,0,&local_info);
  roaming_exists=GetFileAttributesExW(roaming,0,&roaming_info);
  GetPrivateProfileStringW(config_section,L"seconds",L"",value,COUNT(value),portable);local_valid=parse_seconds(value)>0;
  GetPrivateProfileStringW(config_section,L"seconds",L"",value,COUNT(value),roaming);roaming_valid=parse_seconds(value)>0;
  /* A writable APPDATA fallback must remain authoritative on the next run,
   * even when a stale, read-only portable INI is still beside the EXE. */
  if(roaming_exists && (!local_exists || (roaming_valid && !local_valid) ||
     (local_valid==roaming_valid && (roaming_info.write[1]>local_info.write[1] ||
     (roaming_info.write[1]==local_info.write[1] && roaming_info.write[0]>local_info.write[0])))))
    wcopy(ini_file,COUNT(ini_file),roaming);
  else wcopy(ini_file,COUNT(ini_file),portable);
}
static int load_int(const WCHAR*name,int fallback) {return (int)GetPrivateProfileIntW(config_section,name,fallback,ini_file);}
static void load_settings(void) {
  WCHAR value[32];locate_settings();enabled=load_int(L"enabled",1)!=0;
  GetPrivateProfileStringW(config_section,L"seconds",L"",value,COUNT(value),ini_file);seconds=parse_seconds(value);
  if(seconds<1 || seconds>10800)seconds=5;
  double_click_toggle=load_int(L"double_click_toggle",1)!=0;
  start_minimized=load_int(L"start_minimized",0)!=0;
  always_on_top=load_int(L"always_on_top",0)!=0;
}
/* Stage a complete INI beside the destination and atomically replace it. Existing
 * unrelated sections survive; retired keys are removed from Config. */
static BOOL write_settings_from(LPCWSTR path,LPCWSTR source,int delay,BOOL auto_hide,BOOL toggle,BOOL minimized,BOOL topmost) {
  WCHAR temp[1100],number[24]; BOOL ok;
  wcopy(temp,COUNT(temp),path);wappend(temp,COUNT(temp),L".tmp");
  if(GetFileAttributesW(source)!=INVALID_FILE_ATTRIBUTES){
    if(!CopyFileW(source,temp,FALSE))return 0;
    if(!SetFileAttributesW(temp,0x80u)){DeleteFileW(temp);return 0;}
  }
  else DeleteFileW(temp);
  ok=WritePrivateProfileStringW(config_section,0,0,temp);
  wnum(number,COUNT(number),(UINT)delay);
  ok=WritePrivateProfileStringW(config_section,L"seconds",number,temp)&&ok;
  ok=WritePrivateProfileStringW(config_section,L"enabled",auto_hide?L"1":L"0",temp)&&ok;
  ok=WritePrivateProfileStringW(config_section,L"double_click_toggle",toggle?L"1":L"0",temp)&&ok;
  ok=WritePrivateProfileStringW(config_section,L"start_minimized",minimized?L"1":L"0",temp)&&ok;
  ok=WritePrivateProfileStringW(config_section,L"always_on_top",topmost?L"1":L"0",temp)&&ok;
  /* The cache-flush form may return zero even after all writes succeeded. */
  WritePrivateProfileStringW(0,0,0,temp);
  if(ok)ok=MoveFileExW(temp,path,0x1u|0x8u); /* REPLACE_EXISTING | WRITE_THROUGH */
  if(!ok)DeleteFileW(temp);
  return ok;
}
static BOOL write_settings_at(LPCWSTR path,int delay,BOOL auto_hide,BOOL toggle,BOOL minimized,BOOL topmost) {
  return write_settings_from(path,path,delay,auto_hide,toggle,minimized,topmost);
}
static BOOL startup_enabled(void) {
  HKEY key=0; LONG result;
  if(RegOpenKeyExW(HKEY_CURRENT_USER,run_path,0,KEY_QUERY_VALUE,&key)!=0)return 0;
  result=RegQueryValueExW(key,run_name,0,0,0,0);RegCloseKey(key);return result==0;
}
static BOOL set_startup(BOOL wanted) {
  HKEY key=0; LONG result;
  if(RegCreateKeyExW(HKEY_CURRENT_USER,run_path,0,0,0,KEY_SET_VALUE,0,&key,0)!=0)return 0;
  if(wanted){
    static WCHAR cmd[1024]; wcopy(cmd,COUNT(cmd),L"\"");
    {static WCHAR exepath[900];GetModuleFileNameW(0,exepath,COUNT(exepath));wappend(cmd,COUNT(cmd),exepath);}
    wappend(cmd,COUNT(cmd),L"\"");
    result=RegSetValueExW(key,run_name,0,REG_SZ,(const BYTE*)cmd,(DWORD)((wlen(cmd)+1)*sizeof(WCHAR)));
  }else{result=RegDeleteValueW(key,run_name);if(result==ERROR_FILE_NOT_FOUND)result=0;}
  RegCloseKey(key);return result==0;
}
static BOOL find_defview_cb(HWND window, LPARAM param) {
  HWND*items=(HWND*)(UINT_PTR)param;HWND view=FindWindowExW(window,0,L"SHELLDLL_DefView",0);
  if(view){items[0]=view;items[1]=GetAncestor(view,GA_ROOT);return 0;}return 1;
}
static BOOL find_list_cb(HWND child,LPARAM param) {
  WCHAR klass[64];GetClassNameW(child,klass,COUNT(klass));
  if(weq(klass,L"SysListView32")){*(HWND*)(UINT_PTR)param=child;return 0;}return 1;
}
static BOOL locate_desktop(void) {
  HWND view,root,list,windows[2]={0,0};
  if(desktop_list && IsWindow(desktop_list) && desktop_root && IsWindow(desktop_root))return 1;
  if(visibility_hook){UnhookWinEvent(visibility_hook);visibility_hook=0;}
  if(remote_hit && !remote_timeout)VirtualFreeEx(desktop_process,remote_hit,0,MEM_RELEASE);
  /* A timed-out receiver might still access the remote page. In that exceptional
   * case Explorer reclaims the page on exit; never reuse or free it prematurely. */
  remote_hit=0;remote_timeout=0;
  if(desktop_process){CloseHandle(desktop_process);desktop_process=0;}
  desktop_list=0;desktop_root=0;desktop_view=0;
  known_desktop=0;owned_hidden=0;
  view=FindWindowW(L"Progman",0);
  if(view)view=FindWindowExW(view,0,L"SHELLDLL_DefView",0);
  if(view){windows[0]=view;windows[1]=GetAncestor(view,GA_ROOT);}
  else EnumWindows(find_defview_cb,(LPARAM)(UINT_PTR)windows);
  view=windows[0];root=windows[1];
  if(!view){desktop_list=0;desktop_root=0;return 0;}
  list=FindWindowExW(view,0,L"SysListView32",0);
  if(!list)EnumChildWindows(view,find_list_cb,(LPARAM)(UINT_PTR)&list);
  if(!list){desktop_list=0;desktop_root=0;return 0;}
  desktop_list=list;desktop_root=root;desktop_view=view;
  {DWORD pid=0;GetWindowThreadProcessId(list,&pid);
    if(pid)visibility_hook=SetWinEventHook(EVENT_OBJECT_CREATE,EVENT_OBJECT_HIDE,0,visibility_event,pid,0,WINEVENT_SKIPOWNPROCESS);}
  return 1;
}

static BOOL system_icons_disabled(void) {
  HKEY key=0;DWORD value=0,size=sizeof(value),type=0;
  if(RegOpenKeyExW(HKEY_CURRENT_USER,L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced",0,KEY_QUERY_VALUE,&key)!=0)return 0;
  if(RegQueryValueExW(key,L"HideIcons",0,&type,(BYTE*)&value,&size)!=0 || type!=4 || size!=4)value=0;
  RegCloseKey(key);return value!=0;
}
static void restart_countdown(void) {
  ULONGLONG elapsed,delay;
  KillTimer(main_window,TIMER_HIDE);
  if(!enabled || paused || toggle_pending || !known_desktop || hidden || shutting_down || system_icons_disabled())return;
  elapsed=GetTickCount64()-last_reveal;delay=(ULONGLONG)(UINT)seconds*1000u;
  SetTimer(main_window,TIMER_HIDE,(UINT)(elapsed>=delay?1:delay-elapsed),0);
}
static void refresh_desktop(void) {
  BOOL now;
  if(!locate_desktop()){KillTimer(main_window,TIMER_HIDE);return;}
  now=!IsWindowVisible(desktop_list);
  if(!known_desktop || now!=hidden){
    hidden=now;owned_hidden=0;known_desktop=1;
    if(!hidden)last_reveal=GetTickCount64();
    restart_countdown();
  }
}
static BOOL set_icons_visible(BOOL visible) {
  BOOL was_hidden;
  KillTimer(main_window,TIMER_TOGGLE);toggle_pending=0;
  refresh_desktop();if(!known_desktop)return 0;
  if(visible && system_icons_disabled())return 0;
  was_hidden=hidden;
  if(hidden==visible)ShowWindow(desktop_list,visible?SW_SHOWNA:SW_HIDE);
  hidden=!IsWindowVisible(desktop_list);
  if(!was_hidden && hidden)owned_hidden=1;
  if(!hidden)owned_hidden=0;
  if(!hidden)last_reveal=GetTickCount64();
  restart_countdown();
  return hidden==!visible;
}
static void restore_desktop(void) {
  if(owned_hidden && IsWindow(desktop_list) && !IsWindowVisible(desktop_list) && !system_icons_disabled())
    ShowWindow(desktop_list,SW_SHOWNA);
  owned_hidden=0;
}

/* Only data (LVHITTESTINFO), never code, is placed in Explorer. LVM_* messages
 * do not marshal pointers across processes. Fail closed on access/timeout errors. */
static BOOL list_blank_at(POINT point) {
  LVHITTESTINFO hit={0}; ULONG_PTR result=0; DWORD pid=0;RECT bounds;
  if(remote_timeout)return 0;
  if(!ScreenToClient(desktop_list,&point) || !GetClientRect(desktop_list,&bounds) ||
     point.x<0 || point.y<0 || point.x>=bounds.right || point.y>=bounds.bottom)return 0;
  if(!desktop_process){
    GetWindowThreadProcessId(desktop_list,&pid);
    desktop_process=OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE,FALSE,pid);
  }
  if(!desktop_process)return 0;
  if(!remote_hit)remote_hit=VirtualAllocEx(desktop_process,0,sizeof(hit),MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
  if(!remote_hit)return 0;
  hit.pt=point;hit.iItem=-1;
  if(!WriteProcessMemory(desktop_process,remote_hit,&hit,sizeof(hit),0))return 0;
  if(!SendMessageTimeoutW(desktop_list,LVM_HITTEST,0,(LPARAM)(UINT_PTR)remote_hit,
                          SMTO_BLOCK|SMTO_ABORTIFHUNG,100,&result)){
    remote_timeout=1;return 0;
  }
  if(!ReadProcessMemory(desktop_process,remote_hit,&hit,sizeof(hit),0))return 0;
  return (INT_PTR)result==-1 && hit.iItem==-1 && (hit.flags&1u)!=0; /* LVHT_NOWHERE */
}
static BOOL desktop_click_at(POINT pt) {
  HWND hit,root;WCHAR klass[48];DWORD a=0,b=0;
  refresh_desktop();if(!known_desktop)return 0;
  hit=WindowFromPoint(pt);if(!hit)return 0;
  root=GetAncestor(hit,GA_ROOT);if(!root)return 0;
  if(root!=desktop_root){
    if(!hidden)return 0;
    GetClassNameW(root,klass,COUNT(klass));
    if(!weq(klass,L"WorkerW") && !weq(klass,L"Progman"))return 0;
    GetWindowThreadProcessId(root,&a);GetWindowThreadProcessId(desktop_root,&b);
    if(!a || a!=b)return 0;
  }
  if(hit!=root && hit!=desktop_view && hit!=desktop_list)return 0;
  return hidden?1:list_blank_at(pt);
}
static LRESULT mouse_proc(int code,WPARAM msg,LPARAM data) {
  if(code==HC_ACTION && main_window && !shutting_down &&
     (msg==WM_LBUTTONDOWN || msg==WM_LBUTTONUP || msg==WM_RBUTTONDOWN || msg==WM_MBUTTONDOWN)){
    MSLLHOOKSTRUCT*mouse=(MSLLHOOKSTRUCT*)(UINT_PTR)data;
    /* Queue coordinates/time only: no cross-process calls inside the LL hook. */
    PostMessageW(main_window,MSG_MOUSE,((WPARAM)mouse->time<<32)|msg,
       (LPARAM)(((ULONGLONG)(DWORD)mouse->pt.y<<32)|(DWORD)mouse->pt.x));
  }
  return CallNextHookEx(mouse_hook,code,msg,data);
}
static void sync_mouse_hook(void) {
  click_pending=0;click_released=0;click_burst=0;click_ready=0;left_down=0;
  KillTimer(main_window,TIMER_TOGGLE);toggle_pending=0;
  restart_countdown();
  if(!double_click_toggle){if(mouse_hook)UnhookWindowsHookEx(mouse_hook);mouse_hook=0;return;}
  if(mouse_hook)return;
  mouse_hook=SetWindowsHookExW(WH_MOUSE_LL,mouse_proc,instance,0);
  if(!mouse_hook)notice(L"无法监听双击，请通过托盘操作",1);
}
static BOOL near_point(POINT a,POINT b,int width,int height) {
  LONGLONG dx=(LONGLONG)a.x-b.x,dy=(LONGLONG)a.y-b.y;
  return dx>=-width/2 && dx<=width/2 && dy>=-height/2 && dy<=height/2;
}
static BOOL register_click(UINT msg,POINT point,DWORD time,BOOL blank) {
  BOOL same;
  if(msg==WM_LBUTTONUP){
    click_released=click_pending && near_point(point,click_point,GetSystemMetrics(SM_CXDRAG),GetSystemMetrics(SM_CYDRAG));
    BOOL fire=click_ready && click_released && blank && (DWORD)(time-click_time)<=GetDoubleClickTime();
    click_ready=0;
    if(!click_released)click_pending=0;
    return fire;
  }
  if(msg!=WM_LBUTTONDOWN || !blank){
    click_pending=0;click_burst=0;click_released=0;click_ready=0;return 0;
  }
  same=click_pending && (DWORD)(time-click_time)<=GetDoubleClickTime() &&
       near_point(point,click_point,GetSystemMetrics(SM_CXDOUBLECLK),GetSystemMetrics(SM_CYDOUBLECLK));
  BOOL fire=same && click_released && !click_burst;
  click_ready=fire;
  if(fire)click_burst=1;
  else if(!same)click_burst=0;
  /* Keep a consumed burst until a time/distance break, so a triple/quadruple
   * click never toggles twice. Each pair requires a released first click. */
  click_pending=1;click_released=0;click_time=time;click_point=point;
  return 0; /* The second down only arms the pair. Never change its target yet. */
}
static void defer_toggle(POINT point) {
  toggle_pending=1;toggle_show=hidden;toggle_list=desktop_list;toggle_point=point;
  KillTimer(main_window,TIMER_HIDE);
  /* LL notifications precede Explorer's input handling. Let both releases and
   * native double-click/focus processing finish before hiding the list view. */
  if(!SetTimer(main_window,TIMER_TOGGLE,75,0)){
    toggle_pending=0;restart_countdown();notice(L"无法切换桌面图标，请稍后重试",1);
  }
}
static void finish_toggle(void) {
  BOOL show=toggle_show;HWND list=toggle_list;
  KillTimer(main_window,TIMER_TOGGLE);
  if(!toggle_pending)return;
  if(left_down){SetTimer(main_window,TIMER_TOGGLE,75,0);return;}
  toggle_pending=0;
  if(double_click_toggle && !shutting_down && desktop_click_at(toggle_point) && desktop_list==list)
    set_icons_visible(show);
  else restart_countdown();
}
static void on_mouse(WPARAM wp,LPARAM lp) {
  DWORD time=(DWORD)(wp>>32);UINT msg=(UINT)wp;
  POINT point={(LONG)(DWORD)lp,(LONG)(DWORD)((ULONGLONG)lp>>32)};
  if(!double_click_toggle)return;
  if(msg==WM_LBUTTONDOWN)left_down=1;
  if(msg==WM_LBUTTONUP){
    left_down=0;
    if(toggle_pending)SetTimer(main_window,TIMER_TOGGLE,75,0);
  }
  BOOL blank=(msg==WM_LBUTTONDOWN || (msg==WM_LBUTTONUP && click_ready))?desktop_click_at(point):0;
  if(register_click(msg,point,time,blank))defer_toggle(point);
}
static void visibility_event(HANDLE hook,DWORD event,HWND window,LONG object,LONG child,DWORD thread,DWORD time) {
  (void)hook;(void)child;(void)thread;(void)time;
  if(shutting_down || object!=OBJID_WINDOW)return;
  if(window==desktop_list || window==desktop_view || window==desktop_root ||
     (event==EVENT_OBJECT_CREATE && !IsWindow(desktop_list)))PostMessageW(main_window,MSG_DESKTOP,0,0);
}
static void tray_add(void) {
  NOTIFYICONDATAW n={0};n.cbSize=sizeof(n);n.hWnd=main_window;n.uID=1;
  n.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;n.uCallbackMessage=MSG_TRAY;n.hIcon=app_icon;
  wcopy(n.szTip,COUNT(n.szTip),app_name);tray_registered=Shell_NotifyIconW(NIM_ADD,&n);
  if(!tray_registered)tray_registered=Shell_NotifyIconW(NIM_MODIFY,&n);
  if(tray_registered){n.uVersion=NOTIFYICON_VERSION_4;Shell_NotifyIconW(NIM_SETVERSION,&n);KillTimer(main_window,TIMER_TRAY);}
  else SetTimer(main_window,TIMER_TRAY,2000,0);
}
static void tray_delete(void) {
  NOTIFYICONDATAW n={0};n.cbSize=sizeof(n);n.hWnd=main_window;n.uID=1;
  Shell_NotifyIconW(NIM_DELETE,&n);
}
static void show_main(void) {ShowWindow(main_window,SW_SHOWNORMAL);SetForegroundWindow(main_window);SetFocus(enabled_switch);}
static void tray_menu(void) {
  HMENU m=CreatePopupMenu();UINT id;POINT p={0};if(!m)return;
  AppendMenuW(m,MF_STRING,ID_TRAY_OPEN,L"打开设置");AppendMenuW(m,MF_SEPARATOR,0,0);
  AppendMenuW(m,MF_STRING,ID_TRAY_SHOW,L"显示桌面图标");
  AppendMenuW(m,MF_STRING,ID_TRAY_HIDE,L"隐藏桌面图标");
  AppendMenuW(m,MF_STRING,ID_TRAY_PAUSE,paused?L"恢复自动隐藏":L"暂停自动隐藏");
  AppendMenuW(m,MF_SEPARATOR,0,0);
  AppendMenuW(m,MF_STRING,ID_TRAY_EXIT,L"退出程序");
  GetCursorPos(&p);SetForegroundWindow(main_window);
  id=TrackPopupMenu(m,TPM_RETURNCMD|TPM_NONOTIFY|TPM_RIGHTBUTTON,p.x,p.y,0,main_window,0);
  DestroyMenu(m);
  if(id)SendMessageW(main_window,WM_COMMAND,(WPARAM)id,0);
  PostMessageW(main_window,WM_NULL,0,0);
}
static int scale(int x) {return MulDiv(x,(int)dpi,96);}
static LRESULT hover_proc(HWND window,UINT msg,WPARAM wp,LPARAM lp) {
  int id=GetDlgCtrlID(window);
  if(id>=0 && id<(int)COUNT(ui_hover)){
    if(msg==WM_MOUSEMOVE && !ui_hover[id]){
      TRACKMOUSEEVENT track={sizeof(track),TME_LEAVE,window,0};
      ui_hover[id]=1;TrackMouseEvent(&track);InvalidateRect(window,0,FALSE);
    }else if(msg==WM_MOUSELEAVE){ui_hover[id]=0;InvalidateRect(window,0,FALSE);}
  }
  return CallWindowProcW(button_proc,window,msg,wp,lp);
}
static BOOL digits_only(LPCWSTR text) {
  UINT i=0;if(!text)return 0;
  while(text[i]){if(text[i]<L'0' || text[i]>L'9' || i>=5)return 0;i++;}return 1;
}
static LRESULT number_proc(HWND window,UINT msg,WPARAM wp,LPARAM lp) {
  if(msg==WM_CHAR && wp>=32 && (wp<L'0' || wp>L'9'))return 0;
  if(msg==WM_SETTEXT && !digits_only((LPCWSTR)(UINT_PTR)lp))return 0;
  if(msg==WM_PASTE){
    BOOL valid=0;
    if(OpenClipboard(window)){
      HANDLE data=GetClipboardData(CF_UNICODETEXT);
      if(data){LPCWSTR text=(LPCWSTR)GlobalLock(data);valid=digits_only(text);if(text)GlobalUnlock(data);}
      CloseClipboard();
    }
    if(!valid){notice(L"隐藏时间只能输入整数",1);return 0;}
  }
  return CallWindowProcW(edit_proc,window,msg,wp,lp);
}
static HWND control(LPCWSTR cls,LPCWSTR txt,DWORD style,int x,int y,int w,int h,int id,DWORD ex) {
  HWND c=CreateWindowExW(ex,cls,txt,WS_CHILD|WS_VISIBLE|style,scale(x),scale(y),scale(w),scale(h),main_window,(HMENU)(INT_PTR)id,instance,0);
  if(c && regular_font)SendMessageW(c,WM_SETFONT,(WPARAM)(UINT_PTR)regular_font,TRUE);
  if(c && weq(cls,L"BUTTON")){
    WNDPROC prev=(WNDPROC)(UINT_PTR)SetWindowLongPtrW(c,GWLP_WNDPROC,(LONGLONG)(UINT_PTR)hover_proc);
    if(!button_proc)button_proc=prev;
  }
  return c;
}

static void checked(HWND h,BOOL v) {
  int id;if(!h)return;id=GetDlgCtrlID(h);
  if(id>=0 && id<(int)COUNT(ui_check_state)){ui_check_state[id]=v!=0;InvalidateRect(h,0,1);}
}
static BOOL ischecked(HWND h) {
  int id;if(!h)return 0;id=GetDlgCtrlID(h);
  return id>=0 && id<(int)COUNT(ui_check_state)?ui_check_state[id]:0;
}
static void fill_area(HDC dc,int x,int y,int w,int h,COLORREF color) {
  RECT r;HBRUSH brush;
  r.left=scale(x);r.top=scale(y);r.right=scale(x+w);r.bottom=scale(y+h);
  brush=CreateSolidBrush(color);FillRect(dc,&r,brush);DeleteObject((HGDIOBJ)brush);
}
static void rounded(HDC dc,int x,int y,int w,int h,int rad,COLORREF color,COLORREF border) {
  HBRUSH brush=CreateSolidBrush(color);HGDIOBJ old_brush;
  HGDIOBJ pen=CreatePen(PS_SOLID,scale(1),border),old_pen;
  old_brush=SelectObject(dc,(HGDIOBJ)brush);old_pen=SelectObject(dc,pen);
  RoundRect(dc,scale(x),scale(y),scale(x+w),scale(y+h),scale(rad*2),scale(rad*2));
  SelectObject(dc,old_brush);SelectObject(dc,old_pen);
  DeleteObject((HGDIOBJ)brush);DeleteObject(pen);
}
static void line(HDC dc,int x1,int y1,int x2,int y2,COLORREF color,int thick) {
  HGDIOBJ pen=CreatePen(PS_SOLID,scale(thick),color),prev=SelectObject(dc,pen);
  MoveToEx(dc,scale(x1),scale(y1),0);LineTo(dc,scale(x2),scale(y2));
  SelectObject(dc,prev);DeleteObject(pen);
}
static void text_at(HDC dc,LPCWSTR txt,int x,int y,int w,int h,HFONT font,COLORREF color,UINT flags) {
  RECT r={scale(x),scale(y),scale(x+w),scale(y+h)};
  HGDIOBJ old=SelectObject(dc,(HGDIOBJ)font);
  SetBkMode(dc,TRANSPARENT);SetTextColor(dc,color);
  DrawTextW(dc,txt,-1,&r,flags|DT_NOPREFIX);
  SelectObject(dc,old);
}
static void paint_layout(HDC dc) {
  COLORREF bg=RGBW(248,250,249),panel=RGBW(255,255,255),hair=RGBW(232,238,234);
  COLORREF text=RGBW(36,51,41),muted=RGBW(120,133,124);
  fill_area(dc,0,0,420,488,bg);
  rounded(dc,16,16,388,412,10,panel,hair);
  text_at(dc,L"自动隐藏",32,28,300,24,section_font,text,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
  text_at(dc,L"隐藏时间",32,98,190,28,regular_font,text,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
  rounded(dc,278,94,78,34,5,panel,GetFocus()==seconds_edit?RGBW(34,163,74):RGBW(211,221,215));
  text_at(dc,L"秒",366,98,22,28,regular_font,muted,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
  line(dc,32,144,388,144,hair,1);
  text_at(dc,L"双击隐藏 / 显示",32,158,320,24,section_font,text,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
  text_at(dc,L"双击桌面空白处，切换图标显示状态。",32,230,356,22,small_font,muted,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
  line(dc,32,264,388,264,hair,1);
  text_at(dc,L"其他设置",32,278,300,24,section_font,text,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
  text_at(dc,ui_notice,20,434,242,48,small_font,notice_error?RGBW(183,56,42):RGBW(34,143,65),DT_LEFT|DT_VCENTER);
}

static void paint_switch(const DRAWITEMSTRUCT* di) {
  HDC dc=di->hDC;RECT r=di->rcItem;WCHAR caption[120];
  int id=(int)di->CtlID;
  int track_w=scale(38), track_h=scale(20), knob=scale(16), radius=scale(20);
  int tx=r.right-track_w, ty=(r.top+r.bottom-track_h)/2;
  int knob_x=ui_check_state[id]? tx+track_w-knob-scale(2) : tx+scale(2);
  COLORREF on=RGBW(34,163,74), off=RGBW(210,218,213);
  if(ui_hover[id]){on=RGBW(29,148,66);off=RGBW(192,205,197);}
  if(di->itemState&ODS_SELECTED){on=RGBW(23,125,55);off=RGBW(176,192,182);}
  HBRUSH bg=CreateSolidBrush(RGBW(255,255,255));
  HGDIOBJ old=SelectObject(dc,(HGDIOBJ)bg);
  FillRect(dc,&r,bg);
  SelectObject(dc,old);DeleteObject((HGDIOBJ)bg);

  GetWindowTextW(di->hwndItem,caption,COUNT(caption));
  { RECT txt=r; txt.right=tx-scale(14);
    SetBkMode(dc,TRANSPARENT); SetTextColor(dc,RGBW(42,52,46));
    old=SelectObject(dc,(HGDIOBJ)regular_font);
    DrawTextW(dc,caption,-1,&txt,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
    SelectObject(dc,old); }

  { HBRUSH fill=CreateSolidBrush(ui_check_state[id]?on:off);
    HGDIOBJ old_b=SelectObject(dc,(HGDIOBJ)fill);
    HGDIOBJ pen=CreatePen(PS_SOLID,scale(1),ui_check_state[id]?on:RGBW(195,205,198));
    HGDIOBJ old_p=SelectObject(dc,pen);
    RoundRect(dc,tx,ty,tx+track_w,ty+track_h,radius,radius);
    SelectObject(dc,old_b); SelectObject(dc,old_p);
    DeleteObject((HGDIOBJ)fill); DeleteObject(pen); }

  { HBRUSH fill=CreateSolidBrush(RGBW(255,255,255));
    HGDIOBJ old_b=SelectObject(dc,(HGDIOBJ)fill);
    HGDIOBJ pen=CreatePen(PS_SOLID,scale(1),RGBW(230,235,231));
    HGDIOBJ old_p=SelectObject(dc,pen);
    Ellipse(dc,knob_x,ty+scale(2),knob_x+knob,ty+scale(2)+knob);
    SelectObject(dc,old_b); SelectObject(dc,old_p);
    DeleteObject((HGDIOBJ)fill); DeleteObject(pen); }

  if(di->itemState&ODS_FOCUS){RECT f=di->rcItem;f.left+=scale(2);f.right-=scale(2);f.top+=scale(2);f.bottom-=scale(2);DrawFocusRect(dc,&f);}
}

static void paint_action_button(const DRAWITEMSTRUCT* di) {
  int id=(int)di->CtlID,primary=(id==ID_APPLY);
  int x=di->rcItem.left,y=di->rcItem.top;
  int w=di->rcItem.right-x,h=di->rcItem.bottom-y;
  COLORREF fill=primary?RGBW(34,163,74):RGBW(255,255,255);
  COLORREF edge=primary?RGBW(34,163,74):RGBW(214,224,217);
  COLORREF ink=primary?RGBW(255,255,255):RGBW(45,61,50);
  WCHAR caption[48];RECT txt=di->rcItem;
  HBRUSH b;HGDIOBJ old_b,p,old_p;
  if(ui_hover[id])fill=RGBW(29,148,66);
  if(di->itemState&ODS_SELECTED)fill=RGBW(23,125,55);
  b=CreateSolidBrush(RGBW(248,250,249));FillRect(di->hDC,&di->rcItem,b);DeleteObject((HGDIOBJ)b);
  b=CreateSolidBrush(fill);p=CreatePen(PS_SOLID,scale(1),edge);
  old_b=SelectObject(di->hDC,(HGDIOBJ)b);old_p=SelectObject(di->hDC,p);
  RoundRect(di->hDC,x,y,x+w,y+h,scale(10),scale(10));
  SelectObject(di->hDC,old_b);SelectObject(di->hDC,old_p);
  DeleteObject((HGDIOBJ)b);DeleteObject(p);
  GetWindowTextW(di->hwndItem,caption,COUNT(caption));
  SetBkMode(di->hDC,TRANSPARENT);SetTextColor(di->hDC,ink);
  {HGDIOBJ old=SelectObject(di->hDC,(HGDIOBJ)button_font);
    DrawTextW(di->hDC,caption,-1,&txt,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
    SelectObject(di->hDC,old);}
  if(di->itemState&ODS_FOCUS){
    RECT f=di->rcItem;f.left+=scale(4);f.top+=scale(4);f.right-=scale(4);f.bottom-=scale(4);
    DrawFocusRect(di->hDC,&f);
  }
}
static BOOL is_switch_id(int id) {
  return id==ID_ENABLED||id==ID_DBLCLICK||id==ID_STARTUP||id==ID_MINIMIZED||id==ID_TOPMOST;
}
static void create_fonts(void) {
  if(regular_font)DeleteObject((HGDIOBJ)regular_font);
  if(small_font)DeleteObject((HGDIOBJ)small_font);
  if(section_font)DeleteObject((HGDIOBJ)section_font);
  if(button_font)DeleteObject((HGDIOBJ)button_font);
  regular_font=CreateFontW(-MulDiv(10,(int)dpi,72),0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,FF_SWISS,L"Microsoft YaHei UI");
  small_font=CreateFontW(-MulDiv(9,(int)dpi,72),0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,FF_SWISS,L"Microsoft YaHei UI");
  section_font=CreateFontW(-MulDiv(11,(int)dpi,72),0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,FF_SWISS,L"Microsoft YaHei UI");
  button_font=CreateFontW(-MulDiv(10,(int)dpi,72),0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,FF_SWISS,L"Microsoft YaHei UI");

}
static void move_control(HWND control_window,int x,int y,int width,int height) {
  SetWindowPos(control_window,0,scale(x),scale(y),scale(width),scale(height),0x4u|SWP_NOACTIVATE);
  SendMessageW(control_window,WM_SETFONT,(WPARAM)(UINT_PTR)regular_font,TRUE);
}
static void layout_ui(void) {
  move_control(enabled_switch,32,58,356,30);
  move_control(seconds_edit,286,100,62,24);
  move_control(dblclick_switch,32,190,356,30);
  move_control(startup_switch,32,310,356,30);
  move_control(topmost_switch,32,346,356,30);
  move_control(minimized_switch,32,382,356,30);
  move_control(save_button,276,444,128,34);
  InvalidateRect(main_window,0,TRUE);
}
static void create_ui(void) {
  WCHAR number[24];create_fonts();white_brush=CreateSolidBrush(RGBW(255,255,255));
  enabled_switch=control(L"BUTTON",L"启用自动隐藏",BS_OWNERDRAW|WS_TABSTOP,32,58,356,30,ID_ENABLED,0);
  seconds_edit=control(L"EDIT",L"",WS_TABSTOP|ES_NUMBER|ES_AUTOHSCROLL,286,100,62,24,ID_SECONDS,0);
  edit_proc=(WNDPROC)(UINT_PTR)SetWindowLongPtrW(seconds_edit,GWLP_WNDPROC,(LONGLONG)(UINT_PTR)number_proc);
  SendMessageW(seconds_edit,EM_SETLIMITTEXT,5,0);
  wnum(number,COUNT(number),(unsigned)seconds);SetWindowTextW(seconds_edit,number);
  dblclick_switch=control(L"BUTTON",L"启用双击切换",BS_OWNERDRAW|WS_TABSTOP,32,190,356,30,ID_DBLCLICK,0);
  startup_switch=control(L"BUTTON",L"开机自动启动",BS_OWNERDRAW|WS_TABSTOP,32,310,356,30,ID_STARTUP,0);
  topmost_switch=control(L"BUTTON",L"窗口置顶",BS_OWNERDRAW|WS_TABSTOP,32,346,356,30,ID_TOPMOST,0);
  minimized_switch=control(L"BUTTON",L"启动后隐藏至托盘",BS_OWNERDRAW|WS_TABSTOP,32,382,356,30,ID_MINIMIZED,0);
  save_button=control(L"BUTTON",L"保存设置",BS_OWNERDRAW|WS_TABSTOP,276,444,128,34,ID_APPLY,0);

  checked(enabled_switch,enabled);
  checked(dblclick_switch,double_click_toggle);
  checked(startup_switch,startup_enabled());
  checked(minimized_switch,start_minimized);
  checked(topmost_switch,always_on_top);
}

static int parse_seconds(const WCHAR*text) {
  int x=0,i=0,any=0;
  while(text[i]>=L'0' && text[i]<=L'9'){
    any=1;x=x*10+(int)(text[i]-L'0');if(x>10800)return -1;i++;
  }
  return any && !text[i] && x>=1?x:-1;
}

static void notice(LPCWSTR text,BOOL error) {
  wcopy(ui_notice,COUNT(ui_notice),text);notice_error=error;
  SetTimer(main_window,TIMER_NOTICE,error?6000:2400,0);InvalidateRect(main_window,0,FALSE);
}
static BOOL apply_settings(void) {
  WCHAR text[64];static WCHAR fallback[1024],target[1024];int n;BOOL wanted_startup,old_startup,saved;
  GetWindowTextW(seconds_edit,text,COUNT(text));n=parse_seconds(text);
  if(n<1){notice(text[0]?L"请输入 1～10800 之间的整数秒数":L"请输入隐藏时间（1～10800 秒）",1);
    SetFocus(seconds_edit);SendMessageW(seconds_edit,EM_SETSEL,0,-1);return 0;}
  wanted_startup=ischecked(startup_switch);old_startup=startup_enabled();
  if(!set_startup(wanted_startup)){
    notice(L"无法修改开机自启设置，请重试",1);return 0;
  }
  wcopy(target,COUNT(target),ini_file);
  saved=write_settings_at(target,n,ischecked(enabled_switch),ischecked(dblclick_switch),ischecked(minimized_switch),ischecked(topmost_switch));
  if(!saved){
    appdata_file(fallback,COUNT(fallback),1);
    if(!weq(target,fallback)){
      saved=write_settings_from(fallback,ini_file,n,ischecked(enabled_switch),ischecked(dblclick_switch),ischecked(minimized_switch),ischecked(topmost_switch));
      if(saved){wcopy(target,COUNT(target),fallback);}
    }
  }
  if(!saved){
    if(!set_startup(old_startup))notice(L"保存失败，开机自启恢复失败，请检查",1);
    else notice(L"配置保存失败，请检查目录写入权限",1);
    return 0;
  }
  wcopy(ini_file,COUNT(ini_file),target);
  seconds=n;enabled=ischecked(enabled_switch);double_click_toggle=ischecked(dblclick_switch);
  start_minimized=ischecked(minimized_switch);always_on_top=ischecked(topmost_switch);
  SetWindowPos(main_window,always_on_top?HWND_TOPMOST:HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
  paused=0;refresh_desktop();last_reveal=GetTickCount64();restart_countdown();sync_mouse_hook();
  notice(mouse_hook || !double_click_toggle?L"设置已保存":L"已保存，但双击监听失败",!mouse_hook && double_click_toggle);
  return 1;
}


static LRESULT window_proc(HWND window,UINT msg,WPARAM wp,LPARAM lp) {
  if(taskbar_created && msg==taskbar_created){
    tray_registered=0;tray_add();refresh_desktop();return 0;
  }
  switch(msg){
    case WM_CREATE:
      main_window=window;
      {typedef UINT (*WINDOW_DPI)(HWND);
        WINDOW_DPI get_dpi=(WINDOW_DPI)GetProcAddress(GetModuleHandleW(L"user32.dll"),"GetDpiForWindow");
        if(get_dpi)dpi=get_dpi(window);}
      create_ui();tray_add();
      /* Slow fallback also covers a missing accessibility event / shell restart. */
      SetTimer(window,TIMER_RECOVER,5000,0);
      sync_mouse_hook();refresh_desktop();return 0;
    case WM_ERASEBKGND:return TRUE;
    case WM_PAINT:{PAINTSTRUCT ps={0};HDC dc=BeginPaint(window,&ps);if(dc)paint_layout(dc);EndPaint(window,&ps);return 0;}
    case WM_DRAWITEM:{const DRAWITEMSTRUCT* di=(const DRAWITEMSTRUCT*)(UINT_PTR)lp;
      if(!di)return 0;
      if(is_switch_id((int)di->CtlID)){paint_switch(di);return TRUE;}
      if(di->CtlID==ID_APPLY){ paint_action_button(di); return TRUE; } return 0;}
    case WM_COMMAND:{
      int id=LOWORD(wp),code=(int)((UINT_PTR)wp>>16);
      if(id==ID_SECONDS && (code==EN_SETFOCUS || code==EN_KILLFOCUS)){InvalidateRect(window,0,FALSE);return 0;}
      if(is_switch_id(id) && code==BN_CLICKED){
        HWND box=(HWND)(UINT_PTR)lp;checked(box,!ischecked(box));
        return 0;
      }
      switch(id){
        case ID_TRAY_HIDE:
          if(!set_icons_visible(0))MessageBoxW(window,L"隐藏失败：未找到可控制的桌面图标。",app_name,MB_OK|MB_ICONWARNING);
          return 0;
        case ID_TRAY_SHOW:
          if(!set_icons_visible(1))MessageBoxW(window,L"显示失败：请确认系统已开启“显示桌面图标”。",app_name,MB_OK|MB_ICONWARNING);
          return 0;
        case ID_APPLY:
          apply_settings();
          return 0;
        case ID_TRAY_OPEN:show_main();return 0;
        case ID_TRAY_PAUSE:
          paused=!paused;refresh_desktop();last_reveal=GetTickCount64();restart_countdown();return 0;
        case ID_TRAY_EXIT:DestroyWindow(window);return 0;
      }return 0;
    }
    case MSG_MOUSE:on_mouse(wp,lp);return 0;
    case MSG_DESKTOP:refresh_desktop();return 0;
    case MSG_SHOW:show_main();return 0;
    case MSG_TRAY:
      if(LOWORD(lp)==WM_LBUTTONDBLCLK || LOWORD(lp)==NIN_SELECT)show_main();
      else if(LOWORD(lp)==WM_CONTEXTMENU || LOWORD(lp)==WM_RBUTTONUP)tray_menu();
      return 0;
    case WM_TIMER:
      if(wp==TIMER_TOGGLE)finish_toggle();
      else if(wp==TIMER_HIDE){
        KillTimer(window,TIMER_HIDE);refresh_desktop();
        if(enabled && !paused && !toggle_pending && known_desktop && !hidden && !system_icons_disabled()){
          if(GetTickCount64()-last_reveal >= (ULONGLONG)(UINT)seconds*1000u){
            if(!set_icons_visible(0))notice(L"未能隐藏桌面图标，请稍后重试",1);
          }else restart_countdown();
        }
      }else if(wp==TIMER_RECOVER)refresh_desktop();
      else if(wp==TIMER_TRAY)tray_add();
      else if(wp==TIMER_NOTICE){KillTimer(window,TIMER_NOTICE);ui_notice[0]=0;InvalidateRect(window,0,FALSE);}
      return 0;
    case WM_CTLCOLOREDIT:
      SetBkColor((HDC)(UINT_PTR)wp,RGBW(255,255,255));SetTextColor((HDC)(UINT_PTR)wp,RGBW(36,51,41));
      return (LRESULT)(UINT_PTR)white_brush;
    case WM_DPICHANGED:{
      RECT *bounds=(RECT*)(UINT_PTR)lp;dpi=LOWORD(wp);create_fonts();layout_ui();
      SetWindowPos(window,0,bounds->left,bounds->top,bounds->right-bounds->left,bounds->bottom-bounds->top,0x4u|SWP_NOACTIVATE);
      return 0;}
    case WM_CLOSE:
      if(!tray_registered)notice(L"托盘暂不可用，请稍后再关闭窗口",1);
      else ShowWindow(window,SW_HIDE);
      return 0;
    case WM_QUERYENDSESSION:return TRUE;
    case WM_ENDSESSION:if(wp){shutting_down=1;restore_desktop();}return 0;
    case WM_DESTROY:
      shutting_down=1;
      KillTimer(window,TIMER_HIDE);KillTimer(window,TIMER_RECOVER);KillTimer(window,TIMER_NOTICE);KillTimer(window,TIMER_TRAY);
      KillTimer(window,TIMER_TOGGLE);toggle_pending=0;
      if(mouse_hook){UnhookWindowsHookEx(mouse_hook);mouse_hook=0;}
      if(visibility_hook){UnhookWinEvent(visibility_hook);visibility_hook=0;}
      restore_desktop();tray_delete();
      if(remote_hit && !remote_timeout)VirtualFreeEx(desktop_process,remote_hit,0,MEM_RELEASE);
      if(desktop_process)CloseHandle(desktop_process);
      if(regular_font)DeleteObject((HGDIOBJ)regular_font);
      if(section_font)DeleteObject((HGDIOBJ)section_font);
      if(small_font)DeleteObject((HGDIOBJ)small_font);
      if(button_font)DeleteObject((HGDIOBJ)button_font);
      if(white_brush)DeleteObject((HGDIOBJ)white_brush);
      PostQuitMessage(0);return 0;
  }
  return DefWindowProcW(window,msg,wp,lp);
}

void Entry(void) {
  WNDCLASSEXW c={0};RECT r={0};MSG m={0};DWORD last_error;
  HWND window;int x,y,w,h;DWORD style=WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX;
  instance=(HINSTANCE)GetModuleHandleW(0);
  mutex=CreateMutexW(0,0,L"Local\\AutoHideCN_v1_SingleInstance");
  last_error=GetLastError();
  if(mutex && last_error==ERROR_ALREADY_EXISTS){
    HWND existing=FindWindowW(window_class,0);
    if(existing)PostMessageW(existing,MSG_SHOW,0,0);
    CloseHandle(mutex);ExitProcess(0);
  }
  if(!mutex){MessageBoxW(0,L"无法创建程序互斥锁，请稍后重试。",app_name,MB_OK|MB_ICONWARNING);ExitProcess(1);}
  {typedef BOOL (*DPI_CONTEXT)(HANDLE);
    DPI_CONTEXT set_context=(DPI_CONTEXT)GetProcAddress(GetModuleHandleW(L"user32.dll"),"SetProcessDpiAwarenessContext");
    if(set_context)set_context((HANDLE)(INT_PTR)-4);else SetProcessDPIAware();}
  {HDC screen=GetDC(0);if(screen){dpi=(UINT)GetDeviceCaps(screen,LOGPIXELSX);ReleaseDC(0,screen);}if(dpi<96 || dpi>480)dpi=96;}
  {typedef UINT (*SYSTEM_DPI)(void);
    SYSTEM_DPI get_dpi=(SYSTEM_DPI)GetProcAddress(GetModuleHandleW(L"user32.dll"),"GetDpiForSystem");
    if(get_dpi)dpi=get_dpi();}
  load_settings();taskbar_created=RegisterWindowMessageW(L"TaskbarCreated");
  app_icon=LoadIconW(instance,(LPCWSTR)(UINT_PTR)1);
  if(!app_icon)app_icon=LoadIconW(0,IDI_APPLICATION);
  c.cbSize=sizeof(c);c.hInstance=instance;c.lpfnWndProc=window_proc;
  c.lpszClassName=window_class;c.hCursor=LoadCursorW(0,IDC_ARROW);
  c.hIcon=app_icon;c.hIconSm=app_icon;c.hbrBackground=(HBRUSH)(UINT_PTR)(COLOR_WINDOW+1);
  if(!RegisterClassExW(&c)){if(mutex)CloseHandle(mutex);ExitProcess(1);}
  r.right=scale(420);r.bottom=scale(488);
  {typedef BOOL (*ADJUST_DPI)(RECT*,DWORD,BOOL,DWORD,UINT);
    ADJUST_DPI adjust=(ADJUST_DPI)GetProcAddress(GetModuleHandleW(L"user32.dll"),"AdjustWindowRectExForDpi");
    if(adjust)adjust(&r,style,0,0,dpi);else AdjustWindowRectEx(&r,style,0,0);}
  w=r.right-r.left;h=r.bottom-r.top;
  x=(GetSystemMetrics(SM_CXSCREEN)-w)/2;y=(GetSystemMetrics(SM_CYSCREEN)-h)/2;
  window=CreateWindowExW(0,window_class,app_name,style,x,y,w,h,0,0,instance,0);
  if(!window){if(mutex)CloseHandle(mutex);ExitProcess(1);}
  {COLORREF caption=RGBW(248,250,249),caption_text=RGBW(36,51,41);DWORD corner=2;
    DwmSetWindowAttribute(window,35,&caption,sizeof(caption));
    DwmSetWindowAttribute(window,36,&caption_text,sizeof(caption_text));
    DwmSetWindowAttribute(window,33,&corner,sizeof(corner));}
  SetWindowPos(window,always_on_top?HWND_TOPMOST:HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
  if(!start_minimized || !tray_registered){ShowWindow(window,SW_SHOWNORMAL);UpdateWindow(window);SetFocus(enabled_switch);}
  while(GetMessageW(&m,0,0,0)>0){
    if(m.message==WM_KEYDOWN && m.wParam==13){
      if(GetFocus()==enabled_switch || GetFocus()==dblclick_switch || GetFocus()==startup_switch || GetFocus()==topmost_switch || GetFocus()==minimized_switch)
        SendMessageW(main_window,WM_COMMAND,(WPARAM)GetDlgCtrlID(GetFocus()),(LPARAM)(UINT_PTR)GetFocus());
      else SendMessageW(main_window,WM_COMMAND,ID_APPLY,0);
    }else if(!IsDialogMessageW(window,&m)){TranslateMessage(&m);DispatchMessageW(&m);}
  }
  if(mutex)CloseHandle(mutex);
  ExitProcess((UINT)m.wParam);
}


/* Compiler-generated zero initialization helper; no external CRT dependency. */
#if defined(__clang__)
__attribute__((optnone,noinline))
#else
__declspec(noinline)
#endif
void *memset(void *p,int value,unsigned long long count) {
  volatile BYTE *d=(volatile BYTE*)p;
  unsigned long long i;for(i=0;i<count;i++)d[i]=(BYTE)value;
  return p;
}
