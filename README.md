# AutoHideCN v1.4.1

轻量的 Windows 桌面图标自动隐藏工具。采用 C11 和原生 Win32 API，支持 Windows 10／11 x64，单个 EXE 即可运行，无需安装运行库、数据库或后台服务。

请勿与 AutoHideDesktopIcons 等其他桌面图标隐藏工具同时运行，它们会同时修改图标可见性并干扰双击切换。

## 使用

1. 将 `AutoHideCN.exe` 放入固定目录后运行。
2. 设置自动隐藏时间和双击开关，点击「保存设置」统一生效。
3. 关闭设置窗口后，程序继续在系统托盘运行。
4. 双击托盘图标打开设置，右键菜单可以显示／隐藏图标、暂停／恢复自动隐藏和退出程序。

自动隐藏和双击切换默认开启。新配置的隐藏时间为 **5 秒**，允许输入 **1～10800** 的整数。设置修改前不会影响正在运行的配置；保存后重新开始倒计时。无效输入显示中文提示，保存成功显示「设置已保存」，均不弹出确认窗口。

双击桌面空白处切换图标显示状态，显示后重新计时。桌面图标、快捷方式、任务栏和其他应用窗口不属于触发区域。连续三击、四击只切换一次，需要间隔一个系统双击时间或移出判定范围后再开始下一次双击。关闭自动隐藏后仍可双击切换；关闭双击开关后自动隐藏仍可运行。

「暂停自动隐藏」只影响本次运行的计时，不写入配置，也不强制显示已隐藏的图标。保存设置或重启程序后恢复所保存的自动隐藏设置。

## 桌面状态与退出

请通过托盘「退出程序」正常退出。程序只恢复由自己隐藏、且当前仍隐藏的图标。启动前就隐藏的图标会保持隐藏；用户在 Windows 中关闭「显示桌面图标」时，程序不会在退出时覆盖这项偏好。托盘「显示桌面图标」也会尊重这项系统设置。

支持注销／关机通知、Explorer 窗口重新定位和托盘图标重新注册。重复启动会打开已有设置窗口。强制结束进程、系统崩溃或断电无法执行恢复逻辑；此时可通过 Windows 桌面右键「查看 → 显示桌面图标」恢复。

## 配置与升级

沿用 INI 文件和 `[Config]` 分组：

```ini
[Config]
enabled=1
seconds=5
double_click_toggle=1
start_minimized=0
always_on_top=0
```

- 优先读取有效的已有秒数，升级不会直接覆盖为 5 秒。
- 支持 EXE 同目录的 `AutoHideCN.ini` 和 `%APPDATA%\AutoHideCN\AutoHideCN.ini`。两者都有有效配置时读取最近保存的一份；只有一份秒数有效时优先使用它。
- 首次保存尝试写入 EXE 所在目录，目录不可写时回退到用户配置目录。下次启动继续读取最新配置。
- 使用临时文件和原子替换保存；失败时显示错误，运行设置不提交。其他 INI 分组保留，保存时清理 `[Config]` 中的废弃键。
- 开机启动记录在当前用户的 Windows「运行」注册表项中。移动 EXE 后应重新保存设置以更新启动路径。「启动后隐藏至托盘」同时用于手动启动和开机启动。

## 源码结构

| 文件 | 用途 |
| --- | --- |
| `AutoHideCN_native.c` | 界面、桌面命中、鼠标钩子、计时、配置和托盘 |
| `AutoHideCN.manifest` | Per-Monitor V2 DPI、版本和普通用户权限 |
| `build_icon_res.py` | 图标、清单与 1.4.1 版本资源；仅使用 Python 标准库 |
| `build-linux.sh`／`build-windows.cmd` | 原有构建入口，已更新 |
| `tests/` | 核心逻辑、实机生命周期和 DPI 布局测试 |
| `TEST-RESULTS.md` | 本次实际验证结果与未验证项目 |

`make_icon.py` 仅在重新设计图标时需要 Pillow，正常构建使用已有 ICO。程序运行不依赖 Python 或 Pillow。

## 构建

推荐使用本次实际验证的 Linux／WSL 构建入口，需要 `clang`、`lld-link`、Python 3：

```sh
sh build-linux.sh
```

脚本生成 x64 Windows GUI EXE，开启 `-Wall -Wextra -Werror`，不链接 C／C++ 运行库。使用 `.def` 生成 Windows 系统导入库，不需要 Windows SDK。

也可在 Visual Studio 的 **x64 Native Tools Command Prompt** 中运行 `build-windows.cmd`。脚本有可用 Python 时重建资源，否则使用源码包内的 `.res`。此 MSVC 构建路径本次未实测。

Windows 实机回归测试需要 WSL Debian 中的上述工具及 `x86_64-w64-mingw32-gcc`：

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-windows.ps1
```

运行前退出已有 AutoHideCN。测试会短暂显示／隐藏桌面图标，结束时还原测试前的可见状态。不会重启 Explorer、注销 Windows 或修改系统显示缩放。测试程序使用的运行库只用于测试，不进入发布 EXE。

重新打包：

```sh
python3 release.py
```

输出位于 `dist/`，包括中文便携包和完整源码包，不包含个人配置和测试生成的可执行文件。独立实现，不包含 SoftwareOK 原版代码或资源。
