"""Package v1.4.1; excludes personal settings and test executables."""
from pathlib import Path
from zipfile import ZipFile, ZIP_DEFLATED
import hashlib

VERSION = '1.4.1'
root = Path(__file__).resolve().parent
out = root / 'dist'
out.mkdir(exist_ok=True)
sha = hashlib.sha256((root/'AutoHideCN.exe').read_bytes()).hexdigest()
(root/'SHA256SUMS.txt').write_text(f'{sha}  AutoHideCN.exe\n', encoding='utf-8')
docs = ['README.md', 'CHANGELOG.md', 'TEST-RESULTS.md', 'SHA256SUMS.txt']
sources = ['AutoHideCN_native.c', 'AutoHideCN.ico', 'AutoHideCN.res', 'AutoHideCN.manifest',
           'make_icon.py', 'build_icon_res.py', 'build-linux.sh', 'build-windows.cmd', 'release.py',
           'kernel32.def', 'user32.def', 'gdi32.def', 'shell32.def', 'advapi32.def', 'dwmapi.def',
           '.gitignore', 'tests/core.c', 'tests/runtime.c', 'tests/layout.c', 'tests/run-windows.ps1']
for label, files, prefix in [('中文便携版', ['AutoHideCN.exe']+docs, ''),
                            ('完整源码', ['AutoHideCN.exe']+docs+sources, f'AutoHideCN_v{VERSION}/')]:
    target = out/f'AutoHideCN_v{VERSION}_{label}.zip'
    with ZipFile(target, 'w', ZIP_DEFLATED, compresslevel=9) as archive:
        for name in files:
            archive.write(root/name, prefix+name)
    with ZipFile(target) as archive:
        assert archive.testzip() is None
        assert not any(n.endswith('.ini') for n in archive.namelist())
    print(target.name, target.stat().st_size, 'bytes')
print('EXE SHA256:', sha)
