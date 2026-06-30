using System.Collections.Immutable;
using System.Diagnostics;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Text.RegularExpressions;
using System.Xml.Linq;
using System.Runtime.CompilerServices;

[assembly: InternalsVisibleTo("CppWinRTModuleFilterAnalyzer.Tests")]

var exitCode = await ProgramMain.RunAsync(args);
return exitCode;

internal static partial class ProgramMain
{
    public static async Task<int> RunAsync(string[] args)
    {
        try
        {
            var options = Options.Parse(args);
            if (options.ShowHelp)
            {
                Console.WriteLine(Options.HelpText);
                return 0;
            }

            var project = ProjectInfo.Load(options.ProjectPath, options.Configuration, options.Platform);
            var cppwinrt = CppWinRTLocator.Find(project);
            var rspFiles = ResponseFileSet.Find(project);

            Console.WriteLine($"Project: {project.ProjectPath}");
            Console.WriteLine($"Configuration: {project.Configuration}");
            Console.WriteLine($"Platform: {project.Platform}");
            Console.WriteLine($"C++/WinRT: {cppwinrt}");
            Console.WriteLine($"Response files: {rspFiles.Files.Count}");
            Console.WriteLine();

            var projectionGraphs = new List<ProjectionGraph>();
            var tempRoot = Path.Combine(Path.GetTempPath(), "cppwinrt-module-analysis-" + Guid.NewGuid().ToString("N"));
            try
            {
                Directory.CreateDirectory(tempRoot);
                foreach (var rspFile in rspFiles.Files)
                {
                    var projectionTemp = Path.Combine(tempRoot, Path.GetFileNameWithoutExtension(rspFile.Path));
                    var generatedDir = Path.Combine(projectionTemp, "Generated Files");
                    Directory.CreateDirectory(generatedDir);

                    var rewritten = ResponseRewriter.RewriteForUnfilteredModules(rspFile.Path, generatedDir);
                    var rewrittenRsp = Path.Combine(projectionTemp, Path.GetFileName(rspFile.Path));
                    await File.WriteAllTextAsync(rewrittenRsp, rewritten, Utf8NoBom);

                    await RunCppWinRTAsync(cppwinrt, rewrittenRsp);

                    var graph = ModuleGraph.Parse(Path.Combine(generatedDir, "winrt"), rspFile.Kind);
                    projectionGraphs.Add(graph);
                }
            }
            finally
            {
                DeleteDirectoryQuietly(tempRoot);
            }

            var mergedGraph = ModuleGraph.Merge(projectionGraphs);
            var sourceFiles = SourceFileFinder.Find(project);
            var sourceScan = SourceScanner.Scan(sourceFiles, mergedGraph);

            var roots = sourceScan.DirectModules.Concat(mergedGraph.ProjectComponentNamespaces(project));
            var include = mergedGraph.DependencyClosure(roots);
            var exclude = FilterCalculator.CalculateExcludes(include, mergedGraph.Namespaces);
            var validation = await FilterVerifier.VerifyAsync(cppwinrt, rspFiles, include, exclude);

            var report = AnalysisReport.Create(project, rspFiles, mergedGraph, sourceScan, include, exclude, validation);

            if (!string.IsNullOrWhiteSpace(options.OutputJson))
            {
                var jsonPath = Path.GetFullPath(options.OutputJson);
                Directory.CreateDirectory(Path.GetDirectoryName(jsonPath)!);
                await File.WriteAllTextAsync(jsonPath, JsonSerializer.Serialize(report, JsonOptions), Utf8NoBom);
                Console.WriteLine($"JSON report: {jsonPath}");
            }

            Console.WriteLine(XmlSnippetFormatter.Format(report));

            if (report.Warnings.Length > 0)
            {
                Console.WriteLine();
                Console.WriteLine("Warnings:");
                foreach (var warning in report.Warnings)
                {
                    Console.WriteLine($"- {warning}");
                }
            }

            return validation.IsExact ? 0 : 2;
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine("error: " + ex.Message);
            return 1;
        }
    }

    private static readonly JsonSerializerOptions JsonOptions = new()
    {
        WriteIndented = true,
        DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull
    };

    private static readonly UTF8Encoding Utf8NoBom = new(encoderShouldEmitUTF8Identifier: false);

    private static async Task RunCppWinRTAsync(string cppwinrt, string rspPath)
    {
        var startInfo = new ProcessStartInfo
        {
            FileName = cppwinrt,
            UseShellExecute = false,
            RedirectStandardError = true,
            RedirectStandardOutput = true
        };
        startInfo.ArgumentList.Add("@" + rspPath);

        using var process = Process.Start(startInfo) ?? throw new InvalidOperationException("Failed to start cppwinrt.exe.");
        var stdout = await process.StandardOutput.ReadToEndAsync();
        var stderr = await process.StandardError.ReadToEndAsync();
        await process.WaitForExitAsync();

        if (process.ExitCode != 0)
        {
            throw new InvalidOperationException($"cppwinrt.exe failed for {rspPath}.{Environment.NewLine}{stdout}{stderr}");
        }
    }

    private static void DeleteDirectoryQuietly(string path)
    {
        try
        {
            if (Directory.Exists(path))
            {
                Directory.Delete(path, recursive: true);
            }
        }
        catch
        {
            // Temporary analysis artifacts are best-effort cleanup only.
        }
    }

}

internal sealed record Options(
    string ProjectPath,
    string Configuration,
    string Platform,
    string? OutputJson,
    bool ShowHelp)
{
    public static Options Parse(string[] args)
    {
        var project = "";
        var configuration = "Debug";
        var platform = "ARM64";
        string? outputJson = null;

        for (var i = 0; i < args.Length; i++)
        {
            var arg = args[i];
            if (arg is "-h" or "--help" or "/?")
            {
                return new Options("", configuration, platform, outputJson, true);
            }

            static string ReadValue(string[] args, ref int index, string name)
            {
                if (index + 1 >= args.Length)
                {
                    throw new ArgumentException($"Missing value for {name}.");
                }
                index++;
                return args[index];
            }

            switch (arg)
            {
                case "--project":
                    project = ReadValue(args, ref i, arg);
                    break;
                case "--configuration":
                    configuration = ReadValue(args, ref i, arg);
                    break;
                case "--platform":
                    platform = ReadValue(args, ref i, arg);
                    break;
                case "--output-json":
                    outputJson = ReadValue(args, ref i, arg);
                    break;
                default:
                    throw new ArgumentException($"Unknown argument: {arg}");
            }
        }

        if (string.IsNullOrWhiteSpace(project))
        {
            throw new ArgumentException("--project is required.");
        }

        return new Options(Path.GetFullPath(project), configuration, platform, outputJson, false);
    }

    public const string HelpText = """
Usage:
  CppWinRTModuleFilterAnalyzer --project <path.vcxproj> [--configuration Debug] [--platform ARM64] [--output-json report.json]

The analyzer requires existing obj\<Platform>\<Configuration>\<ProjectName>\*.cppwinrt_*.rsp files from a prior build.
""";
}

internal sealed record ProjectInfo(
    string ProjectPath,
    string ProjectDirectory,
    string RepositoryRoot,
    string? IntDirectory,
    string ProjectName,
    string RootNamespace,
    string ProjectRootPrefix,
    string Configuration,
    string Platform,
    string? CppWinRTPackageVersion)
{
    public static ProjectInfo Load(string projectPath, string configuration, string platform)
    {
        if (!File.Exists(projectPath))
        {
            throw new FileNotFoundException("Project file was not found.", projectPath);
        }

        var doc = XDocument.Load(projectPath);
        var ns = doc.Root?.Name.Namespace ?? XNamespace.None;
        string? RawElementValue(string name) =>
            doc.Descendants(ns + name)
                .Select(e => e.Value.Trim())
                .FirstOrDefault(v => !string.IsNullOrWhiteSpace(v));
        string? ElementValue(string name) =>
            doc.Descendants(ns + name)
                .Select(e => e.Value.Trim())
                .FirstOrDefault(v => !string.IsNullOrWhiteSpace(v) && !v.Contains("$(", StringComparison.Ordinal));

        var projectDirectory = Path.GetDirectoryName(projectPath)!;
        var msBuildProjectName = Path.GetFileNameWithoutExtension(projectPath);
        var projectName = ElementValue("ProjectName") ?? Path.GetFileNameWithoutExtension(projectPath);
        var rootNamespace = ElementValue("RootNamespace") ?? projectName;
        var properties = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase)
        {
            ["Configuration"] = configuration,
            ["Platform"] = platform,
            ["MSBuildProjectDirectory"] = projectDirectory,
            ["MSBuildProjectName"] = msBuildProjectName,
            ["ProjectName"] = projectName,
            ["RootNamespace"] = rootNamespace
        };
        var intDirectory = ExpandDirectory(RawElementValue("IntDir"), projectDirectory, properties);
        var packageVersion = doc.Descendants(ns + "PackageReference")
            .Where(e => string.Equals((string?)e.Attribute("Include"), "Microsoft.Windows.CppWinRT", StringComparison.OrdinalIgnoreCase))
            .Select(e => (string?)e.Attribute("Version"))
            .FirstOrDefault();

        return new ProjectInfo(
            projectPath,
            projectDirectory,
            FindRepositoryRoot(projectDirectory),
            intDirectory,
            projectName,
            rootNamespace,
            ProjectRootPrefixFrom(rootNamespace),
            configuration,
            platform,
            packageVersion);
    }

    private static string? ExpandDirectory(string? value, string projectDirectory, IReadOnlyDictionary<string, string> properties)
    {
        if (string.IsNullOrWhiteSpace(value))
        {
            return null;
        }

        var expanded = Regex.Replace(value, @"\$\((?<name>[^)]+)\)", match =>
        {
            var name = match.Groups["name"].Value;
            return properties.TryGetValue(name, out var propertyValue) ? propertyValue : match.Value;
        });

        if (expanded.Contains("$(", StringComparison.Ordinal))
        {
            return null;
        }

        return Path.GetFullPath(Path.IsPathRooted(expanded)
            ? expanded
            : Path.Combine(projectDirectory, expanded));
    }

    private static string ProjectRootPrefixFrom(string rootNamespace)
    {
        var parts = rootNamespace.Split('.', StringSplitOptions.RemoveEmptyEntries);
        return parts.Length >= 2 ? string.Join('.', parts.Take(2)) : rootNamespace;
    }

    private static string FindRepositoryRoot(string start)
    {
        var current = new DirectoryInfo(start);
        while (current is not null)
        {
            if (Directory.Exists(Path.Combine(current.FullName, ".git")) || File.Exists(Path.Combine(current.FullName, "Islands.UI.Xaml.slnx")))
            {
                return current.FullName;
            }

            current = current.Parent;
        }

        return Path.GetFullPath(Path.Combine(start, ".."));
    }
}

internal static class CppWinRTLocator
{
    public static string Find(ProjectInfo project)
    {
        var versions = new List<string>();
        if (!string.IsNullOrWhiteSpace(project.CppWinRTPackageVersion))
        {
            versions.Add(project.CppWinRTPackageVersion);
        }

        var packageRoot = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), ".nuget", "packages", "microsoft.windows.cppwinrt");
        if (Directory.Exists(packageRoot))
        {
            versions.AddRange(Directory.EnumerateDirectories(packageRoot).Select(Path.GetFileName).Where(v => !string.IsNullOrWhiteSpace(v))!);
        }

        foreach (var version in versions.Distinct().OrderByDescending(v => v, StringComparer.OrdinalIgnoreCase))
        {
            var candidate = Path.Combine(packageRoot, version, "bin", "cppwinrt.exe");
            if (File.Exists(candidate))
            {
                return candidate;
            }
        }

        throw new FileNotFoundException("Could not find Microsoft.Windows.CppWinRT cppwinrt.exe in the NuGet package cache.");
    }
}

internal sealed record ResponseFile(string Path, string Kind);

internal sealed record ResponseFileSet(IReadOnlyList<ResponseFile> Files)
{
    public static ResponseFileSet Find(ProjectInfo project)
    {
        var intDirs = CandidateIntDirectories(project).Distinct(StringComparer.OrdinalIgnoreCase).ToArray();

        var projectFileName = Path.GetFileName(project.ProjectPath);
        var files = intDirs
            .Where(Directory.Exists)
            .SelectMany(intDir => Directory.EnumerateFiles(intDir, $"{projectFileName}.cppwinrt_*.rsp", SearchOption.TopDirectoryOnly))
            .Select(path => new ResponseFile(path, KindFromPath(path)))
            .OrderBy(file => file.Kind switch { "platform" => 0, "reference" => 1, "component" => 2, _ => 3 })
            .ToList();

        if (files.Count == 0)
        {
            var searched = string.Join(Environment.NewLine, intDirs.Select(path => "  " + path));
            throw new FileNotFoundException($"No C++/WinRT response files found. Build the project once before running the analyzer. Searched:{Environment.NewLine}{searched}");
        }

        return new ResponseFileSet(files);
    }

    private static IEnumerable<string> CandidateIntDirectories(ProjectInfo project)
    {
        if (!string.IsNullOrWhiteSpace(project.IntDirectory))
        {
            yield return project.IntDirectory;
        }

        yield return Path.Combine(project.RepositoryRoot, "obj", project.Platform, project.Configuration, project.ProjectName);
    }

    private static string KindFromPath(string path)
    {
        var name = Path.GetFileName(path);
        if (name.Contains("_plat.", StringComparison.OrdinalIgnoreCase)) return "platform";
        if (name.Contains("_ref.", StringComparison.OrdinalIgnoreCase)) return "reference";
        if (name.Contains("_comp.", StringComparison.OrdinalIgnoreCase)) return "component";
        return "unknown";
    }
}

internal static partial class ResponseRewriter
{
    public static string RewriteForUnfilteredModules(string rspPath, string generatedDir)
    {
        return Rewrite(rspPath, generatedDir, include: null, exclude: null);
    }

    public static string RewriteWithFilters(
        string rspPath,
        string generatedDir,
        ImmutableSortedSet<string> include,
        ImmutableSortedSet<string> exclude)
    {
        return Rewrite(rspPath, generatedDir, include, exclude);
    }

    private static string Rewrite(
        string rspPath,
        string generatedDir,
        ImmutableSortedSet<string>? include,
        ImmutableSortedSet<string>? exclude)
    {
        var text = File.ReadAllText(rspPath);
        var tokens = CommandLineTokenizer.Tokenize(text);
        var rewritten = new List<string>();

        for (var i = 0; i < tokens.Count; i++)
        {
            var token = tokens[i];
            if (token is "-module_include" or "-module_exclude")
            {
                i++;
                while (i < tokens.Count && !tokens[i].StartsWith("-", StringComparison.Ordinal))
                {
                    i++;
                }
                i--;
                continue;
            }

            if (token is "-out" or "-output")
            {
                i++;
                continue;
            }

            rewritten.Add(token);
        }

        if (!rewritten.Contains("-modules", StringComparer.Ordinal))
        {
            rewritten.Add("-modules");
        }

        if (include is { Count: > 0 })
        {
            rewritten.Add("-module_include");
            rewritten.AddRange(include);
        }

        if (exclude is { Count: > 0 })
        {
            rewritten.Add("-module_exclude");
            rewritten.AddRange(exclude);
        }

        rewritten.Add("-out");
        rewritten.Add(Path.Combine(generatedDir, "."));
        return CommandLineTokenizer.Join(rewritten);
    }
}

internal static class CommandLineTokenizer
{
    public static List<string> Tokenize(string text)
    {
        var result = new List<string>();
        var current = new StringBuilder();
        var inQuote = false;

        for (var i = 0; i < text.Length; i++)
        {
            var c = text[i];
            if (c == '"')
            {
                inQuote = !inQuote;
                continue;
            }

            if (char.IsWhiteSpace(c) && !inQuote)
            {
                Flush();
                continue;
            }

            current.Append(c);
        }

        Flush();
        return result;

        void Flush()
        {
            if (current.Length == 0)
            {
                return;
            }

            result.Add(current.ToString());
            current.Clear();
        }
    }

    public static string Join(IEnumerable<string> tokens) =>
        string.Join(Environment.NewLine, tokens.Select(QuoteIfNeeded));

    private static string QuoteIfNeeded(string token)
    {
        if (token.Length == 0 || token.Any(char.IsWhiteSpace))
        {
            return "\"" + token.Replace("\"", "\\\"", StringComparison.Ordinal) + "\"";
        }

        return token;
    }
}

internal sealed record ModuleInfo(string Namespace, string ModuleName, string FilePath, string ProjectionKind, ImmutableSortedSet<string> Imports);

internal sealed record ProjectionGraph(string Kind, ImmutableSortedDictionary<string, ModuleInfo> Modules)
{
    public ImmutableSortedSet<string> Namespaces => Modules.Keys.ToImmutableSortedSet(StringComparer.Ordinal);
}

internal sealed partial record ModuleGraph(ImmutableSortedDictionary<string, ModuleInfo> Modules)
{
    public ImmutableSortedSet<string> Namespaces => Modules.Keys.ToImmutableSortedSet(StringComparer.Ordinal);

    public ImmutableSortedSet<string> DependencyClosure(IEnumerable<string> roots)
    {
        var output = new SortedSet<string>(StringComparer.Ordinal);
        foreach (var root in roots)
        {
            Add(root);
        }

        return output.ToImmutableSortedSet(StringComparer.Ordinal);

        void Add(string moduleNamespace)
        {
            if (moduleNamespace is "winrt_base" or "winrt_numerics")
            {
                return;
            }

            if (!Modules.TryGetValue(moduleNamespace, out var module))
            {
                return;
            }

            if (!output.Add(module.Namespace))
            {
                return;
            }

            foreach (var dependency in module.Imports)
            {
                Add(dependency);
            }
        }
    }

    public ImmutableSortedSet<string> ProjectComponentNamespaces(ProjectInfo project)
    {
        var componentNamespaces = Modules.Values
            .Where(module => module.ProjectionKind == "component")
            .Select(module => module.Namespace)
            .Where(ns => ns is not "winrt_base" and not "winrt_numerics")
            .ToImmutableSortedSet(StringComparer.Ordinal);

        if (componentNamespaces.Count > 0)
        {
            return componentNamespaces;
        }

        return Modules.Keys
            .Where(ns => ns == project.RootNamespace || ns.StartsWith(project.RootNamespace + ".", StringComparison.Ordinal))
            .Where(ns => ns is not "winrt_base" and not "winrt_numerics")
            .ToImmutableSortedSet(StringComparer.Ordinal);
    }

    public IEnumerable<ModuleInfo> ProjectComponentModules(ProjectInfo project)
    {
        var namespaces = ProjectComponentNamespaces(project);
        foreach (var ns in namespaces)
        {
            if (Modules.TryGetValue(ns, out var module))
            {
                yield return module;
            }
        }
    }

    public static ProjectionGraph Parse(string winrtDir, string kind)
    {
        if (!Directory.Exists(winrtDir))
        {
            return new ProjectionGraph(kind, ImmutableSortedDictionary<string, ModuleInfo>.Empty.WithComparers(StringComparer.Ordinal));
        }

        var builder = ImmutableSortedDictionary.CreateBuilder<string, ModuleInfo>(StringComparer.Ordinal);
        foreach (var file in Directory.EnumerateFiles(winrtDir, "*.ixx", SearchOption.TopDirectoryOnly))
        {
            var moduleName = Path.GetFileNameWithoutExtension(file);
            var ns = NamespaceFromModuleName(moduleName);
            var imports = ImportRegex().Matches(File.ReadAllText(file))
                .Select(m => NamespaceFromModuleName(m.Groups["module"].Value))
                .Where(import => import != ns)
                .ToImmutableSortedSet(StringComparer.Ordinal);

            builder[ns] = new ModuleInfo(ns, moduleName, file, kind, imports);
        }

        return new ProjectionGraph(kind, builder.ToImmutable());
    }

    public static ModuleGraph Merge(IEnumerable<ProjectionGraph> graphs)
    {
        var builder = ImmutableSortedDictionary.CreateBuilder<string, ModuleInfo>(StringComparer.Ordinal);
        foreach (var graph in graphs)
        {
            foreach (var (ns, module) in graph.Modules)
            {
                if (builder.TryGetValue(ns, out var existing))
                {
                    builder[ns] = existing with
                    {
                        Imports = existing.Imports.Union(module.Imports),
                        ProjectionKind = existing.ProjectionKind == module.ProjectionKind ? existing.ProjectionKind : "multiple"
                    };
                }
                else
                {
                    builder[ns] = module;
                }
            }
        }

        return new ModuleGraph(builder.ToImmutable());
    }

    public static string NamespaceFromModuleName(string moduleName)
    {
        if (moduleName is "winrt_base" or "winrt_numerics")
        {
            return moduleName;
        }

        return moduleName.StartsWith("winrt.", StringComparison.Ordinal) ? moduleName["winrt.".Length..] : moduleName;
    }

    [GeneratedRegex(@"(?m)^\s*(?:export\s+)?import\s+(?<module>winrt(?:\.[A-Za-z0-9_]+)+|winrt_base|winrt_numerics)\s*;")]
    private static partial Regex ImportRegex();
}

internal static class SourceFileFinder
{
    private static readonly ImmutableHashSet<string> Extensions = ImmutableHashSet.Create(StringComparer.OrdinalIgnoreCase,
        ".h", ".hpp", ".hh", ".hxx", ".cpp", ".cxx", ".cc", ".ixx");

    public static ImmutableArray<string> Find(ProjectInfo project)
    {
        var files = Directory.EnumerateFiles(project.ProjectDirectory, "*", SearchOption.AllDirectories)
            .Where(path => Extensions.Contains(Path.GetExtension(path)))
            .Where(path => !IsUnder(path, Path.Combine(project.ProjectDirectory, "Generated Files")))
            .Where(path => !path.Contains($"{Path.DirectorySeparatorChar}obj{Path.DirectorySeparatorChar}", StringComparison.OrdinalIgnoreCase))
            .Where(path => !path.Contains($"{Path.DirectorySeparatorChar}bin{Path.DirectorySeparatorChar}", StringComparison.OrdinalIgnoreCase))
            .ToList();

        var sharedItems = XDocument.Load(project.ProjectPath)
            .Descendants()
            .Where(e => e.Name.LocalName == "Import" && string.Equals((string?)e.Attribute("Label"), "Shared", StringComparison.OrdinalIgnoreCase))
            .Select(e => (string?)e.Attribute("Project"))
            .Where(p => !string.IsNullOrWhiteSpace(p));

        foreach (var sharedItem in sharedItems)
        {
            var path = Path.GetFullPath(Path.Combine(project.ProjectDirectory, sharedItem!));
            if (!File.Exists(path))
            {
                continue;
            }

            var directory = Path.GetDirectoryName(path)!;
            files.AddRange(Directory.EnumerateFiles(directory, "*", SearchOption.AllDirectories)
                .Where(item => Extensions.Contains(Path.GetExtension(item))));
        }

        return files.Distinct(StringComparer.OrdinalIgnoreCase).OrderBy(path => path, StringComparer.OrdinalIgnoreCase).ToImmutableArray();
    }

    private static bool IsUnder(string path, string directory)
    {
        var relative = Path.GetRelativePath(directory, path);
        return !relative.StartsWith("..", StringComparison.Ordinal) && !Path.IsPathRooted(relative);
    }
}

internal sealed record SourceScanResult(
    ImmutableSortedSet<string> DirectModules,
    ImmutableSortedDictionary<string, ImmutableSortedSet<string>> Reasons,
    ImmutableSortedSet<string> UnresolvedShortNames,
    ImmutableArray<string> ScannedFiles);

internal static partial class SourceScanner
{
    public static SourceScanResult Scan(ImmutableArray<string> files, ModuleGraph graph)
    {
        var direct = new SortedSet<string>(StringComparer.Ordinal);
        var reasons = new SortedDictionary<string, SortedSet<string>>(StringComparer.Ordinal);
        var unresolved = new SortedSet<string>(StringComparer.Ordinal);

        foreach (var file in files)
        {
            var text = StripComments(File.ReadAllText(file));

            foreach (Match match in ImportRegex().Matches(text))
            {
                Add(match.Groups["ns"].Value, file, "import");
            }

            foreach (Match match in WinrtIncludeRegex().Matches(text))
            {
                Add(match.Groups["ns"].Value, file, "include");
            }

            var textWithoutNamespaceDeclarations = NamespaceDeclarationRegex().Replace(text, " ");
            foreach (Match match in QualifiedWinrtRegex().Matches(textWithoutNamespaceDeclarations))
            {
                var path = match.Groups["path"].Value.Replace("::", ".", StringComparison.Ordinal);
                AddLongestNamespacePrefix(path, file, "qualified winrt name");
            }
        }

        return new SourceScanResult(
            direct.ToImmutableSortedSet(StringComparer.Ordinal),
            reasons.ToImmutableSortedDictionary(pair => pair.Key, pair => pair.Value.ToImmutableSortedSet(StringComparer.Ordinal), StringComparer.Ordinal),
            unresolved.ToImmutableSortedSet(StringComparer.Ordinal),
            files);

        void Add(string ns, string file, string reason)
        {
            if (ns is "winrt_base" or "winrt_numerics")
            {
                return;
            }

            if (!graph.Modules.ContainsKey(ns))
            {
                return;
            }

            direct.Add(ns);
            if (!reasons.TryGetValue(ns, out var set))
            {
                set = new SortedSet<string>(StringComparer.Ordinal);
                reasons[ns] = set;
            }

            set.Add($"{reason}: {Path.GetRelativePath(Environment.CurrentDirectory, file)}");
        }

        void AddLongestNamespacePrefix(string dottedPath, string file, string reason)
        {
            var current = dottedPath;
            while (current.Contains('.', StringComparison.Ordinal))
            {
                if (graph.Modules.ContainsKey(current))
                {
                    Add(current, file, reason);
                    return;
                }

                current = current[..current.LastIndexOf('.')];
            }
        }
    }

    private static string StripComments(string text)
    {
        text = BlockCommentRegex().Replace(text, " ");
        text = LineCommentRegex().Replace(text, " ");
        return text;
    }

    [GeneratedRegex(@"(?m)^\s*import\s+winrt\.(?<ns>[A-Za-z0-9_.]+)\s*;")]
    private static partial Regex ImportRegex();

    [GeneratedRegex(@"#include\s*[<""]winrt/(?<ns>[A-Za-z0-9_.]+)\.h[>""]")]
    private static partial Regex WinrtIncludeRegex();

    [GeneratedRegex(@"\bwinrt::(?<path>(?:[A-Z][A-Za-z0-9_]*::)+[A-Z][A-Za-z0-9_]*)")]
    private static partial Regex QualifiedWinrtRegex();

    [GeneratedRegex(@"(?m)^\s*(?:namespace\s+[A-Za-z_][A-Za-z0-9_]*\s*=\s*winrt::[A-Za-z0-9_:]+\s*;|using\s+namespace\s+winrt::[A-Za-z0-9_:]+\s*;|namespace\s+winrt::[A-Za-z0-9_:]+\s*(?:\{|;))")]
    private static partial Regex NamespaceDeclarationRegex();

    [GeneratedRegex(@"/\*.*?\*/", RegexOptions.Singleline)]
    private static partial Regex BlockCommentRegex();

    [GeneratedRegex(@"//.*?$", RegexOptions.Multiline)]
    private static partial Regex LineCommentRegex();
}

internal static class FilterCalculator
{
    public static ImmutableSortedSet<string> CalculateExcludes(ImmutableSortedSet<string> include, ImmutableSortedSet<string> allNamespaces)
    {
        var generatedByInclude = Apply(include, ImmutableSortedSet<string>.Empty, allNamespaces);
        return generatedByInclude.Except(include)
            .Where(ns => ns is not "winrt_base" and not "winrt_numerics")
            .ToImmutableSortedSet(StringComparer.Ordinal);
    }

    public static FilterValidation Validate(ImmutableSortedSet<string> include, ImmutableSortedSet<string> exclude, ImmutableSortedSet<string> allNamespaces)
    {
        var actual = Apply(include, exclude, allNamespaces)
            .Where(ns => ns is not "winrt_base" and not "winrt_numerics")
            .ToImmutableSortedSet(StringComparer.Ordinal);
        var missing = include.Except(actual).ToImmutableSortedSet(StringComparer.Ordinal);
        var extra = actual.Except(include).ToImmutableSortedSet(StringComparer.Ordinal);
        return new FilterValidation(missing.Count == 0 && extra.Count == 0, actual, missing, extra);
    }

    private static ImmutableSortedSet<string> Apply(ImmutableSortedSet<string> include, ImmutableSortedSet<string> exclude, ImmutableSortedSet<string> allNamespaces)
    {
        return allNamespaces
            .Where(ns => include.Any(prefix => MatchesIncludePrefix(ns, prefix)))
            .Where(ns => !exclude.Contains(ns))
            .ToImmutableSortedSet(StringComparer.Ordinal);
    }

    private static bool MatchesIncludePrefix(string ns, string prefix) =>
        ns.Equals(prefix, StringComparison.Ordinal) || ns.StartsWith(prefix + ".", StringComparison.Ordinal);
}

internal static class FilterVerifier
{
    public static async Task<FilterValidation> VerifyAsync(
        string cppwinrt,
        ResponseFileSet rspFiles,
        ImmutableSortedSet<string> desired,
        ImmutableSortedSet<string> exclude)
    {
        var tempRoot = Path.Combine(Path.GetTempPath(), "cppwinrt-module-filter-verify-" + Guid.NewGuid().ToString("N"));
        var graphs = new List<ProjectionGraph>();
        try
        {
            Directory.CreateDirectory(tempRoot);
            foreach (var rspFile in rspFiles.Files)
            {
                var projectionTemp = Path.Combine(tempRoot, Path.GetFileNameWithoutExtension(rspFile.Path));
                var generatedDir = Path.Combine(projectionTemp, "Generated Files");
                Directory.CreateDirectory(generatedDir);

                var rewritten = ResponseRewriter.RewriteWithFilters(rspFile.Path, generatedDir, desired, exclude);
                var rewrittenRsp = Path.Combine(projectionTemp, Path.GetFileName(rspFile.Path));
                await File.WriteAllTextAsync(rewrittenRsp, rewritten, new UTF8Encoding(encoderShouldEmitUTF8Identifier: false));
                await RunCppWinRTAsync(cppwinrt, rewrittenRsp);

                graphs.Add(ModuleGraph.Parse(Path.Combine(generatedDir, "winrt"), rspFile.Kind));
            }
        }
        finally
        {
            DeleteDirectoryQuietly(tempRoot);
        }

        var actual = ModuleGraph.Merge(graphs).Namespaces
            .Where(ns => ns is not "winrt_base" and not "winrt_numerics")
            .ToImmutableSortedSet(StringComparer.Ordinal);
        var missing = desired.Except(actual).ToImmutableSortedSet(StringComparer.Ordinal);
        var extra = actual.Except(desired).ToImmutableSortedSet(StringComparer.Ordinal);
        return new FilterValidation(missing.Count == 0 && extra.Count == 0, actual, missing, extra);
    }

    private static async Task RunCppWinRTAsync(string cppwinrt, string rspPath)
    {
        var startInfo = new ProcessStartInfo
        {
            FileName = cppwinrt,
            UseShellExecute = false,
            RedirectStandardError = true,
            RedirectStandardOutput = true
        };
        startInfo.ArgumentList.Add("@" + rspPath);

        using var process = Process.Start(startInfo) ?? throw new InvalidOperationException("Failed to start cppwinrt.exe.");
        var stdout = await process.StandardOutput.ReadToEndAsync();
        var stderr = await process.StandardError.ReadToEndAsync();
        await process.WaitForExitAsync();

        if (process.ExitCode != 0)
        {
            throw new InvalidOperationException($"cppwinrt.exe failed for {rspPath}.{Environment.NewLine}{stdout}{stderr}");
        }
    }

    private static void DeleteDirectoryQuietly(string path)
    {
        try
        {
            if (Directory.Exists(path))
            {
                Directory.Delete(path, recursive: true);
            }
        }
        catch
        {
            // Temporary verification artifacts are best-effort cleanup only.
        }
    }
}

internal sealed record FilterValidation(
    bool IsExact,
    ImmutableSortedSet<string> Actual,
    ImmutableSortedSet<string> Missing,
    ImmutableSortedSet<string> Extra);

internal sealed record AnalysisReport(
    string Project,
    string Configuration,
    string Platform,
    string RootNamespace,
    int TotalGeneratedModules,
    int DirectModuleCount,
    int DesiredModuleCount,
    ModuleGroups Include,
    ModuleGroups Exclude,
    ImmutableSortedSet<string> DirectModules,
    ImmutableSortedDictionary<string, ImmutableSortedSet<string>> Reasons,
    ImmutableSortedSet<string> UnresolvedShortNames,
    ImmutableArray<string> ResponseFiles,
    bool ValidationExact,
    ImmutableSortedSet<string> ValidationMissing,
    ImmutableSortedSet<string> ValidationExtra,
    ImmutableArray<string> Warnings)
{
    public static AnalysisReport Create(
        ProjectInfo project,
        ResponseFileSet responseFiles,
        ModuleGraph graph,
        SourceScanResult scan,
        ImmutableSortedSet<string> include,
        ImmutableSortedSet<string> exclude,
        FilterValidation validation)
    {
        var warnings = ImmutableArray.CreateBuilder<string>();
        if (scan.UnresolvedShortNames.Count > 0)
        {
            warnings.Add($"{scan.UnresolvedShortNames.Count} short winrt:: names could not be resolved from generated headers.");
        }

        if (!validation.IsExact)
        {
            warnings.Add("Filter validation was not exact. Inspect validationMissing and validationExtra in the JSON report.");
        }

        return new AnalysisReport(
            project.ProjectPath,
            project.Configuration,
            project.Platform,
            project.RootNamespace,
            graph.Modules.Count,
            scan.DirectModules.Count,
            include.Count,
            ModuleGroups.From(include, graph.ProjectComponentNamespaces(project), project.ProjectRootPrefix),
            ModuleGroups.From(exclude, graph.ProjectComponentNamespaces(project), project.ProjectRootPrefix),
            scan.DirectModules,
            scan.Reasons,
            scan.UnresolvedShortNames,
            responseFiles.Files.Select(f => f.Path).ToImmutableArray(),
            validation.IsExact,
            validation.Missing,
            validation.Extra,
            warnings.ToImmutable());
    }
}

internal sealed record ModuleGroups(
    ImmutableArray<string> ProjectComponentModules,
    ImmutableArray<string> ThirdPartyModules,
    ImmutableArray<string> WindowsSdkModules)
{
    public static ModuleGroups From(
        IEnumerable<string> modules,
        ImmutableSortedSet<string> projectComponentModules,
        string projectRootPrefix)
    {
        var project = ImmutableArray.CreateBuilder<string>();
        var thirdParty = ImmutableArray.CreateBuilder<string>();
        var windows = ImmutableArray.CreateBuilder<string>();

        foreach (var module in modules.OrderBy(m => m, StringComparer.Ordinal))
        {
            if (projectComponentModules.Contains(module) ||
                module.StartsWith(projectRootPrefix + ".", StringComparison.Ordinal) ||
                module == projectRootPrefix)
            {
                project.Add(module);
            }
            else if (module.StartsWith("Windows.", StringComparison.Ordinal))
            {
                windows.Add(module);
            }
            else
            {
                thirdParty.Add(module);
            }
        }

        return new ModuleGroups(project.ToImmutable(), thirdParty.ToImmutable(), windows.ToImmutable());
    }
}

internal static class XmlSnippetFormatter
{
    public static string Format(AnalysisReport report)
    {
        var builder = new StringBuilder();
        builder.AppendLine("Suggested CppWinRT module filters");
        builder.AppendLine($"Generated modules discovered: {report.TotalGeneratedModules}");
        builder.AppendLine($"Direct modules discovered: {report.DirectModuleCount}");
        builder.AppendLine($"Desired modules: {report.DesiredModuleCount}");
        builder.AppendLine($"Validation exact: {report.ValidationExact}");
        builder.AppendLine();
        builder.AppendLine("<PropertyGroup Label=\"CppWinRTModules\">");
        AppendProperty(builder, "CppWinRTModuleInclude", "Islands modules", report.Include.ProjectComponentModules, useAppend: false);
        AppendProperty(builder, "CppWinRTModuleInclude", "Microsoft modules", report.Include.ThirdPartyModules, useAppend: true);
        AppendProperty(builder, "CppWinRTModuleInclude", "Windows SDK modules", report.Include.WindowsSdkModules, useAppend: true);
        AppendModuleGroupProperties(builder, "CppWinRTModuleExclude", report.Exclude);
        builder.AppendLine("</PropertyGroup>");
        return builder.ToString();
    }

    private static void AppendModuleGroupProperties(StringBuilder builder, string property, ModuleGroups groups)
    {
        var hasValue = false;
        hasValue |= AppendProperty(builder, property, "Islands prefix overmatches", groups.ProjectComponentModules, useAppend: hasValue);
        hasValue |= AppendProperty(builder, property, "Microsoft prefix overmatches", groups.ThirdPartyModules, useAppend: hasValue);
        AppendProperty(builder, property, "Windows SDK prefix overmatches", groups.WindowsSdkModules, useAppend: hasValue);
    }

    private static bool AppendProperty(StringBuilder builder, string property, string label, ImmutableArray<string> values, bool useAppend)
    {
        if (values.Length == 0)
        {
            return false;
        }

        builder.AppendLine($"  <!-- {label} -->");
        var value = string.Join(';', values);
        if (useAppend)
        {
            value = $"$({property});" + value;
        }
        builder.AppendLine($"  <{property}>{System.Security.SecurityElement.Escape(value)}</{property}>");
        return true;
    }
}
