param(
    [Parameter(Mandatory = $true)]
    [string]$Path
)

$text = Get-Content -Raw -LiteralPath $Path
$pchInclude = '#include "pch.h"'
$activationInclude = '#include "XamlTypeInfoActivationIncludes.h"'

$text = $text -replace '#include pch\.h`r`n#include XamlTypeInfoActivationIncludes\.h"', "$pchInclude`r`n$activationInclude"

if ($text -notmatch [regex]::Escape($activationInclude)) {
    $text = $text -replace '(#include\s+"pch\.h"\s*\r?\n)', "`$1$activationInclude`r`n"
}

Set-Content -LiteralPath $Path -Value $text -NoNewline -Encoding UTF8
