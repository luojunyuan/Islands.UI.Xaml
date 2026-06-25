param(
    [Parameter(Mandatory = $true)]
    [string]$Path
)

$text = Get-Content -Raw -LiteralPath $Path
$pchInclude = '#include "pch.h"'
$workaroundInclude = '#include "XamlWorkaround.h"'
$activationInclude = '#include "XamlTypeInfoActivationIncludes.h"'
$fileName = Split-Path -Leaf $Path

$text = $text -replace '#include pch\.h`r`n#include XamlTypeInfoActivationIncludes\.h"', "$pchInclude`r`n$activationInclude"

$text = $text -replace '(?m)^#include\s+"CppBaseIncludes\.h"\s*\r?\n', ''
$text = $text -replace '(?m)^import\s+CppWinRTModules;\s*\r?\n', ''

if ($text -notmatch [regex]::Escape($workaroundInclude)) {
    $text = $text -replace '(#include\s+"pch\.h"\s*\r?\n)', "`$1$workaroundInclude`r`n"
}

if ($fileName -eq 'XamlTypeInfo.g.cpp' -and $text -notmatch [regex]::Escape($activationInclude)) {
    if ($text -match [regex]::Escape($workaroundInclude)) {
        $text = $text -replace "($([regex]::Escape($workaroundInclude))\s*\r?\n)", "`$1$activationInclude`r`n"
    }
    else {
        $text = $text -replace '(#include\s+"pch\.h"\s*\r?\n)', "`$1$activationInclude`r`n"
    }
}

Set-Content -LiteralPath $Path -Value $text -NoNewline -Encoding UTF8
