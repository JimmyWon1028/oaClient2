#!/bin/bash
set -euo pipefail

#2026.10.12 modify by codex, keep SDK and intermediate output outside the synchronized source.
task_source_root="$(cd "$(dirname "$0")/.." && pwd)"
task_build_root="${OA_BUILD_ROOT:-$HOME/Library/Caches/oaClient2/build/macos-arm64}"
: "${CEF_ROOT:?Set CEF_ROOT to the verified local macosarm64 standard SDK.}"
if [ "$(uname -m)" != arm64 ]; then
  echo "Native Apple Silicon arm64 is required." >&2
  exit 1
fi
python3 - "$task_source_root" "$task_build_root" "$CEF_ROOT" <<'PY'
import sys
from pathlib import Path
source = Path(sys.argv[1]).resolve()
for value in sys.argv[2:]:
  if Path(value).resolve().is_relative_to(source):
    raise SystemExit('Build output and CEF SDK must be outside the synchronized source.')
PY
cmake -S "$task_source_root" -B "$task_build_root" -G 'Unix Makefiles' \
  -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64 -DPROJECT_ARCH=arm64 \
  -DCEF_ROOT="$CEF_ROOT" -DUSE_SANDBOX=OFF -DBUILD_TESTING=ON
cmake --build "$task_build_root" --parallel "${OA_BUILD_JOBS:-8}"
ctest --test-dir "$task_build_root" --output-on-failure
/usr/bin/codesign --verify --deep --strict "$task_build_root/Release/oaClient2.app"
