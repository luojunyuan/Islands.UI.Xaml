# TitleBar C# interaction tests

The copied TitleBar C# test files are upstream shared-project fragments, not a
standalone test project in this repository.

Evidence checked:

- `Islands.UI.Xaml/TitleBar/InteractionTests/TitleBar_InteractionTests.shproj`
  fails with MSB3871 because shared projects cannot build by themselves.
- `TitleBarTests.cs` imports WEX/TAEF and Microsoft.Windows.Apps.Test
  automation packages from the upstream WinUI test infrastructure.
- `TitleBarTests.cs` initializes `TestApplicationInfo.MUXExperimentalTestApp`.
- `TitleBar/TestUI` is also a shared-project fragment for the upstream
  `MUXControlsTestApp` host and depends on types such as `TestPage`,
  `TopLevelTestPage`, and `MUXControlsTestHooks`.
- The only test method in the copied file is currently commented out.

Current decision: keep these files as upstream reference material, but do not
wire them into the local build until the WinUI test host/testhook shared
projects are intentionally brought over. The active local gate is
`Tests/SmokeTests`, which verifies the library outputs and activation factories.

`Tests/IUXControlsTestApp` is the local lightweight replacement host: it uses
CoreIsland and WinUI 2 NuGet packages rather than the upstream WinUI 3 /
Windows App SDK test app.
