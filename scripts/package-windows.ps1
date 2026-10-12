param(
  [string]$BuildRoot = (Join-Path $env:LOCALAPPDATA 'oaClient2/build/windows-x64'),
  [ValidateSet('Debug', 'Release')][string]$Configuration = 'Release'
)

$ErrorActionPreference = 'Stop'
$taskProject = Split-Path -Parent $PSScriptRoot
$taskSource = Join-Path $BuildRoot $Configuration
$taskDestination = Join-Path $taskProject 'artifacts/oaClient2'
if (-not (Test-Path -LiteralPath (Join-Path $taskSource 'oaClient2.exe')) -or
    -not (Test-Path -LiteralPath (Join-Path $taskSource 'cef/libcef.dll')) -or
    (Test-Path -LiteralPath (Join-Path $taskSource 'cef/oaClient2.dll'))) {
  throw 'Build the standalone oaClient2 EXE with the clean cef runtime directory first.'
}
New-Item -ItemType Directory -Path $taskDestination -Force | Out-Null
Copy-Item -LiteralPath (Join-Path $taskSource 'oaClient2.exe') -Destination $taskDestination -Force
Copy-Item -LiteralPath (Join-Path $taskSource 'cef') -Destination $taskDestination -Recurse -Force
# The user maintains delivery/prg; do not restore files from the source archive.
# Remove only application binaries from the superseded bootstrap/DLL layout.
$taskDestinationAbsolute = [IO.Path]::GetFullPath($taskDestination)
foreach ($taskName in @('cef/oaClient2.exe', 'cef/oaClient2.dll', 'oaClient2.dll')) {
  $taskOldApplication = [IO.Path]::GetFullPath((Join-Path $taskDestination $taskName))
  if (-not $taskOldApplication.StartsWith($taskDestinationAbsolute + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase)) {
    throw 'The obsolete application path escaped artifacts/oaClient2.'
  }
  if (Test-Path -LiteralPath $taskOldApplication) { Remove-Item -LiteralPath $taskOldApplication -Force }
}
# Remove only the obsolete flat runtime copies after the new runtime is staged.
foreach ($taskItem in (Get-ChildItem -LiteralPath (Join-Path $taskSource 'cef'))) {
  if ($taskItem.Name -eq 'oaClient2.exe') { continue }
  $taskOldPath = [IO.Path]::GetFullPath((Join-Path $taskDestination $taskItem.Name))
  if (-not $taskOldPath.StartsWith($taskDestinationAbsolute + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase)) {
    throw 'The obsolete runtime path escaped artifacts/oaClient2.'
  }
  if (Test-Path -LiteralPath $taskOldPath) {
    Remove-Item -LiteralPath $taskOldPath -Recurse -Force
  }
}
# Remove only the eight obsolete application image copies, now embedded in the EXE.
foreach ($taskName in @('oaClient-16.png', 'oaClient-32.png', 'oaClient-256.png', 'toolbar-console.png', 'toolbar-home.png', 'toolbar-server.png', 'toolbar-zoom-in.png', 'toolbar-zoom-out.png')) {
  $taskOldImage = Join-Path $taskDestination $taskName
  if (Test-Path -LiteralPath $taskOldImage) { Remove-Item -LiteralPath $taskOldImage -Force }
}
Copy-Item -LiteralPath (Join-Path $taskProject 'config/Config.example.ini') -Destination $taskDestination -Force
Write-Output "Windows delivery: $(Join-Path $taskDestination 'oaClient2.exe')"
