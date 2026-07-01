[CmdletBinding()]
param(
  [string]$Version = "0.1.0-local",
  [string]$Configuration = "Release",
  [string]$ArtifactsPath = (Join-Path $PSScriptRoot "..\artifacts"),
  [string]$OutputPath = (Join-Path $PSScriptRoot "..\artifacts\packages"),
  [string[]]$Architectures = @("x86", "x64", "arm64"),
  [switch]$AllowMissingArchitectures,
  [switch]$IncludePdb
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$packageId = "Islands.UI.Xaml"
$tfm = "net10.0-windows10.0.26100.0"

function Get-FullPath {
  param([string]$Path)

  if ([System.IO.Path]::IsPathRooted($Path)) {
    return [System.IO.Path]::GetFullPath($Path)
  }

  return [System.IO.Path]::GetFullPath((Join-Path (Get-Location) $Path))
}

$artifactsRoot = Get-FullPath -Path $ArtifactsPath
$outputRoot = Get-FullPath -Path $OutputPath
$stagingRoot = [System.IO.Path]::GetFullPath((Join-Path $artifactsRoot "obj\NuGetPack\$packageId"))
$safeStagingBase = [System.IO.Path]::GetFullPath((Join-Path $artifactsRoot "obj\NuGetPack"))
$nuspecPath = Join-Path $PSScriptRoot "$packageId.nuspec"

function Remove-StagingDirectory {
  param([string]$Path)

  if (-not (Test-Path -LiteralPath $Path)) {
    return
  }

  $resolvedPath = [System.IO.Path]::GetFullPath((Resolve-Path -LiteralPath $Path).Path)
  if (-not $resolvedPath.StartsWith($safeStagingBase, [System.StringComparison]::OrdinalIgnoreCase)) {
    throw "Refusing to delete staging path outside '$safeStagingBase': $resolvedPath"
  }

  Remove-Item -LiteralPath $resolvedPath -Recurse -Force
}

function Find-ArtifactDirectory {
  param(
    [string]$Root,
    [string[]]$Pivots
  )

  foreach ($pivot in $Pivots) {
    $candidate = Join-Path $Root $pivot
    if (Test-Path -LiteralPath $candidate -PathType Container) {
      return $candidate
    }
  }

  return $null
}

function Copy-RequiredFile {
  param(
    [string]$Source,
    [string]$Destination,
    [System.Collections.Generic.List[string]]$Missing
  )

  if (-not (Test-Path -LiteralPath $Source -PathType Leaf)) {
    $Missing.Add($Source)
    return
  }

  New-Item -ItemType Directory -Force -Path (Split-Path -Parent $Destination) | Out-Null
  Copy-Item -LiteralPath $Source -Destination $Destination -Force
}

function Copy-OptionalFile {
  param(
    [string]$Source,
    [string]$Destination
  )

  if (Test-Path -LiteralPath $Source -PathType Leaf) {
    New-Item -ItemType Directory -Force -Path (Split-Path -Parent $Destination) | Out-Null
    Copy-Item -LiteralPath $Source -Destination $Destination -Force
  }
}

function Add-NuGetPackagingAssemblies {
  $dotnetInfo = & dotnet --info
  $sdkBasePath = ($dotnetInfo | Select-String -Pattern "^\s*Base Path:\s*(.+)$" | Select-Object -First 1).Matches.Groups[1].Value.Trim()
  if (-not $sdkBasePath) {
    throw "Unable to locate the .NET SDK base path from 'dotnet --info'."
  }

  foreach ($assemblyName in @("NuGet.Versioning.dll", "NuGet.Frameworks.dll", "NuGet.Common.dll", "NuGet.Packaging.dll")) {
    $assemblyPath = Join-Path $sdkBasePath $assemblyName
    if (-not (Test-Path -LiteralPath $assemblyPath -PathType Leaf)) {
      throw "Unable to locate $assemblyName at '$assemblyPath'."
    }

    Add-Type -Path $assemblyPath
  }
}

function New-Package {
  param(
    [string]$Nuspec,
    [string]$BasePath,
    [string]$OutputFile
  )

  Add-NuGetPackagingAssemblies
  $propertyProvider = [System.Func[string, string]] {
    param([string]$name)

    if ($name -eq "version") {
      return $Version
    }

    return $null
  }

  $builder = [NuGet.Packaging.PackageBuilder]::new($Nuspec, $BasePath, $propertyProvider, $false)
  New-Item -ItemType Directory -Force -Path (Split-Path -Parent $OutputFile) | Out-Null
  if (Test-Path -LiteralPath $OutputFile -PathType Leaf) {
    Remove-Item -LiteralPath $OutputFile -Force
  }

  $stream = [System.IO.File]::Create($OutputFile)
  try {
    $builder.Save($stream)
  }
  finally {
    $stream.Dispose()
  }
}

$architectureMap = @{
  x86 = @{
    Rid = "win-x86"
    NativePivots = @("${Configuration}_x86", "${Configuration}_Win32")
    ProjectionPivots = @("${Configuration}_x86", "${Configuration}_Win32")
  }
  x64 = @{
    Rid = "win-x64"
    NativePivots = @("${Configuration}_x64")
    ProjectionPivots = @("${Configuration}_x64")
  }
  arm64 = @{
    Rid = "win-arm64"
    NativePivots = @("${Configuration}_ARM64", "${Configuration}_arm64")
    ProjectionPivots = @("${Configuration}_ARM64", "${Configuration}_arm64")
  }
}

Remove-StagingDirectory -Path $stagingRoot
New-Item -ItemType Directory -Force -Path $stagingRoot | Out-Null

Copy-Item -LiteralPath (Join-Path $PSScriptRoot "build") -Destination $stagingRoot -Recurse -Force
Copy-Item -LiteralPath (Join-Path $PSScriptRoot "buildTransitive") -Destination $stagingRoot -Recurse -Force

$missing = [System.Collections.Generic.List[string]]::new()
$includedArchitectures = [System.Collections.Generic.List[string]]::new()
$nativeRoot = Join-Path $artifactsRoot "bin\Islands.UI.Xaml"
$projectionRoot = Join-Path $artifactsRoot "bin\Islands.UI.Xaml.Controls.Projection"

foreach ($architecture in $Architectures) {
  $key = $architecture.ToLowerInvariant()
  if (-not $architectureMap.ContainsKey($key)) {
    throw "Unsupported architecture '$architecture'. Use x86, x64, or arm64."
  }

  $entry = $architectureMap[$key]
  $rid = $entry.Rid
  $nativeDir = Find-ArtifactDirectory -Root $nativeRoot -Pivots $entry.NativePivots
  $projectionDir = Find-ArtifactDirectory -Root $projectionRoot -Pivots $entry.ProjectionPivots
  $architectureMissing = [System.Collections.Generic.List[string]]::new()

  if (-not $nativeDir) {
    $architectureMissing.Add("Native output directory: $nativeRoot\$($entry.NativePivots -join ' or ')")
  }

  if (-not $projectionDir) {
    $architectureMissing.Add("Projection output directory: $projectionRoot\$($entry.ProjectionPivots -join ' or ')")
  }

  if ($nativeDir -and $projectionDir) {
    $nativeTarget = Join-Path $stagingRoot "runtimes\$rid\native"
    $projectionTarget = Join-Path $stagingRoot "runtimes\$rid\lib\$tfm"
    $libTarget = Join-Path $stagingRoot "build\native\lib\$key"
    $priTarget = Join-Path $stagingRoot "build\native\pri\$key"

    Copy-RequiredFile -Source (Join-Path $nativeDir "Islands.UI.Xaml.Controls.dll") -Destination (Join-Path $nativeTarget "Islands.UI.Xaml.Controls.dll") -Missing $architectureMissing
    Copy-RequiredFile -Source (Join-Path $nativeDir "Islands.UI.Xaml.Controls.pri") -Destination (Join-Path $priTarget "Islands.UI.Xaml.Controls.pri") -Missing $architectureMissing
    Copy-RequiredFile -Source (Join-Path $nativeDir "Islands.UI.Xaml.Controls.winmd") -Destination (Join-Path $nativeTarget "Islands.UI.Xaml.Controls.winmd") -Missing $architectureMissing
    Copy-OptionalFile -Source (Join-Path $nativeDir "Islands.UI.Xaml.Automation.winmd") -Destination (Join-Path $nativeTarget "Islands.UI.Xaml.Automation.winmd")
    Copy-OptionalFile -Source (Join-Path $nativeDir "Microsoft.Web.WebView2.Core.dll") -Destination (Join-Path $nativeTarget "Microsoft.Web.WebView2.Core.dll")
    Copy-OptionalFile -Source (Join-Path $nativeDir "Islands.UI.Xaml.Controls.lib") -Destination (Join-Path $libTarget "Islands.UI.Xaml.Controls.lib")

    Copy-RequiredFile -Source (Join-Path $projectionDir "Islands.UI.Xaml.Controls.Projection.dll") -Destination (Join-Path $projectionTarget "Islands.UI.Xaml.Controls.Projection.dll") -Missing $architectureMissing
    Copy-OptionalFile -Source (Join-Path $projectionDir "Islands.UI.Xaml.Controls.Projection.deps.json") -Destination (Join-Path $projectionTarget "Islands.UI.Xaml.Controls.Projection.deps.json")
    Copy-OptionalFile -Source (Join-Path $projectionDir "Microsoft.Web.WebView2.Core.Projection.dll") -Destination (Join-Path $projectionTarget "Microsoft.Web.WebView2.Core.Projection.dll")

    if ($IncludePdb) {
      Copy-OptionalFile -Source (Join-Path $nativeDir "Islands.UI.Xaml.Controls.pdb") -Destination (Join-Path $nativeTarget "Islands.UI.Xaml.Controls.pdb")
      Copy-OptionalFile -Source (Join-Path $projectionDir "Islands.UI.Xaml.Controls.Projection.pdb") -Destination (Join-Path $projectionTarget "Islands.UI.Xaml.Controls.Projection.pdb")
    }
  }

  if ($architectureMissing.Count -gt 0) {
    foreach ($item in $architectureMissing) {
      $missing.Add("[$key] $item")
    }

    if (-not $AllowMissingArchitectures) {
      continue
    }
  }
  else {
    $includedArchitectures.Add($key)
  }
}

if ($missing.Count -gt 0 -and -not $AllowMissingArchitectures) {
  $message = "Cannot create $packageId.$Version because required artifacts are missing:`n  " + ($missing -join "`n  ")
  throw $message
}

if ($includedArchitectures.Count -eq 0) {
  throw "No architectures were staged. Missing artifacts:`n  $($missing -join "`n  ")"
}

if ($missing.Count -gt 0) {
  Write-Warning ("Skipping missing architectures/assets:`n  " + ($missing -join "`n  "))
}

$packagePath = Join-Path $outputRoot "$packageId.$Version.nupkg"
New-Package -Nuspec $nuspecPath -BasePath $stagingRoot -OutputFile $packagePath

Write-Host "Created package: $packagePath"
Write-Host "Included architectures: $($includedArchitectures -join ', ')"
