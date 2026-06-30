# IUXControlsTestApp

Minimal CoreIsland-based host for exercising `Islands.UI.Xaml.Controls` from C#.

This is intentionally not a direct copy of WinUI's `MUXControlsTestApp`:

- it uses WinUI 2 through the `Microsoft.UI.Xaml` NuGet package;
- it uses `CoreIsland` instead of WinUI 3 / Windows App SDK;
- it references the local `Islands.UI.Xaml.Controls` native output through
  `Islands.UI.Xaml.Controls.Projection`;
- it starts with a focused TitleBar page and is meant to grow with TestHooks,
  ScrollPresenter, and ScrollView.

Build:

```powershell
& "C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe" Tests\IUXControlsTestApp\IUXControlsTestApp.csproj /p:Configuration=Debug /p:Platform=x64 /m:1 /v:minimal /nr:false
```

The project is included in the main `.slnx` with explicit platform mappings for
`x64`, `x86`, and `ARM64`.
