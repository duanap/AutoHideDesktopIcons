"""Generate standard Win32 ICO icon resources without the Windows SDK."""
import struct
from pathlib import Path

def resource(rtype, name, value, lang=0x0804):
    prefix = struct.pack('<II',len(value),32)
    prefix += struct.pack('<HH',0xffff,rtype)
    prefix += struct.pack('<HH',0xffff,name)
    prefix += struct.pack('<IHHII',0,0x1030,lang,0,0)
    assert len(prefix)==32
    return prefix + value + b'\x00' * ((-len(value)) & 3)

ico = Path(__file__).with_name('AutoHideCN.ico').read_bytes()
reserved, kind, count = struct.unpack_from('<HHH',ico)
assert (reserved,kind)==(0,1) and count>0
out = resource(0,0,b'')
group = bytearray(struct.pack('<HHH',0,1,count))
for j in range(count):
    w,h,colors,reserved,planes,bpp,length,offset=struct.unpack_from('<BBBBHHII',ico,6+j*16)
    payload=ico[offset:offset+length]
    assert len(payload)==length
    ident=10+j
    out += resource(3,ident,payload)
    group += struct.pack('<BBBBHHIH',w,h,colors,reserved,planes,bpp,length,ident)
out += resource(14,1,bytes(group))
# Native visual styles, Per-Monitor V2 DPI and Windows version metadata.
out += resource(24,1,Path(__file__).with_name('AutoHideCN.manifest').read_bytes())

def align(data):
    return data + b'\x00' * (-len(data) & 3)

def version_block(key, value=b'', children=b'', text=False):
    header = struct.pack('<HHH', 0, len(value)//2 if text else len(value), int(text))
    data = align(header + (key+'\x00').encode('utf-16le')) + value
    if children:
        data = align(data) + children
    return struct.pack('<H', len(data)) + data[2:]

strings = b''
for key, value in [('FileDescription','桌面图标自动隐藏'), ('FileVersion','1.4.1.0'),
                   ('ProductName','AutoHideCN'), ('ProductVersion','1.4.1'),
                   ('OriginalFilename','AutoHideCN.exe')]:
    strings += align(version_block(key, (value+'\x00').encode('utf-16le'), text=True))
table = version_block('080404B0', children=strings)
info = version_block('StringFileInfo', children=align(table))
translation = version_block('Translation', struct.pack('<HH', 0x0804, 1200))
var = version_block('VarFileInfo', children=align(translation))
fixed = struct.pack('<13I', 0xfeef04bd, 0x10000, 0x10004, 0x10000, 0x10004, 0x10000,
                    0x3f, 0, 0x40004, 1, 0, 0, 0)
out += resource(16, 1, version_block('VS_VERSION_INFO', fixed, align(info)+align(var)))
Path(__file__).with_name('AutoHideCN.res').write_bytes(out)
print(f'Generated .res: {len(out)} bytes, {count} icons')
