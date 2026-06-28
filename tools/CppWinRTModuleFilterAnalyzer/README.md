# CppWinRTModuleFilterAnalyzer

Analyzes an existing C++/WinRT project and prints suggested
`CppWinRTModuleInclude` / `CppWinRTModuleExclude` values.

The v1 analyzer intentionally uses existing C++/WinRT response files from a
prior build. Build the target project once before running it.

```powershell
dotnet run --project tools/CppWinRTModuleFilterAnalyzer -- `
  --project Islands.UI.Xaml.Controls/Islands.UI.Xaml.vcxproj `
  --configuration Debug `
  --platform ARM64 `
  --output-json obj/cppwinrt-module-filter-report.json
```

The tool does not edit project files. It generates unfiltered C++/WinRT module
interfaces in a temporary directory, builds a module dependency graph from the
generated `.ixx` files, scans project sources for WinRT namespace usage, then
prints grouped XML snippets.

Source scanning intentionally uses only stable WinRT namespace signals:

- `import winrt.Namespace;`
- `#include <winrt/Namespace.h>`
- fully-qualified `winrt::Namespace::Type` references

It does not try to resolve user namespace aliases, `using namespace`, or short
type names such as `winrt::Button`. Those are C++ name lookup concerns rather
than C++/WinRT projection filter inputs.

The analyzer treats `CppWinRTModuleInclude` as prefix matching and emits
`CppWinRTModuleExclude` entries only for concrete namespaces that were pulled in
by those prefixes but are not needed by the computed closure.

MSVC `/scanDependencies` output can also describe compiled module dependencies,
but v1 reads the generated `.ixx` imports directly. That keeps the analyzer tied
to `cppwinrt.exe` response files and avoids requiring a configured compiler
scan invocation.
