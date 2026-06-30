// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

module;

module inc.common;

import std;
import winrt_base;
import winrt.Windows.Foundation;
import winrt.Windows.UI.Xaml.Controls;

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
