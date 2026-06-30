import winrt_smoke;

#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace
{
    struct hstring_handle
    {
        HSTRING value{};

        explicit hstring_handle(std::wstring_view text)
        {
            const auto hr = WindowsCreateString(text.data(), static_cast<UINT32>(text.size()), &value);
            if (failed(hr))
            {
                throw std::runtime_error("WindowsCreateString failed");
            }
        }

        ~hstring_handle()
        {
            WindowsDeleteString(value);
        }

        hstring_handle(hstring_handle const&) = delete;
        hstring_handle& operator=(hstring_handle const&) = delete;
    };

    bool file_exists(std::filesystem::path const& path)
    {
        std::error_code error;
        return std::filesystem::is_regular_file(path, error);
    }

    void require_file(std::filesystem::path const& path)
    {
        if (!file_exists(path))
        {
            std::wcerr << L"Missing expected output: " << path << L"\n";
            std::exit(1);
        }
    }

    void require_factory(DllGetActivationFactoryFn getFactory, std::wstring_view className)
    {
        hstring_handle name{ className };
        IActivationFactory* factory{};
        const auto hr = getFactory(name.value, &factory);
        if (failed(hr) || factory == nullptr)
        {
            std::wcerr << L"Activation factory not found: " << className << L" hr=0x"
                       << std::hex << static_cast<unsigned int>(hr) << L"\n";
            std::exit(1);
        }

        factory->Release();
    }
}

int wmain(int argc, wchar_t** argv)
{
    if (argc != 2)
    {
        std::wcerr << L"Usage: Islands.UI.Xaml.Controls.SmokeTests.exe <library-output-dir>\n";
        return 1;
    }

    const std::filesystem::path outputDir = argv[1];
    const auto dllPath = outputDir / L"Islands.UI.Xaml.Controls.dll";
    require_file(dllPath);
    require_file(outputDir / L"Islands.UI.Xaml.Controls.winmd");
    require_file(outputDir / L"Islands.UI.Xaml.Controls.pri");

    const auto initHr = RoInitialize(roInitSingleThreaded);
    if (failed(initHr) && initHr != rpcChangedMode)
    {
        std::wcerr << L"RoInitialize failed hr=0x" << std::hex << static_cast<unsigned int>(initHr) << L"\n";
        return 1;
    }

    std::wcout << L"Loading " << dllPath << L"\n" << std::flush;
    const auto module = LoadLibraryW(dllPath.c_str());
    if (!module)
    {
        std::wcerr << L"LoadLibrary failed for " << dllPath << L" error=" << GetLastError() << L"\n";
        return 1;
    }

    const auto getFactory = reinterpret_cast<DllGetActivationFactoryFn>(GetProcAddress(module, "DllGetActivationFactory"));
    if (!getFactory)
    {
        std::wcerr << L"DllGetActivationFactory export was not found\n";
        FreeLibrary(module);
        return 1;
    }

    const std::vector<std::wstring_view> classNames{
        L"Islands.UI.Xaml.Controls.AppWindowTitleBar",
        L"Islands.UI.Xaml.Controls.InputNonClientPointerSource",
        L"Islands.UI.Xaml.Controls.MUXControlsTestHooks",
        L"Islands.UI.Xaml.Controls.TitleBar",
        L"Islands.UI.Xaml.Controls.TitleBarAutomationPeer",
        L"Islands.UI.Xaml.Controls.TitleBarTemplateSettings",
        L"Islands.UI.Xaml.Controls.TitleBarWindowAdapter",
        L"Islands.UI.Xaml.Automation.Peers.ScrollPresenterAutomationPeer",
        L"Islands.UI.Xaml.Controls.ScrollView",
        L"Islands.UI.Xaml.Controls.ScrollingScrollOptions",
        L"Islands.UI.Xaml.Controls.ScrollingZoomOptions",
        L"Islands.UI.Xaml.Controls.Primitives.RepeatedScrollSnapPoint",
        L"Islands.UI.Xaml.Controls.Primitives.RepeatedZoomSnapPoint",
        L"Islands.UI.Xaml.Controls.Primitives.ScrollControllerAddScrollVelocityRequestedEventArgs",
        L"Islands.UI.Xaml.Controls.Primitives.ScrollControllerPanRequestedEventArgs",
        L"Islands.UI.Xaml.Controls.Primitives.ScrollControllerScrollByRequestedEventArgs",
        L"Islands.UI.Xaml.Controls.Primitives.ScrollControllerScrollToRequestedEventArgs",
        L"Islands.UI.Xaml.Controls.Primitives.ScrollPresenter",
        L"Islands.UI.Xaml.Controls.Primitives.ScrollSnapPoint",
        L"Islands.UI.Xaml.Controls.Primitives.ZoomSnapPoint",
#ifdef _DEBUG
        L"Islands.UI.Xaml.Controls.Primitives.ScrollPresenterTestHooks",
        L"Islands.UI.Xaml.Controls.Primitives.ScrollViewTestHooks",
#endif
        L"Islands.UI.Xaml.Controls.XamlMetaDataProvider",
    };

    for (const auto className : classNames)
    {
        std::wcout << L"Checking " << className << L"\n" << std::flush;
        require_factory(getFactory, className);
    }

    FreeLibrary(module);
    if (succeeded(initHr))
    {
        RoUninitialize();
    }
    std::wcout << L"Smoke tests passed for " << dllPath << L"\n";
    return 0;
}
