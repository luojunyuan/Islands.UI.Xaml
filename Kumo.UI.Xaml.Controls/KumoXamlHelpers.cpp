#define KUMO_USE_IMPORT_STD 1
#define KUMO_DEFER_PREAMBLE_USINGS 1
#include "KumoPreamble.ixx"
import std;
import winrt_base;
import winrt;
#include "KumoPostImports.ixx"
#include "common.ixx"
#include "RuntimeProfiler.ixx"

void SetDefaultStyleKeyWorker(winrt::IControlProtected const& controlProtected, std::wstring_view const& className)
{
    controlProtected.DefaultStyleKey(winrt::box_value(className));

    if (auto control = controlProtected.try_as<winrt::IControl5>())
    {
        control.DefaultStyleResourceUri(winrt::Uri{ L"ms-appx:///Kumo.UI.Xaml.Controls/ScrollView/ScrollView.xaml" });
    }
}

namespace RuntimeProfiler
{
    void FireEvent(bool) noexcept {}
    void RegisterMethod(ProfileGroup, UINT16, UINT16, volatile LONG*) noexcept {}
    void UninitializeRuntimeProfiler() {}
}
