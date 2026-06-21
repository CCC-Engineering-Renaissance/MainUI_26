#!/usr/bin/env bash
# Builds MainUI_26 and packages it as a portable Linux AppImage.
# Run from the repo root: ./packaging/build-appimage.sh
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

BUILD_DIR="$ROOT/build-appimage/build"
APPDIR="$ROOT/build-appimage/AppDir"
CACHE="$ROOT/packaging/.cache"

echo "==> Configuring (Release, output staged into build-appimage/build/bin)"
cmake -S . -B "$BUILD_DIR" -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$BUILD_DIR/bin"

echo "==> Building"
cmake --build "$BUILD_DIR" --parallel

echo "==> Staging AppDir"
rm -rf "$APPDIR"
mkdir -p "$APPDIR/usr/bin"
cp -a "$BUILD_DIR/bin/." "$APPDIR/usr/bin/"

export QMAKE="${QMAKE:-/usr/bin/qmake6}"
export LD_LIBRARY_PATH="$ROOT/third_party/onnxruntime/lib/linux:${LD_LIBRARY_PATH:-}"
export APPIMAGE_EXTRACT_AND_RUN=1

echo "==> Running linuxdeploy + Qt plugin"
# Use the persistently-extracted, strip-patched copies (see packaging/README or
# the AppImage cache setup) rather than the raw downloaded AppImages directly:
# their bundled `strip` predates RELR relocations and aborts on modern Arch libs.
"$CACHE/linuxdeploy-extracted/AppRun" --appdir "$APPDIR" \
  -e "$APPDIR/usr/bin/MainUI_26" \
  -d "$ROOT/packaging/MainUI_26.desktop" \
  -i "$ROOT/packaging/rov_logo_complete.png" \
  -l "$APPDIR/usr/bin/libonnxruntime.so.1.26.0" \
  --plugin qt --output appimage

echo "==> Moving AppImage to repo root"
mv -f "$ROOT"/MainUI_26-*.AppImage "$ROOT/MainUI_26-x86_64.AppImage"

echo "==> Done: $ROOT/MainUI_26-x86_64.AppImage"
