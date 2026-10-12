#!/bin/bash
set -euo pipefail

#2026.10.12 modify by codex, deliver one self-contained app for drag-and-drop installation.
task_source_root="$(cd "$(dirname "$0")/.." && pwd)"
task_build_root="${OA_BUILD_ROOT:-$HOME/Library/Caches/oaClient2/build/macos-arm64}"
task_app="$task_build_root/Release/oaClient2.app"
task_delivery="$task_source_root/artifacts/macos-arm64"
test -x "$task_app/Contents/MacOS/oaClient2"
/usr/bin/codesign --verify --deep --strict "$task_app"
mkdir -p "$task_delivery"
if [ -L "$task_delivery/oaClient2.app" ]; then
  echo "Refusing to replace a linked delivery app." >&2
  exit 1
fi
mkdir -p "$task_delivery/oaClient2.app"
/usr/bin/rsync -a --delete "$task_app/" "$task_delivery/oaClient2.app/"
/usr/bin/codesign --verify --deep --strict "$task_delivery/oaClient2.app"
echo "Packaged: $task_delivery/oaClient2.app"
