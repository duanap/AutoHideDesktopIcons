/* Test-only host: exercise the production WM_DPICHANGED handler without
 * changing monitor settings or adding a test mode to the released EXE. */
#define Entry ApplicationEntry
#include "../AutoHideCN_native.c"
#undef Entry
static LRESULT layout_proc(HWND window,UINT message,WPARAM wp,LPARAM lp){
  if(message==WM_APP+100){
    typedef BOOL (*WINDOW_RECT)(HWND,RECT*);
    WINDOW_RECT get_rect=(WINDOW_RECT)GetProcAddress(GetModuleHandleW(L"user32.dll"),"GetWindowRect");
    RECT outer,client;get_rect(window,&outer);GetClientRect(window,&client);
    int ncx=outer.right-outer.left-client.right,ncy=outer.bottom-outer.top-client.bottom;
    outer.right=outer.left+MulDiv(420,(int)wp,96)+ncx;
    outer.bottom=outer.top+MulDiv(488,(int)wp,96)+ncy;
    LRESULT result=window_proc(window,WM_DPICHANGED,wp|(wp<<16),(LPARAM)(UINT_PTR)&outer);
    UpdateWindow(window);return result;
  }
  return window_proc(window,message,wp,lp);
}
void Entry(void){
  WNDCLASSEXW c={0};RECT bounds={0,0,420,488};MSG message={0};
  instance=GetModuleHandleW(0);enabled=0;double_click_toggle=0;seconds=37;
  SetProcessDPIAware();
  app_icon=LoadIconW(instance,(LPCWSTR)(UINT_PTR)1);taskbar_created=RegisterWindowMessageW(L"TaskbarCreated");
  c.cbSize=sizeof(c);c.hInstance=instance;c.lpfnWndProc=layout_proc;c.lpszClassName=window_class;
  c.hCursor=LoadCursorW(0,IDC_ARROW);c.hIcon=app_icon;c.hIconSm=app_icon;
  RegisterClassExW(&c);DWORD style=WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX;
  AdjustWindowRectEx(&bounds,style,0,0);
  HWND window=CreateWindowExW(0,window_class,app_name,style,60,60,bounds.right-bounds.left,bounds.bottom-bounds.top,0,0,instance,0);
  ShowWindow(window,SW_SHOWNORMAL);UpdateWindow(window);
  while(GetMessageW(&message,0,0,0)>0){if(!IsDialogMessageW(window,&message)){TranslateMessage(&message);DispatchMessageW(&message);}}
  ExitProcess(0);
}
