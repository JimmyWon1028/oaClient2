import struct
import sys
from pathlib import Path


#2026.10.12 modify by codex, wrap the shared original OA PNG in ICNS without redrawing it.
image = Path(sys.argv[1]).read_bytes()
if not image.startswith(b'\x89PNG') or struct.unpack_from('>II', image, 16) != (256, 256):
  raise SystemExit('The shared OA icon must be a 256px PNG.')
chunk = b'ic08' + struct.pack('>I', 8 + len(image)) + image
Path(sys.argv[2]).write_bytes(b'icns' + struct.pack('>I', 8 + len(chunk)) + chunk)
