// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <cstdarg>

import std;
import inc.common;
import inc.win32;
import ixx.Utils;

using LPTSTR = wchar_t*;

winrt::hstring StringUtil::FormatString(std::wstring_view formatString, ...)
{
    std::va_list pArgs;
    va_start(pArgs, formatString);

    void* formattedString = nullptr;

    // Format the string
    formatMessage(
        formatMessageAllocateBuffer |
        formatMessageFromString,
        formatString.data(),
        0,
        0,
        (LPTSTR)&formattedString,
        0,
        &pArgs);

    va_end(pArgs);

    winrt::hstring result((LPTSTR)formattedString);
    localFree(formattedString);

    return result;
}

std::wstring StringUtil::Utf8ToUtf16(const std::string_view& utf8Str)
{
    std::wstring converted;
    if (utf8Str.size() > 0)
    {
        const int length = multiByteToWideChar(cpUtf8, 0, utf8Str.data(), (int)utf8Str.size(), nullptr, 0);
        if (length > 0)
        {
            converted.resize(length);
            if (multiByteToWideChar(cpUtf8, 0, utf8Str.data(), (int)utf8Str.size(), converted.data(), (int)converted.size()) == 0)
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
        const int length = wideCharToMultiByte(cpUtf8, 0, utf16Str.data(), (int)utf16Str.size(), nullptr, 0, nullptr, nullptr);
        if (length > 0)
        {
            converted.resize(length);
            if (wideCharToMultiByte(cpUtf8, 0, utf16Str.data(), (int)utf16Str.size(), converted.data(), (int)converted.size(), nullptr, nullptr) == 0)
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

winrt::VisualStateGroup VisualStateUtil::GetVisualStateGroup(const winrt::FrameworkElement& control, const std::wstring_view& groupName)
{
    winrt::VisualStateGroup group{};
    auto visualStateGroups = winrt::VisualStateManager::GetVisualStateGroups(control);
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

bool VisualStateUtil::VisualStateGroupExists(const winrt::FrameworkElement& control, const std::wstring_view& groupName)
{
    return static_cast<bool>(GetVisualStateGroup(control, groupName));
}

void VisualStateUtil::GoToStateIfGroupExists(const winrt::Control& control, const std::wstring_view& groupName, const std::wstring_view& stateName, bool useTransitions)
{
    auto visualStateGroup = GetVisualStateGroup(control, groupName);
    if (visualStateGroup)
    {
        winrt::VisualStateManager::GoToState(control, stateName, useTransitions);
    }
}
