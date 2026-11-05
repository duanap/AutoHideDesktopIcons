/* Windows integration driver. Only controls this project's test application.
 * Never terminates Explorer or changes the user's system icon preference. */
#ifndef UNICODE
#define UNICODE
#endif
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

static int failures;
static void check(BOOL result,const char *name) {
  printf("%s %s\n",result?"PASS":"FAIL",name);if(!result)failures++;
}
static HWND find_list(void) {
  HWND top=FindWindowW(L"Progman",NULL),view=FindWindowExW(top,NULL,L"SHELLDLL_DefView",NULL);
  if(!view){for(top=FindWindowExW(NULL,NULL,L"WorkerW",NULL);top;top=FindWindowExW(NULL,top,L"WorkerW",NULL)){
    view=FindWindowExW(top,NULL,L"SHELLDLL_DefView",NULL);if(view)break;
  }}
  return view?FindWindowExW(view,NULL,L"SysListView32",NULL):NULL;
}
static void command(HWND window,UINT id){SendMessageW(window,WM_COMMAND,id,0);}
static void toggle(HWND window,UINT id){SendMessageW(window,WM_COMMAND,id,(LPARAM)GetDlgItem(window,(int)id));}
static BOOL wait_visible(HWND list,BOOL visible,DWORD timeout){
  DWORD start=GetTickCount();while(GetTickCount()-start<timeout){if(!!IsWindowVisible(list)==visible)return TRUE;Sleep(40);}return FALSE;
}
static PROCESS_INFORMATION launch(const wchar_t *exe){
  STARTUPINFOW startup={0};PROCESS_INFORMATION process={0};wchar_t cmd[2048];startup.cb=sizeof(startup);
  swprintf(cmd,2048,L"\"%ls\"",exe);check(CreateProcessW(NULL,cmd,NULL,NULL,FALSE,0,NULL,NULL,&startup,&process),"launch");
  if(process.hProcess)WaitForInputIdle(process.hProcess,3000);
  return process;
}
static HWND wait_window(void){
  HWND window=NULL;for(int i=0;i<100&&!window;i++){Sleep(40);window=FindWindowW(L"AutoHideCN.MainWindow.3",NULL);}return window;
}
static void set_dpi(HWND window,UINT dpi){
  SendMessageW(window,WM_APP+100,dpi,0); /* understood only by layout test host */
}
int wmain(int argc,wchar_t **argv){
  SetProcessDPIAware();
  if(argc==3 && !wcscmp(argv[1],L"--dpi")){
    HWND window=FindWindowW(L"AutoHideCN.MainWindow.3",NULL);
    if(window)set_dpi(window,(UINT)_wtoi(argv[2]));
    return 0;
  }
  if(argc==2 && !wcscmp(argv[1],L"--layout")){
    HWND window=FindWindowW(L"AutoHideCN.MainWindow.3",NULL);DWORD pid;
    if(!window)return 3;
    GetWindowThreadProcessId(window,&pid);HANDLE process=OpenProcess(PROCESS_QUERY_INFORMATION,FALSE,pid);
    DWORD before=0;
    UINT scales[]={96,120,144,168,192};
    for(int loop=0;loop<20;loop++)for(int s=0;s<5;s++){
      set_dpi(window,scales[s]);RECT client;GetClientRect(window,&client);
      BOOL inside=TRUE,disjoint=TRUE;RECT boxes[7];
      for(int id=101;id<=107;id++){
        HWND child=GetDlgItem(window,id);RECT *box=&boxes[id-101];GetWindowRect(child,box);
        MapWindowPoints(NULL,window,(POINT*)box,2);
        if(box->left<0||box->top<0||box->right>client.right||box->bottom>client.bottom)inside=FALSE;
        for(int prior=101;prior<id;prior++){RECT overlap;if(IntersectRect(&overlap,box,&boxes[prior-101]))disjoint=FALSE;}
      }
      if(loop==0){char label[100];snprintf(label,sizeof(label),"%u DPI children inside client and disjoint",scales[s]);check(inside&&disjoint,label);}
      if(loop==0 && s==4)before=GetGuiResources(process,GR_GDIOBJECTS);
    }
    set_dpi(window,192);DWORD after=GetGuiResources(process,GR_GDIOBJECTS);
    printf("GDI before=%lu after=%lu\n",before,after);check(after<=before+2,"repeated DPI changes keep GDI stable");
    CloseHandle(process);return failures?1:0;
  }
  if(argc==2 && !wcscmp(argv[1],L"--inspect")){
    HWND app=FindWindowW(L"AutoHideCN.MainWindow.3",NULL);
    if(app)printf("actual window DPI=%u\n",GetDpiForWindow(app));
    HWND list=find_list();
    for(HWND w=list;w;w=GetParent(w)){
      wchar_t name[100];GetClassNameW(w,name,100);
      printf("%ls visible=%d own-visible=%d style=%llx\n",name,IsWindowVisible(w),!!(GetWindowLongPtrW(w,GWL_STYLE)&WS_VISIBLE),(unsigned long long)GetWindowLongPtrW(w,GWL_STYLE));
    }
    return 0;
  }
  if(argc==2 && !wcscmp(argv[1],L"--close")){
    HWND window=FindWindowW(L"AutoHideCN.MainWindow.3",NULL);
    if(window)command(window,304);
    return 0;
  }
  if(argc!=3){fprintf(stderr,"runtime.exe <exe> <ini> | --close\n");return 2;}
  HWND list=find_list();BOOL initially=list&&IsWindowVisible(list);
  check(list!=NULL,"desktop list located");
  if(!list)return 77;
  if(!initially)ShowWindow(list,SW_SHOWNA);
  PROCESS_INFORMATION process=launch(argv[1]);HWND window=wait_window();check(window!=NULL,"settings window created");
  if(!window)return 3;
  wchar_t loaded[20]={0};SendMessageW(GetDlgItem(window,102),WM_GETTEXT,20,(LPARAM)loaded);
  check(!wcscmp(loaded,L"2"),"legacy custom seconds loaded without default overwrite");
  check(wait_visible(list,FALSE,4000),"automatic countdown hides real desktop");
  command(window,302);check(wait_visible(list,TRUE,1500),"tray show reveals real desktop");
  Sleep(600);check(IsWindowVisible(list),"reveal restarts countdown");
  check(wait_visible(list,FALSE,2600),"new countdown hides again");
  command(window,303);command(window,302);Sleep(2600);
  check(IsWindowVisible(list),"tray pause stops auto hide");
  command(window,303);check(wait_visible(list,FALSE,3500),"tray resume starts countdown");
  command(window,302);
  HWND edit=GetDlgItem(window,102);SendMessageW(edit,WM_SETTEXT,0,(LPARAM)L"0");command(window,107);
  check(GetPrivateProfileIntW(L"Config",L"seconds",0,argv[2])==2,"invalid setting does not save");
  SendMessageW(edit,WM_SETTEXT,0,(LPARAM)L"7");
  wchar_t entered[20]={0};SendMessageW(edit,WM_GETTEXT,20,(LPARAM)entered);
  check(!wcscmp(entered,L"7"),"new seconds entered into edit");
  check(GetPrivateProfileIntW(L"Config",L"seconds",0,argv[2])==2,"edits remain staged before save");
  command(window,107);
  check(GetPrivateProfileIntW(L"Config",L"seconds",0,argv[2])==7,"save persists new seconds");
  check(GetPrivateProfileIntW(L"Config",L"obsolete_test",-1,argv[2])==(UINT)-1,"save cleans retired Config keys");
  toggle(window,106);command(window,107);
  check((GetWindowLongPtrW(window,GWL_EXSTYLE)&WS_EX_TOPMOST)!=0,"saved topmost applies");
  toggle(window,106);command(window,107);
  check((GetWindowLongPtrW(window,GWL_EXSTYLE)&WS_EX_TOPMOST)==0,"topmost can be disabled");
  HKEY run;BOOL startup_exists=FALSE;
  if(RegOpenKeyExW(HKEY_CURRENT_USER,L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_QUERY_VALUE,&run)==ERROR_SUCCESS){
    startup_exists=RegQueryValueExW(run,L"AutoHideCN",NULL,NULL,NULL,NULL)==ERROR_SUCCESS;RegCloseKey(run);
  }
  if(!startup_exists){
    toggle(window,104);command(window,107);wchar_t startup_command[2048]={0};DWORD bytes=sizeof(startup_command);
    if(RegOpenKeyExW(HKEY_CURRENT_USER,L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_QUERY_VALUE,&run)==ERROR_SUCCESS){
      RegQueryValueExW(run,L"AutoHideCN",NULL,NULL,(BYTE*)startup_command,&bytes);RegCloseKey(run);
    }
    check(startup_command[0]==L'"' && wcsstr(startup_command,argv[1])!=NULL,"startup command quotes current executable");
    toggle(window,104);command(window,107);
    BOOL removed=FALSE;
    if(RegOpenKeyExW(HKEY_CURRENT_USER,L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_QUERY_VALUE,&run)==ERROR_SUCCESS){
      removed=RegQueryValueExW(run,L"AutoHideCN",NULL,NULL,NULL,NULL)==ERROR_FILE_NOT_FOUND;RegCloseKey(run);
    }
    check(removed,"startup entry removed after disabling");
  }else printf("SKIP preexisting startup entry left unchanged\n");
  SendMessageW(window,WM_CLOSE,0,0);Sleep(100);
  check(!IsWindowVisible(window)&&WaitForSingleObject(process.hProcess,0)==WAIT_TIMEOUT,"close keeps background process alive");
  PROCESS_INFORMATION duplicate=launch(argv[1]);
  check(WaitForSingleObject(duplicate.hProcess,3000)==WAIT_OBJECT_0,"duplicate instance exits");
  Sleep(150);check(IsWindowVisible(window),"duplicate launch reopens settings");
  CloseHandle(duplicate.hThread);CloseHandle(duplicate.hProcess);
  command(window,301);check(wait_visible(list,FALSE,1000),"tray hide hides desktop");
  command(window,304);
  check(WaitForSingleObject(process.hProcess,3000)==WAIT_OBJECT_0,"normal exit completes");
  check(wait_visible(list,TRUE,1000),"normal exit restores owned hide");
  CloseHandle(process.hThread);CloseHandle(process.hProcess);
  /* Simulate an initially hidden list without changing the native registry setting. */
  ShowWindow(list,SW_HIDE);
  process=launch(argv[1]);window=wait_window();Sleep(250);command(window,304);
  check(WaitForSingleObject(process.hProcess,3000)==WAIT_OBJECT_0,"initially hidden exit completes");
  check(!IsWindowVisible(list),"initially hidden desktop stays hidden on exit");
  ShowWindow(list,SW_SHOWNA); /* restore test-owned change unconditionally */
  CloseHandle(process.hThread);CloseHandle(process.hProcess);
  process=launch(argv[1]);window=wait_window();toggle(window,105);command(window,107);command(window,304);
  WaitForSingleObject(process.hProcess,3000);CloseHandle(process.hThread);CloseHandle(process.hProcess);
  process=launch(argv[1]);window=wait_window();Sleep(200);
  check(!IsWindowVisible(window),"saved start-in-tray hides initial settings window");
  command(window,300);check(IsWindowVisible(window),"tray open restores settings window");
  command(window,301);check(wait_visible(list,FALSE,1000),"session-end test owns hide");
  SendMessageW(window,WM_CLOSE,0,0); /* measure actual tray-only operation */
  FILETIME created,ended,kernel0,user0,kernel1,user1;
  GetProcessTimes(process.hProcess,&created,&ended,&kernel0,&user0);Sleep(4000);
  GetProcessTimes(process.hProcess,&created,&ended,&kernel1,&user1);
  ULARGE_INTEGER k0={.LowPart=kernel0.dwLowDateTime,.HighPart=kernel0.dwHighDateTime};
  ULARGE_INTEGER k1={.LowPart=kernel1.dwLowDateTime,.HighPart=kernel1.dwHighDateTime};
  ULARGE_INTEGER u0={.LowPart=user0.dwLowDateTime,.HighPart=user0.dwHighDateTime};
  ULARGE_INTEGER u1={.LowPart=user1.dwLowDateTime,.HighPart=user1.dwHighDateTime};
  double cpu=(double)(k1.QuadPart-k0.QuadPart+u1.QuadPart-u0.QuadPart)/10000000.0;
  printf("Background CPU seconds over 4 seconds: %.6f\n",cpu);
  check(cpu<0.10,"background CPU remains low in short idle sample");
  check(SendMessageW(window,WM_QUERYENDSESSION,0,0)==TRUE,"session end query accepted");
  SendMessageW(window,WM_ENDSESSION,TRUE,0);
  check(wait_visible(list,TRUE,1000),"simulated session end restores owned hide");
  command(window,304);WaitForSingleObject(process.hProcess,3000);CloseHandle(process.hThread);CloseHandle(process.hProcess);
  if(!initially)ShowWindow(list,SW_HIDE);
  printf("Failures: %d\n",failures);return failures?1:0;
}
