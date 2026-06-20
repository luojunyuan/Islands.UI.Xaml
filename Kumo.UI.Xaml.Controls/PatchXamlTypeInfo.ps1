param(
    [Parameter(Mandatory = $true)]
    [string]$Path
)

$text = Get-Content -Raw -LiteralPath $Path
$original = $text
$preambleInclude = '#include "KumoPreamble.ixx"'
$activationInclude = '#include "XamlTypeInfoActivationIncludes.ixx"'

$text = $text -replace '#include\s+"pch\.h"', $preambleInclude
$text = $text -replace '#include\s+"XamlTypeInfoActivationIncludes\.h"', $activationInclude

if ([System.IO.Path]::GetFileName($Path) -eq 'XamlTypeInfo.Impl.g.cpp' -and $text -notmatch [regex]::Escape($activationInclude)) {
    $text = $text -replace "($([regex]::Escape($preambleInclude))\s*\r?\n)", "`$1$activationInclude`r`n"
}

if ($text -ne $original) {
    Set-Content -LiteralPath $Path -Value $text -NoNewline -Encoding UTF8
}
