$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
Set-Location -LiteralPath $projectRoot
if (Get-Process AutoHideCN,layout -ErrorAction SilentlyContinue) {
    throw '请先退出正在运行的 AutoHideCN 或布局测试程序。'
}
function Invoke-Wsl {
    param([string[]]$Arguments)
    & wsl.exe -d Debian -- @Arguments
    if ($LASTEXITCODE -ne 0) { throw "WSL 命令失败：$($Arguments[0])" }
}
Invoke-Wsl -Arguments @('sh','build-linux.sh')
Invoke-Wsl -Arguments @('clang','-target','x86_64-pc-windows-msvc','-std=c11','-Wall','-Wextra','-Werror','-fno-builtin','--analyze','AutoHideCN_native.c','-o','build/analysis.plist')
Invoke-Wsl -Arguments @('x86_64-w64-mingw32-gcc','-std=c11','-O2','-Wall','-Wextra','-Werror','tests/core.c','-o','build/core.exe','-luser32','-lgdi32','-lshell32','-ladvapi32','-ldwmapi')
Invoke-Wsl -Arguments @('x86_64-w64-mingw32-gcc','-std=c11','-O2','-Wall','-Wextra','-Werror','-municode','tests/runtime.c','-o','build/runtime.exe','-luser32','-ladvapi32')
Invoke-Wsl -Arguments @('clang','-target','x86_64-pc-windows-msvc','-std=c11','-O2','-Wall','-Wextra','-Werror','-fno-builtin','-fno-stack-protector','-c','tests/layout.c','-o','build/layout.obj')
Invoke-Wsl -Arguments @('lld-link','/subsystem:windows','/entry:Entry','/nodefaultlib','/machine:x64','/opt:ref','/opt:icf','/out:build/layout.exe','build/layout.obj','AutoHideCN.res','build/kernel32.lib','build/user32.lib','build/gdi32.lib','build/shell32.lib','build/advapi32.lib','build/dwmapi.lib')
& .\build\core.exe | Tee-Object -FilePath build\core-results.txt
if ($LASTEXITCODE -ne 0) { throw '核心测试失败。' }
$testFolder = Join-Path $projectRoot 'build\runtime-test'
New-Item -ItemType Directory -Path $testFolder -Force | Out-Null
Copy-Item -LiteralPath AutoHideCN.exe -Destination (Join-Path $testFolder 'AutoHideCN.exe') -Force
$testIni = Join-Path $testFolder 'AutoHideCN.ini'
Set-Content -LiteralPath $testIni -Encoding ascii -Value "[Config]`nenabled=1`nseconds=2`ndouble_click_toggle=1`nstart_minimized=0`nalways_on_top=0`nobsolete_test=1"
$startupKey = 'HKCU:\Software\Microsoft\Windows\CurrentVersion\Run'
$startupBackup = Get-ItemProperty -LiteralPath $startupKey -Name AutoHideCN -ErrorAction SilentlyContinue
$hadStartup = $null -ne $startupBackup
try {
    & .\build\runtime.exe (Join-Path $testFolder 'AutoHideCN.exe') $testIni | Tee-Object -FilePath build\runtime-results.txt
    if ($LASTEXITCODE -ne 0) { throw '实机回归测试失败。' }
    $layoutProcess = Start-Process -FilePath (Join-Path $projectRoot 'build\layout.exe') -PassThru
    for ($attempt=0; $attempt -lt 50; $attempt++) {
        $layoutProcess.Refresh()
        if ($layoutProcess.MainWindowHandle -ne 0) { break }
        Start-Sleep -Milliseconds 100
    }
    & .\build\runtime.exe --layout | Tee-Object -FilePath build\layout-results.txt
    if ($LASTEXITCODE -ne 0) { throw 'DPI 布局测试失败。' }
} finally {
    & .\build\runtime.exe --close
    if ($hadStartup) {
        Set-ItemProperty -LiteralPath $startupKey -Name AutoHideCN -Value $startupBackup.AutoHideCN
    } else {
        Remove-ItemProperty -LiteralPath $startupKey -Name AutoHideCN -ErrorAction SilentlyContinue
    }
}
Write-Output '全部可执行测试通过，详细输出见 build 目录。'
