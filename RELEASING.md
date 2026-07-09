# Releasing MainUI_26

End users do **not** build from source or install Qt. CI compiles the app once
per platform, bundles every runtime dependency, and attaches ready-to-run
artifacts to a GitHub Release. Users just download and run.

## Cutting a release

```sh
git tag v0.1.0
git push origin v0.1.0
```

The `.github/workflows/release.yml` workflow then:

1. Builds on `ubuntu-22.04` and `windows-latest`.
2. Bundles Qt + OpenCV + ONNX Runtime + the YOLO model alongside the binary.
3. Produces:
   - `MainUI_26-linux-x86_64.AppImage` — single-file, `chmod +x` and run.
   - `MainUI_26-windows-x64.zip` — unzip, run `MainUI_26.exe`.
4. Publishes both to a GitHub Release for the tag.

Run it without publishing from the **Actions → Release → Run workflow** button
(manual runs upload artifacts but skip the Release step).

## What's bundled vs. what isn't

| Dependency      | Linux AppImage         | Windows zip            |
| --------------- | ---------------------- | ---------------------- |
| Qt 6 runtime    | ✅ (linuxdeploy-qt)    | ✅ (windeployqt)       |
| OpenCV          | ✅                     | ✅ (opencv_world DLL)  |
| ONNX Runtime    | ✅ (from repo `.so`)   | ✅ (DLL fetched in CI) |
| YOLO crab model | ✅ `models/`           | ✅ `models/`           |
| **COLMAP**      | ❌ not bundled         | ❌ not bundled         |

### COLMAP is intentionally not bundled

The photogrammetry binaries are ~1 GB/platform and gitignored. They are
**optional**: `MainWindow::detectColmapPath()` (mainwindow.cpp) looks for a
bundled `tools/<platform>/colmap`, then COLMAP on `PATH`, then prompts the user
to locate it. So the release runs fine without them — only the photogrammetry
feature needs COLMAP, and users who want it install COLMAP separately
(`apt install colmap`, or the official Windows installer).

To bundle COLMAP anyway, drop the platform binaries into
`AppDir/usr/bin/tools/<platform>/` (Linux) or the staging dir (Windows) before
packaging, and host the large files outside the git repo (a separate Release
asset that CI downloads, since they exceed Git LFS free limits).

## Version knobs

Pinned at the top of `release.yml` (`env:`): `QT_VERSION`, `ORT_VERSION`
(must match `third_party/onnxruntime/include`), `OPENCV_VERSION`, `QT_MODULES`.

## First-run validation

GitHub Actions can't be dry-run locally, so validate the first tagged build:

- **AppImage** loads `models/` and `libonnxruntime.so.1` relative to the
  executable — confirm crab detection works after extraction.
- **Windows** — confirm `windeployqt` pulled the Multimedia/Charts plugins and
  that `opencv_world*.dll` + `onnxruntime.dll` sit next to the `.exe`.
- If the OpenCV Windows release layout differs (e.g. `vc16` → `vc17`), adjust
  the `opencv_world*.dll` copy path in the workflow.
