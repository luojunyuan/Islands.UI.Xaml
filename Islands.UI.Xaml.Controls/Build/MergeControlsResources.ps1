param(
    [Parameter(Mandatory = $true)]
    [string]$ManifestPath,

    [Parameter(Mandatory = $true)]
    [string]$OutputDirectory,

    [Parameter(Mandatory = $true)]
    [string]$ResourceRoot
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$presentationNamespace = 'http://schemas.microsoft.com/winfx/2006/xaml/presentation'
$xamlNamespace = 'http://schemas.microsoft.com/winfx/2006/xaml'
$xmlNamespace = 'http://www.w3.org/2000/xmlns/'

$preferredPrefixes = @{
    $xamlNamespace = 'x'
    'using:Islands.UI.Xaml.Controls' = 'controls'
    'using:Islands.UI.Xaml.Controls.Primitives' = 'primitives'
    'using:Microsoft.UI.Xaml.Controls' = 'muxc'
    'using:Microsoft.UI.Xaml.Controls.AnimatedVisuals' = 'animatedvisuals'
}

function Get-ResourceKey {
    param([System.Xml.XmlNode]$Node)

    if ($null -eq $Node.Attributes) {
        return ''
    }

    foreach ($attribute in $Node.Attributes) {
        if (($attribute.LocalName -eq 'Key' -or $attribute.LocalName -eq 'Name') -and
            $attribute.NamespaceURI -eq $xamlNamespace) {
            return $attribute.Value
        }
    }

    if ($Node.LocalName -eq 'Style') {
        $targetType = $Node.Attributes['TargetType']
        if ($null -ne $targetType) {
            return $targetType.Value
        }
    }

    return ''
}

function New-ResourceBucket {
    return [pscustomobject]@{
        Nodes = [System.Collections.Generic.List[System.Xml.XmlNode]]::new()
        KeyIndexes = [System.Collections.Generic.Dictionary[string, int]]::new([System.StringComparer]::Ordinal)
    }
}

function Add-ResourceNode {
    param(
        [Parameter(Mandatory = $true)]
        $Bucket,

        [Parameter(Mandatory = $true)]
        [System.Xml.XmlNode]$Node
    )

    $key = Get-ResourceKey $Node
    if ($key.Length -gt 0 -and $Bucket.KeyIndexes.ContainsKey($key)) {
        $Bucket.Nodes[$Bucket.KeyIndexes[$key]] = $Node
        return
    }

    if ($key.Length -gt 0) {
        $Bucket.KeyIndexes.Add($key, $Bucket.Nodes.Count)
    }

    $Bucket.Nodes.Add($Node)
}

function Get-UniquePrefix {
    param(
        [Parameter(Mandatory = $true)]
        [string]$PreferredPrefix,

        [Parameter(Mandatory = $true)]
        [string]$NamespaceUri,

        [Parameter(Mandatory = $true)]
        [System.Collections.Generic.Dictionary[string, string]]$NamespaceByPrefix
    )

    if (-not $NamespaceByPrefix.ContainsKey($PreferredPrefix) -or
        $NamespaceByPrefix[$PreferredPrefix] -eq $NamespaceUri) {
        return $PreferredPrefix
    }

    $suffix = 2
    do {
        $candidate = "$PreferredPrefix$suffix"
        $suffix++
    } while ($NamespaceByPrefix.ContainsKey($candidate) -and
             $NamespaceByPrefix[$candidate] -ne $NamespaceUri)

    return $candidate
}

function Update-NamespacePrefixes {
    param(
        [Parameter(Mandatory = $true)]
        [System.Xml.XmlNode]$Node,

        [Parameter(Mandatory = $true)]
        [System.Collections.Generic.Dictionary[string, string]]$PrefixReplacements
    )

    if ($Node.Prefix.Length -gt 0 -and $PrefixReplacements.ContainsKey($Node.Prefix)) {
        $Node.Prefix = $PrefixReplacements[$Node.Prefix]
    }

    if ($null -ne $Node.Attributes) {
        foreach ($attribute in $Node.Attributes) {
            if ($attribute.Prefix -eq 'xmlns' -or $attribute.Name -eq 'xmlns') {
                continue
            }

            if ($attribute.Prefix.Length -gt 0 -and $PrefixReplacements.ContainsKey($attribute.Prefix)) {
                $attribute.Prefix = $PrefixReplacements[$attribute.Prefix]
            }

            foreach ($oldPrefix in $PrefixReplacements.Keys) {
                $attribute.Value = $attribute.Value.Replace(
                    "${oldPrefix}:",
                    "$($PrefixReplacements[$oldPrefix]):")
            }
        }
    }

    foreach ($child in $Node.ChildNodes) {
        Update-NamespacePrefixes $child $PrefixReplacements
    }
}

function Merge-ResourceDictionaries {
    param(
        [Parameter(Mandatory = $true)]
        [AllowEmptyCollection()]
        [string[]]$InputFiles,

        [Parameter(Mandatory = $true)]
        [string]$OutputPath,

        [string]$MergedDictionarySource
    )

    $outputDocument = [System.Xml.XmlDocument]::new()
    $outputDocument.PreserveWhitespace = $false
    $root = $outputDocument.CreateElement('ResourceDictionary', $presentationNamespace)
    [void]$outputDocument.AppendChild($root)
    $xNamespaceAttribute = $outputDocument.CreateAttribute('xmlns', 'x', $xmlNamespace)
    $xNamespaceAttribute.Value = $xamlNamespace
    [void]$root.Attributes.Append($xNamespaceAttribute)

    $namespaceByPrefix = [System.Collections.Generic.Dictionary[string, string]]::new([System.StringComparer]::Ordinal)
    $prefixByNamespace = [System.Collections.Generic.Dictionary[string, string]]::new([System.StringComparer]::Ordinal)
    $namespaceByPrefix.Add('x', $xamlNamespace)
    $prefixByNamespace.Add($xamlNamespace, 'x')

    $resources = New-ResourceBucket
    $themeBuckets = [System.Collections.Generic.Dictionary[string, object]]::new([System.StringComparer]::Ordinal)
    $themeOrder = [System.Collections.Generic.List[string]]::new()

    foreach ($inputFile in $InputFiles) {
        if ([string]::IsNullOrWhiteSpace($inputFile)) {
            continue
        }

        if (-not (Test-Path -LiteralPath $inputFile)) {
            throw "Controls resource input was not found: $inputFile"
        }

        $inputDocument = [System.Xml.XmlDocument]::new()
        $inputDocument.PreserveWhitespace = $false
        $inputDocument.Load($inputFile)

        $inputRoot = $inputDocument.DocumentElement
        if ($null -eq $inputRoot -or $inputRoot.LocalName -ne 'ResourceDictionary') {
            throw "Controls resource input must have ResourceDictionary as its root: $inputFile"
        }

        $prefixReplacements = [System.Collections.Generic.Dictionary[string, string]]::new([System.StringComparer]::Ordinal)

        foreach ($attribute in $inputRoot.Attributes) {
            if ($attribute.Prefix -ne 'xmlns') {
                continue
            }

            $oldPrefix = $attribute.LocalName
            $namespaceUri = $attribute.Value

            if ($prefixByNamespace.ContainsKey($namespaceUri)) {
                $newPrefix = $prefixByNamespace[$namespaceUri]
            }
            else {
                $preferredPrefix = if ($preferredPrefixes.ContainsKey($namespaceUri)) {
                    $preferredPrefixes[$namespaceUri]
                }
                else {
                    $oldPrefix
                }

                $newPrefix = Get-UniquePrefix $preferredPrefix $namespaceUri $namespaceByPrefix
                $namespaceByPrefix[$newPrefix] = $namespaceUri
                $prefixByNamespace[$namespaceUri] = $newPrefix
                $namespaceAttribute = $outputDocument.CreateAttribute('xmlns', $newPrefix, $xmlNamespace)
                $namespaceAttribute.Value = $namespaceUri
                [void]$root.Attributes.Append($namespaceAttribute)
            }

            if ($oldPrefix -ne $newPrefix) {
                $prefixReplacements[$oldPrefix] = $newPrefix
            }
        }

        foreach ($inputNode in $inputRoot.ChildNodes) {
            if ($inputNode.NodeType -eq [System.Xml.XmlNodeType]::Comment -or
                $inputNode.NodeType -eq [System.Xml.XmlNodeType]::Whitespace -or
                $inputNode.NodeType -eq [System.Xml.XmlNodeType]::SignificantWhitespace) {
                continue
            }

            $node = $outputDocument.ImportNode($inputNode, $true)
            Update-NamespacePrefixes $node $prefixReplacements

            if ($node.LocalName -eq 'ResourceDictionary.ThemeDictionaries') {
                foreach ($themeDictionary in $node.ChildNodes) {
                    if ($themeDictionary.NodeType -ne [System.Xml.XmlNodeType]::Element) {
                        continue
                    }

                    $themeKey = Get-ResourceKey $themeDictionary
                    if ([string]::IsNullOrEmpty($themeKey)) {
                        continue
                    }

                    if ($themeKey -eq 'Dark') {
                        $themeKey = 'Default'
                    }

                    if (-not $themeBuckets.ContainsKey($themeKey)) {
                        $themeBuckets.Add($themeKey, (New-ResourceBucket))
                        [void]$themeOrder.Add($themeKey)
                    }

                    foreach ($themeResource in $themeDictionary.ChildNodes) {
                        if ($themeResource.NodeType -eq [System.Xml.XmlNodeType]::Element) {
                            Add-ResourceNode $themeBuckets[$themeKey] $themeResource
                        }
                    }
                }
            }
            else {
                Add-ResourceNode $resources $node
            }
        }
    }

    if (-not [string]::IsNullOrWhiteSpace($MergedDictionarySource)) {
        $mergedDictionaries = $outputDocument.CreateElement('ResourceDictionary.MergedDictionaries', $presentationNamespace)
        $mergedDictionary = $outputDocument.CreateElement('ResourceDictionary', $presentationNamespace)
        [void]$mergedDictionary.SetAttribute('Source', $MergedDictionarySource)
        [void]$mergedDictionaries.AppendChild($mergedDictionary)
        [void]$root.AppendChild($mergedDictionaries)
    }

    if ($themeOrder.Count -gt 0) {
        $themeDictionaries = $outputDocument.CreateElement('ResourceDictionary.ThemeDictionaries', $presentationNamespace)
        foreach ($themeKey in $themeOrder) {
            $themeDictionary = $outputDocument.CreateElement('ResourceDictionary', $presentationNamespace)
            [void]$themeDictionary.SetAttribute('Key', $xamlNamespace, $themeKey)
            foreach ($themeResource in $themeBuckets[$themeKey].Nodes) {
                [void]$themeDictionary.AppendChild($themeResource)
            }
            [void]$themeDictionaries.AppendChild($themeDictionary)
        }
        [void]$root.AppendChild($themeDictionaries)
    }

    foreach ($resource in $resources.Nodes) {
        [void]$root.AppendChild($resource)
    }

    $settings = [System.Xml.XmlWriterSettings]::new()
    $settings.Indent = $true
    $settings.OmitXmlDeclaration = $true
    $settings.Encoding = [System.Text.UTF8Encoding]::new($false)
    $settings.NewLineChars = "`r`n"
    $settings.NewLineHandling = [System.Xml.NewLineHandling]::Replace

    $stringBuilder = [System.Text.StringBuilder]::new()
    $stringWriter = [System.IO.StringWriter]::new($stringBuilder, [System.Globalization.CultureInfo]::InvariantCulture)
    $writer = [System.Xml.XmlWriter]::Create($stringWriter, $settings)
    try {
        $outputDocument.WriteTo($writer)
        $writer.Flush()
    }
    finally {
        $writer.Dispose()
        $stringWriter.Dispose()
    }

    $content = $stringBuilder.ToString() + "`r`n"
    if ((Test-Path -LiteralPath $OutputPath) -and
        [System.IO.File]::ReadAllText($OutputPath) -eq $content) {
        return
    }

    [System.IO.File]::WriteAllText($OutputPath, $content, [System.Text.UTF8Encoding]::new($false))
}

$pagesByType = @{
    DefaultStyle = [System.Collections.Generic.List[string]]::new()
    ThemeResources = [System.Collections.Generic.List[string]]::new()
    StylePerf2026 = [System.Collections.Generic.List[string]]::new()
    ThemeResourcesPerf2026 = [System.Collections.Generic.List[string]]::new()
}

foreach ($line in [System.IO.File]::ReadAllLines($ManifestPath)) {
    if ([string]::IsNullOrWhiteSpace($line)) {
        continue
    }

    $separator = $line.IndexOf('|')
    if ($separator -lt 1) {
        throw "Invalid controls resource manifest line: $line"
    }

    $type = $line.Substring(0, $separator)
    $path = $line.Substring($separator + 1)
    if (-not $pagesByType.ContainsKey($type)) {
        throw "Unknown controls resource type '$type' in $ManifestPath"
    }

    $pagesByType[$type].Add($path)
}

[System.IO.Directory]::CreateDirectory($OutputDirectory) | Out-Null

Merge-ResourceDictionaries `
    -InputFiles $pagesByType.DefaultStyle.ToArray() `
    -OutputPath (Join-Path $OutputDirectory 'generic.xaml') `
    -MergedDictionarySource "ms-appx:///$ResourceRoot/Themes/themeresources.xaml"

Merge-ResourceDictionaries `
    -InputFiles $pagesByType.ThemeResources.ToArray() `
    -OutputPath (Join-Path $OutputDirectory 'themeresources.xaml')

Merge-ResourceDictionaries `
    -InputFiles $pagesByType.StylePerf2026.ToArray() `
    -OutputPath (Join-Path $OutputDirectory 'generic_perf2026.xaml') `
    -MergedDictionarySource "ms-appx:///$ResourceRoot/Themes/themeresources_perf2026.xaml"

Merge-ResourceDictionaries `
    -InputFiles $pagesByType.ThemeResourcesPerf2026.ToArray() `
    -OutputPath (Join-Path $OutputDirectory 'themeresources_perf2026.xaml')
