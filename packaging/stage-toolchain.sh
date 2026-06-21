#!/usr/bin/env bash
# Stages standalone colmap + OpenMVS binaries into tools/linux/{bin,lib,plugins}
# so the app can bundle them for a self-contained AppImage (see CMakeLists.txt's
# `if(EXISTS .../tools/linux)` copy block). Run from the repo root:
#   ./packaging/stage-toolchain.sh
#
# Prerequisites (built/installed by you beforehand, not by this script):
#   - colmap built with -DONNX_ENABLED=OFF (the AUR onnxruntime-cpu package on
#     this machine is ABI-incompatible with the cachyos-rebuilt protobuf/abseil-cpp;
#     ONNX only gates the optional ALIKED feature matcher, unused by this project).
#     Set COLMAP_BIN below to point at the built binary.
#   - openmvs installed via `yay -S openmvs` (BUILD_CUDA defaults to OFF already).
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

COLMAP_BIN="${COLMAP_BIN:-$HOME/.cache/yay/colmap/src/build/src/colmap/exe/colmap}"
OPENMVS_TOOLS=(InterfaceCOLMAP DensifyPointCloud ReconstructMesh RefineMesh TextureMesh)

LINUXDEPLOY="$ROOT/packaging/.cache/linuxdeploy-extracted/AppRun"
APPDIR="$ROOT/build-appimage/toolchain-appdir"
DEST="$ROOT/tools/linux"

if [[ ! -x "$LINUXDEPLOY" ]]; then
  echo "Missing $LINUXDEPLOY -- run the linuxdeploy extract+patch steps from build-appimage.sh's setup first." >&2
  exit 1
fi

rm -rf "$APPDIR" "$DEST"
mkdir -p "$APPDIR/usr/bin" "$DEST/bin" "$DEST/lib" "$DEST/plugins"

echo "==> Staging colmap"
if [[ ! -x "$COLMAP_BIN" ]]; then
  echo "Missing colmap binary at $COLMAP_BIN (set COLMAP_BIN=...)" >&2
  exit 1
fi
cp "$COLMAP_BIN" "$APPDIR/usr/bin/colmap"

echo "==> Staging OpenMVS tools"
for tool in "${OPENMVS_TOOLS[@]}"; do
  tool_path="$(command -v "$tool" || true)"
  if [[ -z "$tool_path" ]]; then
    echo "Missing OpenMVS tool: $tool (is openmvs installed? \`yay -S openmvs\`)" >&2
    exit 1
  fi
  cp "$tool_path" "$APPDIR/usr/bin/$tool"
done

export QMAKE="${QMAKE:-/usr/bin/qmake6}"
export APPIMAGE_EXTRACT_AND_RUN=1
export EXTRA_PLATFORM_PLUGINS="libqoffscreen.so"

echo "==> Running linuxdeploy + Qt plugin against all staged binaries"
exe_flags=()
for f in "$APPDIR/usr/bin/"*; do
  exe_flags+=(-e "$f")
done
"$LINUXDEPLOY" --appdir "$APPDIR" "${exe_flags[@]}" --plugin qt

echo "==> Flattening into tools/linux/{bin,lib,plugins}"
cp -a "$APPDIR/usr/bin/." "$DEST/bin/"
cp -a "$APPDIR/usr/lib/." "$DEST/lib/"
cp -a "$APPDIR/usr/plugins/." "$DEST/plugins/"

echo "==> Done. Verify with:"
echo "QT_QPA_PLATFORM=offscreen LD_LIBRARY_PATH=\"$DEST/lib\" QT_PLUGIN_PATH=\"$DEST/plugins\" \"$DEST/bin/colmap\" -h"
