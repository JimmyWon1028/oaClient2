import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import plistlib
import posixpath
import shutil
import stat
import struct
import zipfile


def sha256(path):
  digest = hashlib.sha256()
  with path.open('rb') as stream:
    for block in iter(lambda: stream.read(1024 * 1024), b''):
      digest.update(block)
  return digest.hexdigest()


def zip_info(name, mode, directory=False):
  info = zipfile.ZipInfo(name)
  info.create_system = 3
  info.external_attr = (mode << 16) | (0x10 if directory else 0)
  info.compress_type = zipfile.ZIP_DEFLATED
  return info


def main():
  parser = argparse.ArgumentParser(description='Package an already-verified Mac bundle using its macOS delivery manifest.')
  parser.add_argument('--delivery', type=Path, required=True)
  parser.add_argument('--manifest', type=Path, required=True)
  parser.add_argument('--output', type=Path, required=True)
  parser.add_argument('--evidence', type=Path, required=True)
  parser.add_argument('--source-commit', required=True)
  parser.add_argument('--expected-executable-sha256', required=True)
  args = parser.parse_args()
  delivery = args.delivery.resolve()
  output = args.output.resolve()
  if delivery.name != 'oaClient2.app':
    raise ValueError('Expected the complete oaClient2.app bundle.')
  if output.exists() or Path(str(output) + '.sha256').exists():
    raise ValueError('Release output already exists; preserve it before retrying.')
  manifest = json.loads(args.manifest.read_text(encoding='utf-8-sig'))
  directories = {delivery.name + '/'}
  restored_links = []
  mach_o = []
  forbidden = {'config.ini', '.env', '.ds_store', '__macosx', 'picture', 'logs',
    'browser-profile', 'cache', 'instance.lock'}
  for name, entry in manifest.items():
    relative = PurePosixPath(name)
    if relative.is_absolute() or '..' in relative.parts or any(part.casefold() in forbidden for part in relative.parts):
      raise ValueError(f'Unsafe or private bundle entry: {name}')
    path = delivery.joinpath(*relative.parts)
    for parent in relative.parents:
      if str(parent) != '.':
        directories.add(delivery.name + '/' + parent.as_posix() + '/')
    if 'link' in entry:
      target = entry['link']
      resolved = posixpath.normpath(posixpath.join(str(relative.parent), target))
      if PurePosixPath(target).is_absolute() or resolved == '..' or resolved.startswith('../'):
        raise ValueError(f'Link escapes the bundle: {name}')
      if resolved not in manifest and not any(key.startswith(resolved + '/') for key in manifest):
        raise ValueError(f'Link target does not exist in the verified bundle: {name}')
      if path.is_symlink():
        if path.readlink().as_posix() != target:
          raise ValueError(f'Link differs from the macOS manifest: {name}')
      elif path.exists():
        raise ValueError(f'A non-link occupies the expected symlink: {name}')
      else:
        restored_links.append(name)
    else:
      if path.is_symlink() or not path.is_file() or sha256(path) != entry['sha256']:
        raise ValueError(f'Bundle file differs from the macOS manifest: {name}')
      if entry['mode'] not in (0o644, 0o755):
        raise ValueError(f'Unexpected file permissions: {name}')
      with path.open('rb') as stream:
        header = stream.read(8)
      if len(header) == 8 and header[:4] in (b'\xcf\xfa\xed\xfe', b'\xca\xfe\xba\xbe', b'\xbe\xba\xfe\xca'):
        if struct.unpack('<II', header) != (0xfeedfacf, 0x0100000c):
          raise ValueError(f'Expected thin arm64 Mach-O: {name}')
        if not entry['mode'] & 0o111:
          raise ValueError(f'Mach-O file is not executable: {name}')
        mach_o.append(name)
  #2026.11.18 by codex, refuse extra files instead of silently packaging data absent from the signed delivery manifest.
  for path in delivery.rglob('*'):
    if (path.is_file() or path.is_symlink()) and path.relative_to(delivery).as_posix() not in manifest:
      raise ValueError(f'Unverified extra bundle file: {path.relative_to(delivery)}')
  executable = delivery / 'Contents/MacOS/oaClient2'
  if sha256(executable) != args.expected_executable_sha256.lower() or len(mach_o) != 10:
    raise ValueError('The verified executable or ten arm64 components do not match.')
  with (delivery / 'Contents/Info.plist').open('rb') as stream:
    version = plistlib.load(stream)['CFBundleShortVersionString']
  output.parent.mkdir(parents=True, exist_ok=True)
  #2026.11.18 by codex, preserve Unix modes and verified symlink targets even when Windows sync omits the links.
  with zipfile.ZipFile(output, 'x', zipfile.ZIP_DEFLATED, compresslevel=6) as archive:
    for directory in sorted(directories):
      archive.writestr(zip_info(directory, stat.S_IFDIR | 0o755, True), b'')
    for name, entry in sorted(manifest.items()):
      archive_name = delivery.name + '/' + name
      if 'link' in entry:
        archive.writestr(zip_info(archive_name, stat.S_IFLNK | 0o777), entry['link'].encode('utf-8'))
      else:
        info = zip_info(archive_name, stat.S_IFREG | entry['mode'])
        with delivery.joinpath(*PurePosixPath(name).parts).open('rb') as source, archive.open(info, 'w') as target:
          shutil.copyfileobj(source, target, 1024 * 1024)
  with zipfile.ZipFile(output) as archive:
    expected_names = directories | {delivery.name + '/' + name for name in manifest}
    if set(archive.namelist()) != expected_names or archive.testzip() is not None:
      raise ValueError('Archive entry list or CRC validation failed.')
    for name, entry in manifest.items():
      info = archive.getinfo(delivery.name + '/' + name)
      mode = info.external_attr >> 16
      if 'link' in entry:
        if not stat.S_ISLNK(mode) or archive.read(info).decode('utf-8') != entry['link']:
          raise ValueError(f'Archive symlink differs: {name}')
      else:
        if not stat.S_ISREG(mode) or stat.S_IMODE(mode) != entry['mode']:
          raise ValueError(f'Archive mode differs: {name}')
        digest = hashlib.sha256()
        with archive.open(info) as stream:
          for block in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(block)
        if digest.hexdigest() != entry['sha256']:
          raise ValueError(f'Archive file differs: {name}')
        if sha256(delivery.joinpath(*PurePosixPath(name).parts)) != entry['sha256']:
          raise ValueError(f'Delivery changed during packaging: {name}')
  digest = sha256(output)
  Path(str(output) + '.sha256').write_text(f'{digest}  {output.name}\n', encoding='utf-8')
  evidence = {
    'work_id': 'R04', 'source_commit': args.source_commit, 'platform': 'macOS arm64', 'version': version,
    'zip_name': output.name, 'zip_bytes': output.stat().st_size, 'zip_sha256': digest,
    'executable_sha256': args.expected_executable_sha256.lower(), 'bundle_entries': len(manifest),
    'regular_files': len(manifest) - sum('link' in entry for entry in manifest.values()),
    'symlinks': sum('link' in entry for entry in manifest.values()), 'restored_links': restored_links,
    'manifest_sha256': sha256(args.manifest), 'crc_hashes_modes_links': 'passed', 'arm64_components': mach_o,
    'signature': 'bytes and modes match macOS-verified delivery; codesign not rerun on packaging host',
  }
  args.evidence.parent.mkdir(parents=True, exist_ok=True)
  args.evidence.write_text(json.dumps(evidence, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
  print(json.dumps({key: value for key, value in evidence.items() if key != 'arm64_components'}, ensure_ascii=False))


if __name__ == '__main__':
  main()
