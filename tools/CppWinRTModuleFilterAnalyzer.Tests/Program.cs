using System.Collections.Immutable;

var tests = new (string Name, Action Body)[]
{
    ("third-party modules are grouped separately", ThirdPartyModulesAreGroupedSeparately),
    ("project component modules are included and grouped", ProjectComponentModulesAreIncludedAndGrouped),
    ("prefix overmatches become excludes", PrefixOvermatchesBecomeExcludes),
    ("dependency closure includes transitive imports", DependencyClosureIncludesTransitiveImports),
    ("user short names do not create unresolved warnings", UserShortNamesDoNotCreateUnresolvedWarnings)
};

foreach (var (name, body) in tests)
{
    try
    {
        body();
        Console.WriteLine($"PASS {name}");
    }
    catch (Exception ex)
    {
        Console.Error.WriteLine($"FAIL {name}: {ex.Message}");
        return 1;
    }
}

return 0;

static void ThirdPartyModulesAreGroupedSeparately()
{
    var projectComponents = Sorted("Islands.UI.Xaml.Controls");
    var groups = ModuleGroups.From(
        new[] { "Microsoft.UI.Xaml.Controls", "Microsoft.Web.WebView2.Core", "Windows.Foundation" },
        projectComponents,
        "Islands.UI");

    AssertSequence(groups.ThirdPartyModules, "Microsoft.UI.Xaml.Controls", "Microsoft.Web.WebView2.Core");
    AssertSequence(groups.WindowsSdkModules, "Windows.Foundation");
    AssertSequence(groups.ProjectComponentModules);
}

static void ProjectComponentModulesAreIncludedAndGrouped()
{
    var graph = Graph(
        Module("Islands.UI.Xaml.Controls", "component", "Windows.Foundation"),
        Module("Islands.UI.Xaml.Controls.Primitives", "component"),
        Module("Windows.Foundation", "platform"));
    var project = Project();

    var desired = graph.DependencyClosure(graph.ProjectComponentNamespaces(project));
    var groups = ModuleGroups.From(desired, graph.ProjectComponentNamespaces(project), project.ProjectRootPrefix);

    AssertSequence(desired, "Islands.UI.Xaml.Controls", "Islands.UI.Xaml.Controls.Primitives", "Windows.Foundation");
    AssertSequence(groups.ProjectComponentModules, "Islands.UI.Xaml.Controls", "Islands.UI.Xaml.Controls.Primitives");
}

static void PrefixOvermatchesBecomeExcludes()
{
    var include = Sorted("Microsoft.UI.Xaml.Controls");
    var all = Sorted("Microsoft.UI.Xaml.Controls", "Microsoft.UI.Xaml.Controls.Primitives", "Microsoft.UI.Xaml.XamlTypeInfo");

    var exclude = FilterCalculator.CalculateExcludes(include, all);

    AssertSequence(exclude, "Microsoft.UI.Xaml.Controls.Primitives");
}

static void DependencyClosureIncludesTransitiveImports()
{
    var graph = Graph(
        Module("Windows.UI.Xaml.Controls", "platform", "Windows.UI.Xaml", "Windows.Foundation"),
        Module("Windows.UI.Xaml", "platform", "Windows.Foundation.Collections"),
        Module("Windows.Foundation", "platform"),
        Module("Windows.Foundation.Collections", "platform", "Windows.Foundation"));

    var closure = graph.DependencyClosure(new[] { "Windows.UI.Xaml.Controls" });

    AssertSequence(
        closure,
        "Windows.Foundation",
        "Windows.Foundation.Collections",
        "Windows.UI.Xaml",
        "Windows.UI.Xaml.Controls");
}

static void UserShortNamesDoNotCreateUnresolvedWarnings()
{
    var temp = Path.Combine(Path.GetTempPath(), "cppwinrt-filter-analyzer-test-" + Guid.NewGuid().ToString("N"));
    Directory.CreateDirectory(temp);

    try
    {
        var source = Path.Combine(temp, "Source.cpp");
        File.WriteAllText(source, """
            namespace muxc = winrt::Microsoft::UI::Xaml::Controls;
            auto control = winrt::Button{ nullptr };
            auto aliasControl = muxc::Button{ nullptr };
            """);

        var graph = Graph(Module("Microsoft.UI.Xaml.Controls", "reference"));
        var scan = SourceScanner.Scan(ImmutableArray.Create(source), graph);

        AssertSequence(scan.DirectModules);
        AssertSequence(scan.UnresolvedShortNames);
    }
    finally
    {
        Directory.Delete(temp, recursive: true);
    }
}

static ProjectInfo Project() =>
    new(
        @"C:\repo\Islands.UI.Xaml.Controls\Islands.UI.Xaml.vcxproj",
        @"C:\repo\Islands.UI.Xaml.Controls",
        @"C:\repo",
        "Islands.UI.Xaml",
        "Islands.UI.Xaml.Controls",
        "Islands.UI",
        "Debug",
        "ARM64",
        "3.0.260520.1");

static ModuleGraph Graph(params ModuleInfo[] modules) =>
    new(modules.ToImmutableSortedDictionary(module => module.Namespace, module => module, StringComparer.Ordinal));

static ModuleInfo Module(string ns, string kind, params string[] imports) =>
    new(
        ns,
        "winrt." + ns,
        Path.Combine(Path.GetTempPath(), "winrt", "winrt." + ns + ".ixx"),
        kind,
        imports.ToImmutableSortedSet(StringComparer.Ordinal));

static ImmutableSortedSet<string> Sorted(params string[] values) =>
    values.ToImmutableSortedSet(StringComparer.Ordinal);

static void AssertSequence(IEnumerable<string> actual, params string[] expected)
{
    var actualArray = actual.ToArray();
    if (!actualArray.SequenceEqual(expected, StringComparer.Ordinal))
    {
        throw new InvalidOperationException(
            $"expected [{string.Join(", ", expected)}], got [{string.Join(", ", actualArray)}]");
    }
}
