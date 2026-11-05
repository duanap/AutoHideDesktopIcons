"""Build the simple green desktop monitor icon for AutoHideCN.

This is an original icon asset; Pillow is only required to regenerate it.
The application itself has no Pillow or Python dependency.
"""
from PIL import Image, ImageDraw
from pathlib import Path

S = 1024
im = Image.new('RGBA', (S, S), (0, 0, 0, 0))
d = ImageDraw.Draw(im)
# Soft green rounded tile.
d.rounded_rectangle((56, 56, 968, 968), radius=234, fill=(45, 174, 62, 255))
d.rounded_rectangle((74, 74, 948, 948), radius=218, outline=(113, 222, 115, 255), width=6)
# Simple white display symbol.
d.rounded_rectangle((260, 270, 765, 665), radius=55, fill=(255, 255, 255, 255))
d.rounded_rectangle((302, 312, 723, 625), radius=19, fill=(45, 174, 62, 255))
d.rounded_rectangle((482, 664, 543, 748), radius=8, fill=(255, 255, 255, 255))
d.rounded_rectangle((370, 735, 655, 785), radius=24, fill=(255, 255, 255, 255))
# Consistent anti-aliased sizes through ICO output.
im = im.resize((256, 256), Image.Resampling.LANCZOS)
path = Path(__file__).with_name('AutoHideCN.ico')
im.save(path, format='ICO', sizes=[(16, 16), (24, 24), (32, 32), (48, 48), (64, 64), (128, 128), (256, 256)])
print('Created', path, 'size', path.stat().st_size)
