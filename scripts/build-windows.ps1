param(
  [string]$CefRoot = $env:CEF_ROOT,
  [string]$BuildRoot = (Join-Path $env:LOCALAPPDATA 'oaClient2/build/windows-x64'),
  [ValidateSet('Debug', 'Release')][string]$Configuration = 'Release',
  [switch]$RunTests
)

$ErrorActionPreference = 'Stop'
$taskSourceRoot = Split-Path -Parent $PSScriptRoot
$taskVswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio/Installer/vswhere.exe'
$taskVsRoot = & $taskVswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $taskVsRoot) { throw 'Install Visual Studio Build Tools 2022 with C++ and the Windows SDK.' }
$taskCmake = Join-Path $taskVsRoot 'Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe'
if (-not (Test-Path -LiteralPath $taskCmake)) {
  $taskCmake = (Get-Command cmake -ErrorAction Stop).Source
}
if (-not $CefRoot) {
  $taskMetadata = Join-Path $env:LOCALAPPDATA 'oaClient2/deps/cef-windows64.json'
  if (Test-Path -LiteralPath $taskMetadata) {
    $taskMeta = Get-Content -LiteralPath $taskMetadata -Raw | ConvertFrom-Json
    $CefRoot = Join-Path (Split-Path -Parent $taskMetadata) ($taskMeta.file -replace '\.tar\.bz2$', '')
  }
}
if (-not (Test-Path -LiteralPath (Join-Path $CefRoot 'include/cef_app.h'))) { throw 'Provide -CefRoot or set CEF_ROOT.' }
$taskSourceAbsolute = [System.IO.Path]::GetFullPath($taskSourceRoot)
$taskBuildAbsolute = [System.IO.Path]::GetFullPath($BuildRoot)
if ($taskBuildAbsolute.StartsWith($taskSourceAbsolute + [System.IO.Path]::DirectorySeparatorChar, [System.StringComparison]::OrdinalIgnoreCase) -or $taskBuildAbsolute -eq $taskSourceAbsolute) {
  throw 'The build directory must be outside the shared source directory.'
}
& $taskCmake -S $taskSourceRoot -B $BuildRoot -G 'Visual Studio 17 2022' -A x64 "-DCEF_ROOT=$CefRoot"
if ($LASTEXITCODE -ne 0) { throw 'CMake configure failed.' }
& $taskCmake --build $BuildRoot --config $Configuration --parallel 4
if ($LASTEXITCODE -ne 0) { throw 'Build failed.' }
if ($RunTests) {
  $taskCtest = Join-Path (Split-Path -Parent $taskCmake) 'ctest.exe'
  & $taskCtest --test-dir $BuildRoot -C $Configuration --output-on-failure
  if ($LASTEXITCODE -ne 0) { throw 'Core tests failed.' }
}
Write-Output "Executable: $(Join-Path $BuildRoot "$Configuration/oaClient2.exe")"
