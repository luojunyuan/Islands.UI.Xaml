#include <windows.h>

import std;
import winrt_base;
import winrt.Windows.Foundation;
import winrt.Windows.UI.Xaml.Controls;

#include "RuntimeProfiler.h"

void SetDefaultStyleKeyWorker(
    winrt::Windows::UI::Xaml::Controls::IControlProtected const& controlProtected,
    std::wstring_view const& className)
{
    controlProtected.DefaultStyleKey(winrt::box_value(className));

    if (auto control = controlProtected.try_as<winrt::Windows::UI::Xaml::Controls::IControl5>())
    {
        control.DefaultStyleResourceUri(winrt::Windows::Foundation::Uri{ L"ms-appx:///Islands.UI.Xaml.Controls/Themes/generic.xaml" });
    }
}

namespace RuntimeProfiler
{
    void FireEvent(bool) noexcept {}
    void RegisterMethod(ProfileGroup, UINT16, UINT16, volatile LONG*) noexcept {}
    void UninitializeRuntimeProfiler() {}
}
