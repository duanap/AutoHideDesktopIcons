@echo off
setlocal
cd /d "%~dp0"
where cl.exe >nul 2>nul
if errorlevel 1 (
  echo [ERROR] Run this script from "x64 Native Tools Command Prompt for VS".
  exit /b 1
)
if not exist build mkdir build
python --version >nul 2>nul
if not errorlevel 1 (
  python build_icon_res.py
  if errorlevel 1 exit /b 1
)
cl /nologo /TC /std:c11 /utf-8 /W4 /WX /wd4100 /wd4055 /wd4054 /O2 /GS- /c AutoHideCN_native.c /Fo:build\AutoHideCN.obj
if errorlevel 1 exit /b 1
link /nologo /SUBSYSTEM:WINDOWS /ENTRY:Entry /NODEFAULTLIB /MACHINE:X64 /OPT:REF /OPT:ICF /MANIFEST:NO /OUT:AutoHideCN.exe build\AutoHideCN.obj AutoHideCN.res kernel32.lib user32.lib gdi32.lib shell32.lib advapi32.lib dwmapi.lib
if errorlevel 1 exit /b 1
echo [OK] AutoHideCN.exe
endlocal
