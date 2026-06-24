#include "pch.h"
#include "common.h"
#include "RuntimeProfiler.h"

void SetDefaultStyleKeyWorker(winrt::IControlProtected const& controlProtected, std::wstring_view const& className)
{
    controlProtected.DefaultStyleKey(winrt::box_value(className));

    if (auto control = controlProtected.try_as<winrt::IControl5>())
    {
        control.DefaultStyleResourceUri(winrt::Uri{ L"ms-appx:///Islands.UI.Xaml.Controls/Themes/generic.xaml" });
    }
}

namespace RuntimeProfiler
{
    void FireEvent(bool) noexcept {}
    void RegisterMethod(ProfileGroup, UINT16, UINT16, volatile LONG*) noexcept {}
    void UninitializeRuntimeProfiler() {}
}
