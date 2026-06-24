// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <stdarg.h>
#include <windows.h>

import std;
import winrt_base;
import winrt.Windows.Foundation;
import winrt.Windows.UI.Xaml;
import winrt.Windows.UI.Xaml.Controls;

#include "Utils.h"

winrt::hstring StringUtil::FormatString(std::wstring_view formatString, ...)
{
    va_list pArgs;
    va_start(pArgs, formatString);
    
    LPVOID formattedString = nullptr;

    // Format the string
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_STRING,
        formatString.data(),
        0,
        0,
        (LPTSTR)&formattedString,
        0,
        &pArgs);

    va_end(pArgs);

    winrt::hstring result((LPTSTR)formattedString);
    LocalFree(formattedString);

    return result;
}

std::wstring StringUtil::Utf8ToUtf16(const std::string_view& utf8Str)
{
    std::wstring converted;
    if (utf8Str.size() > 0)
    {
        const int length = MultiByteToWideChar(CP_UTF8, 0, utf8Str.data(), (int)utf8Str.size(), nullptr, 0);
        if (length > 0)
        {
            converted.resize(length);
            if (MultiByteToWideChar(CP_UTF8, 0, utf8Str.data(), (int)utf8Str.size(), converted.data(), (int)converted.size()) == 0)
            {
                winrt::throw_last_error();
            }
        }
        else
        {
            winrt::throw_last_error();
        }
    }

    return converted;
}

std::string StringUtil::Utf16ToUtf8(const std::wstring_view& utf16Str)
{
    std::string converted;
    if (utf16Str.size() > 0)
    {
        const int length = WideCharToMultiByte(CP_UTF8, 0, utf16Str.data(), (int)utf16Str.size(), nullptr, 0, nullptr, nullptr);
        if (length > 0)
        {
            converted.resize(length);
            if (WideCharToMultiByte(CP_UTF8, 0, utf16Str.data(), (int)utf16Str.size(), converted.data(), (int)converted.size(), nullptr, nullptr) == 0)
            {
                winrt::throw_last_error();
            }
        }
        else
        {
            winrt::throw_last_error();
        }
    }

    return converted;
}

winrt::Windows::UI::Xaml::VisualStateGroup VisualStateUtil::GetVisualStateGroup(
    const winrt::Windows::UI::Xaml::FrameworkElement& control,
    const std::wstring_view& groupName)
{
    winrt::Windows::UI::Xaml::VisualStateGroup group{};
    auto visualStateGroups = winrt::Windows::UI::Xaml::VisualStateManager::GetVisualStateGroups(control);
    for (auto const& visualStateGroup : visualStateGroups)
    {
        if (visualStateGroup.Name() == groupName)
        {
            group = visualStateGroup;
            return group;
        }
    }
    return group;
}

bool VisualStateUtil::VisualStateGroupExists(const winrt::Windows::UI::Xaml::FrameworkElement& control, const std::wstring_view& groupName)
{
    return static_cast<bool>(GetVisualStateGroup(control, groupName));
}

void VisualStateUtil::GoToStateIfGroupExists(
    const winrt::Windows::UI::Xaml::Controls::Control& control,
    const std::wstring_view& groupName,
    const std::wstring_view& stateName,
    bool useTransitions)
{
    auto visualStateGroup = GetVisualStateGroup(control, groupName);
    if (visualStateGroup)
    {
        winrt::Windows::UI::Xaml::VisualStateManager::GoToState(control, stateName, useTransitions);
    }
}
