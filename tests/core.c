/* Exercise the shipped parser, click tracker and atomic INI writer on Windows. */
#include <stdio.h>
#define Entry ApplicationEntry
#include "../AutoHideCN_native.c"
#undef Entry
API BOOL SetEnvironmentVariableW(LPCWSTR,LPCWSTR);
static int failures,checks;
static void expect(int result,const char *description){checks++;if(!result){failures++;printf("FAIL %s\n",description);}}
static void reset_clicks(void){click_pending=click_released=click_burst=click_ready=0;}
static LRESULT fake_desktop_proc(HWND window,UINT msg,WPARAM wp,LPARAM lp){
  if(msg==LVM_HITTEST){LVHITTESTINFO *hit=(LVHITTESTINFO*)(UINT_PTR)lp;hit->flags=1;hit->iItem=-1;return -1;}
  if(msg==WM_TIMER && wp==TIMER_TOGGLE){finish_toggle();return 0;}
  return DefWindowProcW(window,msg,wp,lp);
}
static void gesture(UINT msg,POINT point,DWORD time){
  on_mouse(((WPARAM)time<<32)|msg,(LPARAM)(((ULONGLONG)(DWORD)point.y<<32)|(DWORD)point.x));
}
static void gesture_pair(POINT point,DWORD time){
  gesture(WM_LBUTTONDOWN,point,time);gesture(WM_LBUTTONUP,point,time+10);
  gesture(WM_LBUTTONDOWN,point,time+20);gesture(WM_LBUTTONUP,point,time+30);
}
int main(void){
  SetProcessDPIAware();
  POINT p={100,100},far={1000,1000};DWORD dt=GetDoubleClickTime();
  expect(parse_seconds(L"1")==1,"minimum seconds");
  expect(parse_seconds(L"10800")==10800,"maximum seconds");
  expect(parse_seconds(L"37")==37,"legacy custom seconds");
  expect(parse_seconds(L"")==-1,"empty rejected");
  expect(parse_seconds(L"0")==-1,"zero rejected");
  expect(parse_seconds(L"10801")==-1,"out of range rejected");
  expect(parse_seconds(L"99999999999999999999")==-1,"overflow rejected");
  expect(parse_seconds(L"1.5")==-1,"decimal rejected");
  expect(parse_seconds(L"-1")==-1,"negative rejected");
  expect(parse_seconds(L"5x")==-1,"trailing text rejected");
  expect(!digits_only(L"ab")&&!digits_only(L"1\n2")&&digits_only(L"10800"),"character validation");
  reset_clicks();
  expect(!register_click(WM_LBUTTONDOWN,p,1000,1),"single down");
  register_click(WM_LBUTTONUP,p,1010,0);
  expect(!register_click(WM_LBUTTONDOWN,p,1020,1),"second down must not hide before Explorer releases");
  expect(register_click(WM_LBUTTONUP,p,1030,1),"valid double click commits on second release");
  expect(!register_click(WM_LBUTTONUP,p,1031,1),"duplicate release does not toggle again");
  expect(!register_click(WM_LBUTTONDOWN,p,1040,1),"triple consumed");
  register_click(WM_LBUTTONUP,p,1050,0);
  expect(!register_click(WM_LBUTTONDOWN,p,1060,1),"quadruple consumed");
  register_click(WM_LBUTTONUP,p,1070,0);
  expect(!register_click(WM_LBUTTONDOWN,p,1060+dt+1,1),"new burst begins");
  register_click(WM_LBUTTONUP,p,1060+dt+2,0);
  expect(!register_click(WM_LBUTTONDOWN,p,1060+dt+3,1),"next separated pair waits for release");
  expect(register_click(WM_LBUTTONUP,p,1060+dt+4,1),"next separated pair fires on release");
  reset_clicks();register_click(WM_LBUTTONDOWN,p,1000,1);register_click(WM_LBUTTONUP,p,1010,0);
  expect(!register_click(WM_LBUTTONDOWN,far,1020,1),"distant second click rejected");
  reset_clicks();register_click(WM_LBUTTONDOWN,p,1000,1);register_click(WM_LBUTTONUP,far,1010,0);
  expect(!register_click(WM_LBUTTONDOWN,p,1020,1),"drag rejected");
  reset_clicks();register_click(WM_LBUTTONDOWN,p,1000,1);register_click(WM_LBUTTONUP,p,1010,0);
  expect(!register_click(WM_LBUTTONDOWN,p,1020,0),"icon/application second click rejected");
  expect(!register_click(WM_LBUTTONDOWN,p,1030,1),"invalid click breaks pair");
  reset_clicks();register_click(WM_LBUTTONDOWN,p,0xfffffff0u,1);register_click(WM_LBUTTONUP,p,0xfffffff1u,0);
  expect(!register_click(WM_LBUTTONDOWN,p,4,1) && register_click(WM_LBUTTONUP,p,5,1),"timestamp wraparound");
  reset_clicks();register_click(WM_LBUTTONDOWN,p,1000,1);register_click(WM_LBUTTONUP,p,1010,1);
  register_click(WM_LBUTTONDOWN,p,1020,1);
  expect(!register_click(WM_LBUTTONUP,far,1030,1),"second-click drag cancels toggle");
  reset_clicks();register_click(WM_LBUTTONDOWN,p,1000,1);register_click(WM_LBUTTONUP,p,1010,1);
  register_click(WM_LBUTTONDOWN,p,1020,1);
  expect(!register_click(WM_LBUTTONUP,p,1030,0),"release over another window cancels toggle");
  reset_clicks();register_click(WM_LBUTTONDOWN,p,1000,1);
  expect(!register_click(WM_LBUTTONDOWN,p,1010,1),"two downs without release rejected");
  WCHAR path[1024];exe_folder(path,COUNT(path));path_append(path,COUNT(path),L"core-test.ini");
  WritePrivateProfileStringW(L"Other",L"keep",L"42",path);
  WritePrivateProfileStringW(config_section,L"old_mouse_button",L"2",path);
  expect(write_settings_at(path,37,1,0,0,1),"atomic config write");
  expect(GetPrivateProfileIntW(config_section,L"seconds",0,path)==37,"custom seconds saved");
  expect(GetPrivateProfileIntW(L"Other",L"keep",0,path)==42,"other section preserved");
  expect(GetPrivateProfileIntW(config_section,L"old_mouse_button",-1,path)==(UINT)-1,"retired key cleaned");
  WCHAR fallback[1024];exe_folder(fallback,COUNT(fallback));path_append(fallback,COUNT(fallback),L"core-fallback.ini");
  SetFileAttributesW(path,1);
  expect(!write_settings_at(path,38,1,0,0,1),"read-only destination reports failure");
  expect(write_settings_from(fallback,path,38,1,0,0,1),"read-only source can seed writable fallback");
  expect(GetPrivateProfileIntW(config_section,L"seconds",0,fallback)==38,"fallback stores new value");
  expect(GetPrivateProfileIntW(L"Other",L"keep",0,fallback)==42,"fallback preserves other sections");
  SetFileAttributesW(path,0x80);DeleteFileW(fallback);
  expect(!write_settings_at(L".\\build\\missing-directory\\test.ini",5,1,1,0,0),"write failure reported");
  DeleteFileW(path);
  WCHAR old_appdata[1024],profile[1024],portable[1024],roaming[1024];
  GetEnvironmentVariableW(L"APPDATA",old_appdata,COUNT(old_appdata));
  exe_folder(profile,COUNT(profile));path_append(profile,COUNT(profile),L"test-profile");CreateDirectoryW(profile,0);
  SetEnvironmentVariableW(L"APPDATA",profile);
  exe_folder(portable,COUNT(portable));path_append(portable,COUNT(portable),L"AutoHideCN.ini");appdata_file(roaming,COUNT(roaming),1);
  WritePrivateProfileStringW(config_section,L"seconds",L"37",portable);
  WritePrivateProfileStringW(config_section,L"seconds",L"invalid",roaming);locate_settings();
  expect(weq(ini_file,portable),"valid portable custom seconds beat invalid roaming config");
  WritePrivateProfileStringW(config_section,L"seconds",L"invalid",portable);
  WritePrivateProfileStringW(config_section,L"seconds",L"61",roaming);locate_settings();
  expect(weq(ini_file,roaming),"valid roaming custom seconds beat invalid portable config");
  SetEnvironmentVariableW(L"APPDATA",old_appdata);DeleteFileW(portable);DeleteFileW(roaming);
  /* Query the actual Explorer list without changing its visibility. */
  enabled=0;
  expect(locate_desktop(),"real Explorer desktop located");
  if(desktop_list){
    typedef int (*MAP_POINTS)(HWND,HWND,POINT*,UINT);
    typedef BOOL (*WINDOW_RECT)(HWND,RECT*);
    MAP_POINTS map=(MAP_POINTS)GetProcAddress(GetModuleHandleW(L"user32.dll"),"MapWindowPoints");
    WINDOW_RECT window_rect=(WINDOW_RECT)GetProcAddress(GetModuleHandleW(L"user32.dll"),"GetWindowRect");
    RECT bounds;GetClientRect(desktop_list,&bounds);BOOL blank_found=0;
    for(int y=20;y<bounds.bottom&&!blank_found;y+=80)for(int x=20;x<bounds.right&&!blank_found;x+=80){
      POINT candidate={x,y};map(desktop_list,0,&candidate,1);blank_found=list_blank_at(candidate);
    }
    expect(blank_found,"remote hit test recognizes desktop whitespace");
    if(remote_hit && !remote_timeout){
      RECT icon={1,0,0,0};ULONG_PTR result=0;
      WriteProcessMemory(desktop_process,remote_hit,&icon,sizeof(icon),0);
      if(SendMessageTimeoutW(desktop_list,0x100eu,0,(LPARAM)(UINT_PTR)remote_hit,SMTO_BLOCK|SMTO_ABORTIFHUNG,100,&result) && result){
        ReadProcessMemory(desktop_process,remote_hit,&icon,sizeof(icon),0);
        POINT center={(icon.left+icon.right)/2,(icon.top+icon.bottom)/2};map(desktop_list,0,&center,1);
        expect(!list_blank_at(center),"remote hit test excludes real desktop icon");
      }else printf("SKIP no first desktop icon rectangle\n");
    }
    HWND overlay=CreateWindowExW(0,L"STATIC",L"自动隐藏测试",WS_VISIBLE|WS_CAPTION,80,80,180,100,0,0,GetModuleHandleW(0),0);
    RECT area;window_rect(overlay,&area);POINT covered={area.left+30,area.top+50};
    expect(!desktop_click_at(covered),"ordinary application window excluded");DestroyWindow(overlay);
    HWND taskbar=FindWindowW(L"Shell_TrayWnd",0);
    if(taskbar){window_rect(taskbar,&area);POINT point={(area.left+area.right)/2,(area.top+area.bottom)/2};expect(!desktop_click_at(point),"taskbar and tray excluded");}
    if(remote_hit && !remote_timeout)VirtualFreeEx(desktop_process,remote_hit,0,MEM_RELEASE);
    if(desktop_process)CloseHandle(desktop_process);
    remote_hit=0;desktop_process=0;remote_timeout=0;
  }
  if(visibility_hook){UnhookWinEvent(visibility_hook);visibility_hook=0;}
  /* Reproduce the late Explorer show/focus operation on a test-owned desktop.
   * The real desktop and the user's input are untouched by this race fixture. */
  WNDCLASSEXW cls={0};cls.cbSize=sizeof(cls);cls.hInstance=GetModuleHandleW(0);
  cls.lpfnWndProc=fake_desktop_proc;cls.lpszClassName=L"AutoHideCN.GestureFixture";RegisterClassExW(&cls);
  HWND fixture=CreateWindowExW(8,cls.lpszClassName,L"",WS_VISIBLE,80,80,180,120,0,0,cls.hInstance,0);
  HWND icons=CreateWindowExW(0,cls.lpszClassName,L"",WS_CHILD|WS_VISIBLE,0,0,180,120,fixture,0,cls.hInstance,0);
  desktop_list=icons;desktop_root=desktop_view=main_window=fixture;
  known_desktop=1;hidden=0;owned_hidden=0;double_click_toggle=1;enabled=0;
  POINT target={130,130};reset_clicks();
  gesture(WM_LBUTTONDOWN,target,1000);gesture(WM_LBUTTONUP,target,1010);gesture(WM_LBUTTONDOWN,target,1020);
  expect(IsWindowVisible(icons) && !toggle_pending,"second down leaves native mouse target visible");
  gesture(WM_LBUTTONUP,target,1030);
  expect(toggle_pending && IsWindowVisible(icons),"release queues hide instead of racing native click");
  gesture(WM_LBUTTONDOWN,target,1040);finish_toggle();
  expect(toggle_pending && IsWindowVisible(icons),"rapid third down delays hide until native gesture ends");
  gesture(WM_LBUTTONUP,target,1050);
  ShowWindow(icons,SW_SHOWNA); /* Explorer completing its original click */
  finish_toggle();
  expect(!IsWindowVisible(icons) && owned_hidden,"deferred hide survives late native show");
  refresh_desktop();finish_toggle();
  expect(!IsWindowVisible(icons),"queued notifications cannot toggle hidden icons back");
  reset_clicks();gesture_pair(target,2000);finish_toggle();
  expect(IsWindowVisible(icons),"next completed double click reveals icons");
  reset_clicks();gesture_pair(target,3000);finish_toggle();
  expect(!IsWindowVisible(icons),"following completed double click hides again");
  reset_clicks();gesture_pair(target,4000);double_click_toggle=0;finish_toggle();
  expect(!IsWindowVisible(icons),"disabling double click cancels deferred operation");
  if(remote_hit && !remote_timeout)VirtualFreeEx(desktop_process,remote_hit,0,MEM_RELEASE);
  if(desktop_process)CloseHandle(desktop_process);
  KillTimer(fixture,TIMER_TOGGLE);DestroyWindow(fixture);
  printf("Core checks: %d, failures: %d\n",checks,failures);return failures?1:0;
}
