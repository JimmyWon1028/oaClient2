param(
  [Parameter(Mandatory = $true)][string]$Php,
  [Parameter(Mandatory = $true)][string]$ApiRoot,
  [Parameter(Mandatory = $true)][string]$TestRoot,
  [switch]$Snapshot
)

$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path $PSScriptRoot -Parent
$apiPath = (Resolve-Path -LiteralPath $ApiRoot).Path
$phpPath = (Resolve-Path -LiteralPath $Php).Path
$isolatedRoot = [IO.Path]::GetFullPath($TestRoot)
if ($isolatedRoot.StartsWith($apiPath + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase) -or $isolatedRoot -eq $apiPath) {
  throw 'TestRoot must be outside the API project.'
}
if (Test-Path -LiteralPath (Join-Path $isolatedRoot '.env')) {
  throw 'TestRoot must not contain an environment file.'
}
#2026.11.17 by codex, isolate Laravel generated files and read vendor libraries without booting the real application.
foreach ($directory in @('bootstrap/cache', 'config', 'storage/framework/views', 'storage/framework/sessions', 'storage/logs')) {
  New-Item -ItemType Directory -Path (Join-Path $isolatedRoot $directory) -Force | Out-Null
}
$variableNames = @('OA_HELPER_TEST_VENDOR', 'OA_HELPER_TEST_ROOT', 'OA_HELPER_TEST_APP')
$previous = @{}
foreach ($name in $variableNames) { $previous[$name] = [Environment]::GetEnvironmentVariable($name, 'Process') }
try {
  $env:OA_HELPER_TEST_VENDOR = Join-Path $apiPath 'vendor'
  $env:OA_HELPER_TEST_ROOT = $isolatedRoot
  $sourceRoot = if ($Snapshot) { Join-Path $projectRoot 'docs/desktop-helper/server/api' } else { $apiPath }
  $env:OA_HELPER_TEST_APP = Join-Path $sourceRoot 'app'
  $phpOptions = @('-n', '-d', ('extension_dir=' + (Join-Path (Split-Path $phpPath -Parent) 'ext')),
    '-d', 'extension=mbstring', '-d', 'extension=pdo_sqlite')
  foreach ($file in @('app/Util/DesktopHelper.php', 'app/Http/Event/Bsi020010Event.php',
      'app/Http/Controllers/DesktopHelperController.php', 'tests/Feature/DesktopHelperTest.php')) {
    & $phpPath @phpOptions -l (Join-Path $sourceRoot $file)
    if ($LASTEXITCODE -ne 0) { throw "PHP lint failed: $file" }
  }
  & $phpPath @phpOptions (Join-Path $apiPath 'vendor/phpunit/phpunit/phpunit') --no-configuration --do-not-cache-result `
    --bootstrap (Join-Path $PSScriptRoot 'desktop_helper_php_bootstrap.php') (Join-Path $sourceRoot 'tests/Feature/DesktopHelperTest.php')
  if ($LASTEXITCODE -ne 0) { throw 'Desktop helper PHP tests failed.' }
} finally {
  foreach ($name in $variableNames) { [Environment]::SetEnvironmentVariable($name, $previous[$name], 'Process') }
}
