<#
.SYNOPSIS
  Builds MainUI_26 and packages it as a portable Windows x64 folder + ZIP
  (the Windows analog of build-appimage.sh). CUDA dense reconstruction comes
  from the bundled tools\win64\colmap.exe -- run stage-tools-win.ps1 first.

  Steps:
    1. CMake configure (Release, Ninja) with Qt6 + OpenCV located.
    2. Build -- POST_BUILD steps auto-copy onnxruntime.dll, models\, tools\win64\
       next to the exe (see CMakeLists.txt lines ~141-189).
    3. windeployqt -- bundles Qt6 DLLs, platforms\qwindows.dll, the multimedia/
       charts/opengl plugins, and the VC++ runtime next to the exe.
    4. Copy the OpenCV runtime DLL (opencv_world*.dll).
    5. Zip the staged folder -> MainUI_26-win64-cuda.zip at the repo root.

  Run from a "x64 Native Tools Command Prompt for VS 2022" (so the MSVC
  toolchain is on PATH), e.g.:  powershell -File packaging\build-windows.ps1 ...

.PARAMETER QtDir
  Qt msvc2022_64 prefix, e.g. C:\Qt\6.8.1\msvc2022_64

.PARAMETER OpenCVDir
  Folder containing OpenCVConfig.cmake, e.g. C:\opencv\build
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)][string]$QtDir,
    [Parameter(Mandatory = $true)][string]$OpenCVDir,
    [string]$RepoRoot  = (Resolve-Path (Join-Path $PSScriptRoot "..")),
    [string]$BuildDir  = "build-win",
    [string]$DistName  = "MainUI_26-win64-cuda"
)

$ErrorActionPreference = "Stop"
Set-Location $RepoRoot

$build   = Join-Path $RepoRoot $BuildDir
$binDir  = Join-Path $build "bin"          # CMAKE_RUNTIME_OUTPUT_DIRECTORY
$winDeploy = Join-Path $QtDir "bin\windeployqt.exe"

if (-not (Test-Path $winDeploy)) { throw "windeployqt not found at $winDeploy (check -QtDir)" }
if (-not (Test-Path (Join-Path $RepoRoot "third_party\onnxruntime\lib\win\onnxruntime.dll"))) {
    throw "onnxruntime.dll missing -- run stage-tools-win.ps1 first."
}
if (-not (Test-Path (Join-Path $RepoRoot "tools\win64\colmap.exe"))) {
    Write-Warning "tools\win64\colmap.exe missing -- CUDA dense step will have no COLMAP. Run stage-tools-win.ps1."
}

Write-Host "==> Configuring (Release, output staged into $BuildDir\bin)"
cmake -S . -B $build -G Ninja `
    -DCMAKE_BUILD_TYPE=Release `
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$binDir" `
    -DCMAKE_PREFIX_PATH="$QtDir" `
    -DOpenCV_DIR="$OpenCVDir"
if ($LASTEXITCODE) { throw "CMake configure failed" }

Write-Host "==> Building"
cmake --build $build --parallel
if ($LASTEXITCODE) { throw "Build failed" }

$exe = Join-Path $binDir "MainUI_26.exe"
if (-not (Test-Path $exe)) { throw "Build produced no $exe" }

Write-Host "==> Running windeployqt"
& $winDeploy --release --compiler-runtime --no-translations $exe
if ($LASTEXITCODE) { throw "windeployqt failed" }

Write-Host "==> Copying OpenCV runtime DLL"
$cvDll = Get-ChildItem -Path $OpenCVDir -Recurse -Filter "opencv_world*.dll" |
    Where-Object { $_.Name -notmatch 'd\.dll$' } | Select-Object -First 1
if ($cvDll) {
    Copy-Item $cvDll.FullName $binDir -Force
    Write-Host "    $($cvDll.Name)"
} else {
    Write-Warning "No opencv_world*.dll found under $OpenCVDir -- if you built OpenCV as separate modules, copy opencv_core/imgproc/dnn DLLs into $binDir manually."
}

# Sanity: the POST_BUILD steps should already have placed these.
foreach ($must in @("onnxruntime.dll", "models\crabs_yolov8n.onnx", "tools\win64\colmap.exe")) {
    if (-not (Test-Path (Join-Path $binDir $must))) {
        Write-Warning "Expected $must next to the exe but it's missing."
    }
}

Write-Host "==> Zipping portable folder -> $DistName.zip"
$zip = Join-Path $RepoRoot "$DistName.zip"
if (Test-Path $zip) { Remove-Item $zip -Force }
Compress-Archive -Path (Join-Path $binDir "*") -DestinationPath $zip

Write-Host ""
Write-Host "==> Done: $zip"
Write-Host "    Portable folder: $binDir"
