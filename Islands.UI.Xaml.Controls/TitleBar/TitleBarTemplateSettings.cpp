import winrt_base;
import winrt.Windows.UI.Xaml;
import winrt.Windows.UI.Xaml.Controls;
import winrt.Windows.UI.Xaml.Interop;
import winrt.Islands.UI.Xaml.Controls;

namespace winrt
{
namespace xaml = Windows::UI::Xaml;
namespace xaml_controls = Windows::UI::Xaml::Controls;
namespace xaml_interop = Windows::UI::Xaml::Interop;
}

#define WINRT_IMPORT_MODULE
#include "TitleBarTemplateSettings.h"
#undef WINRT_IMPORT_MODULE

#if __has_include("TitleBarTemplateSettings.g.cpp")
#include "TitleBarTemplateSettings.g.cpp"
#endif

namespace winrt::Islands::UI::Xaml::Controls::implementation
{

winrt::xaml::DependencyProperty TitleBarTemplateSettings::s_iconElementProperty{ nullptr };

TitleBarTemplateSettings::TitleBarTemplateSettings()
{
    EnsureProperties();
}

void TitleBarTemplateSettings::EnsureProperties()
{
    if (!s_iconElementProperty)
    {
        s_iconElementProperty = winrt::xaml::DependencyProperty::Register(
            L"IconElement",
            winrt::xaml_typename<winrt::xaml_controls::IconElement>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBarTemplateSettings>(),
            winrt::xaml::PropertyMetadata{ nullptr });
    }
}

winrt::xaml::DependencyProperty TitleBarTemplateSettings::IconElementProperty()
{
    EnsureProperties();
    return s_iconElementProperty;
}

winrt::xaml_controls::IconElement TitleBarTemplateSettings::IconElement()
{
    return GetValue(IconElementProperty()).try_as<winrt::xaml_controls::IconElement>();
}

void TitleBarTemplateSettings::IconElement(winrt::xaml_controls::IconElement const& value)
{
    SetValue(IconElementProperty(), value);
}

}
