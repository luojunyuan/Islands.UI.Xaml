#pragma once

#include "TitleBarTemplateSettings.g.h"

namespace winrt::Islands::UI::Xaml::Controls::implementation
{

struct TitleBarTemplateSettings : TitleBarTemplateSettingsT<TitleBarTemplateSettings>
{
    TitleBarTemplateSettings();

    winrt::xaml_controls::IconElement IconElement();
    void IconElement(winrt::xaml_controls::IconElement const& value);

    static winrt::xaml::DependencyProperty IconElementProperty();

private:
    static void EnsureProperties();

    static winrt::xaml::DependencyProperty s_iconElementProperty;
};

}

namespace winrt::Islands::UI::Xaml::Controls::factory_implementation
{

struct TitleBarTemplateSettings : TitleBarTemplateSettingsT<TitleBarTemplateSettings, implementation::TitleBarTemplateSettings>
{
};

}
