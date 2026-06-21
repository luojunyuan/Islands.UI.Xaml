#include "pch.h"
#include "TitleBarTemplateSettings.h"
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
