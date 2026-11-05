#!/bin/sh
set -eu
cd "$(dirname "$0")"
command -v clang >/dev/null || { echo "需要 clang 编译器"; exit 1; }
command -v lld-link >/dev/null || { echo "需要 lld-link 链接器"; exit 1; }
python3 build_icon_res.py
mkdir -p build
for name in kernel32 user32 gdi32 shell32 advapi32 dwmapi; do
    lld-link /lib /machine:x64 /def:"$name.def" /out:"build/$name.lib"
done
clang -target x86_64-pc-windows-msvc -std=c11 -O2 -Wall -Wextra -Werror -fno-builtin -fno-stack-protector -c AutoHideCN_native.c -o build/AutoHideCN.obj
lld-link /subsystem:windows /entry:Entry /nodefaultlib /machine:x64 /opt:ref /opt:icf /out:AutoHideCN.exe build/AutoHideCN.obj AutoHideCN.res build/kernel32.lib build/user32.lib build/gdi32.lib build/shell32.lib build/advapi32.lib build/dwmapi.lib
echo '已生成：AutoHideCN.exe'
