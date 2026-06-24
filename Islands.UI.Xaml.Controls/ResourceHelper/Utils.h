// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace StringUtil
{
    /// <summary>
    /// Formats a given string with the desired parameter list.
    /// </summary>
    /// <param name="formatString">The format string.</param>
    /// <param name="...">The parameter list of format args.</param>
    /// <returns>The formatted string.</returns>
    winrt::hstring FormatString(std::wstring_view formatString, ...);

    std::wstring Utf8ToUtf16(const std::string_view& utf8Str);
    std::string Utf16ToUtf8(const std::wstring_view& utf16Str);
}

class VisualStateUtil
{
public:
    static winrt::Windows::UI::Xaml::VisualStateGroup GetVisualStateGroup(const winrt::Windows::UI::Xaml::FrameworkElement& control, const std::wstring_view& groupName);
    static bool VisualStateGroupExists(const winrt::Windows::UI::Xaml::FrameworkElement& control, const std::wstring_view& groupName);
    static void GoToStateIfGroupExists(const winrt::Windows::UI::Xaml::Controls::Control& control, const std::wstring_view& groupName, const std::wstring_view& stateName, bool useTransitions);
};

namespace LayoutUtils
{
    inline constexpr winrt::Windows::Foundation::Size c_infSize{ std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() };

    template<class UIElementType>
    inline float MeasureAndGetDesiredWidthFor(UIElementType element, winrt::Windows::Foundation::Size const& availableSize)
    {
        float desiredWidth = 0;
        if (element)
        {
            element.Measure(availableSize);
            desiredWidth = element.DesiredSize().Width;
        }
        return desiredWidth;
    }

    template<class UIElementType>
    inline float MeasureAndGetDesiredHeightFor(UIElementType element, winrt::Windows::Foundation::Size const& availableSize)
    {
        float desiredHeight = 0;
        if (element)
        {
            element.Measure(availableSize);
            desiredHeight = element.DesiredSize().Height;
        }
        return desiredHeight;
    }

    template<class UIElementType>
    inline double GetActualWidthFor(UIElementType element)
    {
        return (element ? element.ActualWidth() : 0);
    }
}

namespace Util
{
    inline winrt::Windows::UI::Xaml::Visibility constexpr VisibilityFromBool(bool visible)
    { 
        return visible ? winrt::Windows::UI::Xaml::Visibility::Visible : winrt::Windows::UI::Xaml::Visibility::Collapsed;
    }
}
