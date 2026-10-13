import argparse
import hashlib
import json
from pathlib import Path
import struct
import zipfile


def sha256(path):
  digest = hashlib.sha256()
  with path.open('rb') as stream:
    for block in iter(lambda: stream.read(1024 * 1024), b''):
      digest.update(block)
  return digest.hexdigest()


def require_x64(path):
  with path.open('rb') as stream:
    if stream.read(2) != b'MZ':
      raise ValueError(f'Invalid PE file: {path.name}')
    stream.seek(0x3c)
    offset = struct.unpack('<I', stream.read(4))[0]
    stream.seek(offset)
    if stream.read(4) != b'PE\x00\x00' or stream.read(2) != b'\x64\x86':
      raise ValueError(f'Expected an AMD64 PE file: {path.name}')


def main():
  project = Path(__file__).resolve().parent.parent
  parser = argparse.ArgumentParser()
  parser.add_argument('--delivery', type=Path, default=project / 'artifacts/oaClient2')
  parser.add_argument('--output', type=Path, required=True)
  parser.add_argument('--evidence', type=Path, required=True)
  parser.add_argument('--source-commit', required=True)
  parser.add_argument('--expected-exe-sha256', required=True)
  args = parser.parse_args()
  delivery = args.delivery.resolve()
  output = args.output.resolve()
  if output.exists() or Path(str(output) + '.sha256').exists():
    raise ValueError('Release output already exists; preserve it and inspect before retrying.')
  executable = delivery / 'oaClient2.exe'
  require_x64(executable)
  require_x64(delivery / 'cef/libcef.dll')
  if sha256(executable) != args.expected_exe_sha256.lower():
    raise ValueError('The delivery EXE differs from the verified build.')
  example = delivery / 'Config.example.ini'
  if sha256(example) != sha256(project / 'config/Config.example.ini'):
    raise ValueError('The delivery example differs from the shared safe example.')

  #2026.10.13 modify by codex, package only runtime files and the current user-maintained prg.
  runtime_names = {
    'CEF-LICENSE.txt', 'chrome_100_percent.pak', 'chrome_200_percent.pak',
    'chrome_elf.dll', 'd3dcompiler_47.dll', 'dxcompiler.dll', 'dxil.dll',
    'icudtl.dat', 'libcef.dll', 'resources.pak', 'v8_context_snapshot.bin',
    'vk_swiftshader.dll', 'vk_swiftshader_icd.json', 'vulkan-1.dll',
  }
  files = [executable, example]
  runtime = sorted(path for path in (delivery / 'cef').rglob('*') if path.is_file())
  for path in runtime:
    relative = path.relative_to(delivery / 'cef')
    valid = len(relative.parts) == 1 and relative.name in runtime_names
    valid = valid or (len(relative.parts) == 2 and relative.parts[0] == 'locales'
      and relative.suffix == '.pak')
    if not valid:
      raise ValueError(f'Unexpected runtime file: {relative}')
  if not runtime_names.issubset({path.name for path in runtime}):
    raise ValueError('Required CEF runtime files are missing.')
  if not any(path.parent.name == 'locales' for path in runtime):
    raise ValueError('CEF locale files are missing.')
  files.extend(runtime)
  tools = sorted(path for path in (delivery / 'prg').rglob('*') if path.is_file())
  if not any(path.name == 'Reptool.exe' for path in tools):
    raise ValueError('The current delivery lacks Reptool.exe.')
  if any(path.suffix.lower() not in {'.exe', '.dll'} for path in tools):
    raise ValueError('Inspect non-binary prg files before publishing a release.')
  files.extend(tools)
  if any(path.is_symlink() for path in files):
    raise ValueError('Release files must not be symlinks.')
  entries = {f'oaClient2/{path.relative_to(delivery).as_posix()}': sha256(path)
    for path in files}
  output.parent.mkdir(parents=True, exist_ok=True)
  with zipfile.ZipFile(output, 'x', zipfile.ZIP_DEFLATED, compresslevel=6) as archive:
    for path in files:
      archive.write(path, f'oaClient2/{path.relative_to(delivery).as_posix()}')
  with zipfile.ZipFile(output) as archive:
    if archive.testzip() is not None or set(archive.namelist()) != set(entries):
      raise ValueError('ZIP CRC or entry validation failed.')
    for name, expected in entries.items():
      with archive.open(name) as stream:
        digest = hashlib.sha256()
        for block in iter(lambda: stream.read(1024 * 1024), b''):
          digest.update(block)
      if digest.hexdigest() != expected:
        raise ValueError(f'ZIP content mismatch: {name}')
  if any(sha256(path) != entries[f'oaClient2/{path.relative_to(delivery).as_posix()}']
      for path in files):
    raise ValueError('Delivery files changed while packaging.')
  digest = sha256(output)
  Path(str(output) + '.sha256').write_text(f'{digest}  {output.name}\n', encoding='utf-8')
  evidence = {
    'work_id': 'R02', 'source_commit': args.source_commit, 'platform': 'Windows x64',
    'zip_name': output.name, 'zip_bytes': output.stat().st_size, 'zip_sha256': digest,
    'exe_sha256': args.expected_exe_sha256.lower(), 'file_count': len(entries),
    'cef_file_count': len(runtime), 'prg': [path.relative_to(delivery).as_posix() for path in tools],
    'crc_and_all_file_hashes': 'passed', 'entries': entries,
  }
  args.evidence.parent.mkdir(parents=True, exist_ok=True)
  args.evidence.write_text(json.dumps(evidence, ensure_ascii=False, indent=2) + '\n',
    encoding='utf-8')
  print(json.dumps({key: value for key, value in evidence.items() if key != 'entries'},
    ensure_ascii=False))


if __name__ == '__main__':
  main()
