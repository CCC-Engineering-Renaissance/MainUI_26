<#
.SYNOPSIS
  Stages the Windows-only binary assets that are NOT tracked in git, so the app
  can bundle them (mirrors the role of stage-toolchain.sh on Linux):

    1. A real ONNX Runtime 1.26.0 win-x64 onnxruntime.dll + onnxruntime.lib into
       third_party\onnxruntime\lib\win\  (the in-tree .lib is a 2 KB stub and the
       .dll is missing -- CMakeLists.txt links the .lib and copies the .dll next
       to the exe at build time).
    2. The official prebuilt COLMAP-CUDA, FLATTENED so colmap.exe + its DLLs land
       directly in tools\win64\  (detectColmapPath() probes tools/win64/colmap.exe
       and ColmapRunner::startStep puts that dir first on PATH for DLL loading).

  CUDA is provided entirely by this prebuilt colmap.exe -- the app itself has no
  CUDA code, so nothing here needs the CUDA toolkit.

.PARAMETER OrtZip
  Path to onnxruntime-win-x64-1.26.0.zip (from the ONNX Runtime GitHub releases).

.PARAMETER ColmapZip
  Path to colmap-x64-windows-cuda.zip (from the COLMAP GitHub releases).

.EXAMPLE
  .\packaging\stage-tools-win.ps1 `
     -OrtZip C:\dl\onnxruntime-win-x64-1.26.0.zip `
     -ColmapZip C:\dl\colmap-x64-windows-cuda.zip
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)][string]$OrtZip,
    [Parameter(Mandatory = $true)][string]$ColmapZip,
    [string]$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot ".."))
)

$ErrorActionPreference = "Stop"

function Expand-ToTemp([string]$zip, [string]$tag) {
    if (-not (Test-Path $zip)) { throw "Zip not found: $zip" }
    $dest = Join-Path ([System.IO.Path]::GetTempPath()) "mainui26-$tag-$(Get-Random)"
    Write-Host "==> Extracting $tag -> $dest"
    Expand-Archive -Path $zip -DestinationPath $dest -Force
    return $dest
}

# --- 1. ONNX Runtime -------------------------------------------------------
$ortOut = Join-Path $RepoRoot "third_party\onnxruntime\lib\win"
New-Item -ItemType Directory -Force -Path $ortOut | Out-Null

$ortTmp = Expand-ToTemp $OrtZip "ort"
$ortDll = Get-ChildItem -Path $ortTmp -Recurse -Filter "onnxruntime.dll" | Select-Object -First 1
$ortLib = Get-ChildItem -Path $ortTmp -Recurse -Filter "onnxruntime.lib" | Select-Object -First 1
if (-not $ortDll) { throw "onnxruntime.dll not found inside $OrtZip" }
if (-not $ortLib) { throw "onnxruntime.lib not found inside $OrtZip" }

Copy-Item $ortDll.FullName (Join-Path $ortOut "onnxruntime.dll") -Force
Copy-Item $ortLib.FullName (Join-Path $ortOut "onnxruntime.lib") -Force
Write-Host ("==> ONNX staged: onnxruntime.dll {0:N1} MB, onnxruntime.lib {1:N1} MB" -f `
    ($ortDll.Length / 1MB), ($ortLib.Length / 1MB))
if ($ortLib.Length -lt 100KB) {
    Write-Warning "onnxruntime.lib looks suspiciously small -- is this a real ORT package?"
}

# --- 2. COLMAP-CUDA --------------------------------------------------------
$toolsOut = Join-Path $RepoRoot "tools\win64"
if (Test-Path $toolsOut) { Remove-Item $toolsOut -Recurse -Force }
New-Item -ItemType Directory -Force -Path $toolsOut | Out-Null

$colTmp = Expand-ToTemp $ColmapZip "colmap"
$colExe = Get-ChildItem -Path $colTmp -Recurse -Filter "colmap.exe" | Select-Object -First 1
if (-not $colExe) { throw "colmap.exe not found inside $ColmapZip" }
$binDir = $colExe.Directory.FullName

# Flatten the bin\ contents (colmap.exe + all DLLs) to the top of tools\win64.
Write-Host "==> Flattening $binDir -> $toolsOut"
Copy-Item -Path (Join-Path $binDir "*") -Destination $toolsOut -Recurse -Force

# Carry along sibling lib\ / share\ dirs (Qt plugins, vocab trees, etc.) if present.
$colRoot = Split-Path $binDir -Parent
foreach ($sub in @("lib", "share", "plugins")) {
    $src = Join-Path $colRoot $sub
    if (Test-Path $src) {
        Write-Host "==> Carrying $sub\"
        Copy-Item -Path $src -Destination $toolsOut -Recurse -Force
    }
}

$stagedColmap = Join-Path $toolsOut "colmap.exe"
if (-not (Test-Path $stagedColmap)) { throw "Staging failed: $stagedColmap missing" }

Write-Host ""
Write-Host "==> Done. Verify COLMAP is the CUDA build with:"
Write-Host "    & '$stagedColmap' -h     # banner should mention CUDA"
