# Building MainUI_26 for Windows 11 (with CUDA) — portable ZIP

This produces a self-contained `MainUI_26-win64-cuda.zip` (unzip → run, no installs),
the Windows analog of the Linux AppImage. **CUDA dense reconstruction is provided by the
bundled prebuilt `colmap.exe`** — the app itself has no CUDA code, so no CUDA toolkit is
needed to *build*; only an NVIDIA driver is needed to *run* the CUDA step.

All steps run **on the Windows 11 + NVIDIA machine.**

## 1. Install prerequisites

| Dependency | Notes |
|---|---|
| **Visual Studio 2022** (Community) | Workload: *Desktop development with C++* (MSVC v143 + Windows SDK). Use its **"x64 Native Tools Command Prompt for VS 2022"** for the build. |
| **Qt 6 (msvc2022_64)** | Qt Online Installer. Modules required: Core, Concurrent, Widgets, **Multimedia**, **MultimediaWidgets**, Network, OpenGL, OpenGLWidgets, **Qt Charts**. Note the path, e.g. `C:\Qt\6.8.1\msvc2022_64`. |
| **OpenCV (Windows prebuilt)** | `opencv-*-windows.exe` self-extractor → gives `...\opencv\build` (has `OpenCVConfig.cmake` + `opencv_world*.dll`). |
| **CMake + Ninja** | Bundled with VS 2022, or install standalone. |
| **NVIDIA GPU driver** | Recent driver so the CUDA dense step runs. CUDA *toolkit* not required (colmap bundles cudart). |
| **Python 3** (for the ROV Setup page) | Install from python.org with **"Add python.exe to PATH"** checked, then `pip install -r scripts\requirements.txt` (pygame + pytest). The app finds `py -3` automatically; no Python is embedded. |

## 2. Download the two binary assets (not in git)

- **ONNX Runtime 1.26.0 win-x64 (CPU):** `onnxruntime-win-x64-1.26.0.zip`
  (ONNX Runtime GitHub releases).
- **COLMAP CUDA prebuilt:** `colmap-x64-windows-cuda.zip` (COLMAP GitHub releases).

## 3. Stage the assets

From the repo root (PowerShell):

```powershell
.\packaging\stage-tools-win.ps1 `
    -OrtZip    C:\path\to\onnxruntime-win-x64-1.26.0.zip `
    -ColmapZip C:\path\to\colmap-x64-windows-cuda.zip
```

This puts a real `onnxruntime.dll`/`.lib` in `third_party\onnxruntime\lib\win\` and flattens
COLMAP into `tools\win64\` (so `tools\win64\colmap.exe` exists). Verify CUDA:

```powershell
& .\tools\win64\colmap.exe -h    # banner should mention CUDA
```

## 4. Build + package

From the **x64 Native Tools Command Prompt for VS 2022**, in the repo root:

```powershell
powershell -ExecutionPolicy Bypass -File .\packaging\build-windows.ps1 `
    -QtDir     C:\Qt\6.8.1\msvc2022_64 `
    -OpenCVDir C:\opencv\build
```

Output: `MainUI_26-win64-cuda.zip` at the repo root, and the portable folder at
`build-win\bin\`.

> If CMake configure can't find Qt Charts/Multimedia, the Qt install is missing those
> modules — re-run the Qt Maintenance Tool and add them.
> `-ExecutionPolicy Bypass` is needed because the scripts aren't signed.

## 4b. Enable the ROV Setup (script activation) page

The build bundles the PC-native control-systems scripts into `build-win\bin\scripts\`
(`thruster.py`, `test_controllers.py`, `axistest.py`, `tests\`). The Pi-side scripts are
intentionally not included. To make the page work:

1. Install Python 3 (PATH option checked) and `pip install -r scripts\requirements.txt`.
2. Launch the app → **ROV Setup → Connection Settings** → set **Local scripts** to the
   bundled `scripts\` folder (next to `MainUI_26.exe`). Leave the Python field blank to use
   the system `py -3`, or point it at a specific `python.exe`.
3. The Detect / Thruster / Axis / Pytest buttons should now be enabled.

## 5. Verify (end-to-end)

1. **Cold launch:** unzip on a *clean* Windows 11 box (no Qt/OpenCV/COLMAP installed) and run
   `MainUI_26.exe`. The main window must render; a missing DLL shows as a "…not found" dialog.
2. **COLMAP auto-detect:** the app resolves COLMAP to the bundled `tools\win64\colmap.exe`
   with no file-picker prompt.
3. **CUDA reconstruction:** run a small (well-overlapping) dataset. The Windows dense pipeline
   runs `image_undistorter` → **Dense Stereo (CUDA)** → `stereo_fusion`. During the dense step,
   **Task Manager → Performance → GPU → CUDA** should show load — that's the proof CUDA is on.
   Output `dense\fused.ply` should load in the model viewer.
4. **Crab detector:** confirm the YOLO model loads (CPU ONNX) without error.
5. **ROV Setup page:** with a game controller plugged in, click **Detect Controllers**
   (runs `test_controllers.py`), then **Thruster Control** (runs `thruster.py`). Output should
   appear in the log with no "no Python interpreter found" / "set a valid folder" errors.
   **Pytest** should run `tests\` green (proves pygame/pytest are installed correctly).

## Notes

- No C++ source changes are needed — the codebase already has full Windows branches.
- OpenMVS is intentionally **not** shipped on Windows; the dense path is pure COLMAP-CUDA
  (`src/colmaprunner.cpp` lines ~124-174).
- The staged binaries (`third_party\onnxruntime\lib\win\*`, `tools\win64\*`) are git-ignored —
  they live locally on the Windows box.
