// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "CppBaseIncludes.h"

import CppWinRTModules;
#include "common.h"
#include "DoubleUtil.h"
#include "FloatUtil.h"
#include "RegUtil.h"
#include "SharedHelpers.h"

bool SharedHelpers::s_isOnXboxInitialized{ false };
bool SharedHelpers::s_isOnXbox{ false };
bool SharedHelpers::s_isMouseModeEnabledInitialized{ false };
bool SharedHelpers::s_isMouseModeEnabled{ false };

const double DoubleUtil::NaN = std::numeric_limits<double>::quiet_NaN();
const float FloatUtil::NaN = std::numeric_limits<float>::quiet_NaN();

bool SharedHelpers::IsAnimationsEnabled()
{
    return winrt::UISettings().AnimationsEnabled();
}

bool SharedHelpers::DoRectsIntersect(const winrt::Rect& rect1, const winrt::Rect& rect2)
{
    return !(rect1.Width <= 0 || rect1.Height <= 0 || rect2.Width <= 0 || rect2.Height <= 0) &&
        rect2.X <= rect1.X + rect1.Width &&
        rect2.X + rect2.Width >= rect1.X &&
        rect2.Y <= rect1.Y + rect1.Height &&
        rect2.Y + rect2.Height >= rect1.Y;
}

bool SharedHelpers::IsAncestor(
    const winrt::DependencyObject& child,
    const winrt::DependencyObject& parent,
    bool checkVisibility)
{
    if (!child || !parent || child == parent)
    {
        return false;
    }

    auto isCollapsed = [](const winrt::DependencyObject& object)
    {
        if (const auto element = object.try_as<winrt::IUIElement>())
        {
            return element.Visibility() == winrt::Visibility::Collapsed;
        }

        return false;
    };

    if (checkVisibility && (isCollapsed(parent) || isCollapsed(child)))
    {
        return false;
    }

    winrt::DependencyObject current = winrt::VisualTreeHelper::GetParent(child);
    while (current)
    {
        if (checkVisibility && isCollapsed(current))
        {
            return false;
        }

        if (current == parent)
        {
            return true;
        }

        current = winrt::VisualTreeHelper::GetParent(current);
    }

    return false;
}

bool RegUtil::UseDynamicScrollbars() noexcept
{
    constexpr LPCWSTR subKey = L"Control Panel\\Accessibility";
    constexpr LPCWSTR value = L"DynamicScrollbars";
    DWORD keyValue = 0;
    DWORD keySize = sizeof(DWORD);

    if (SUCCEEDED(HRESULT_FROM_WIN32(::RegGetValueW(HKEY_CURRENT_USER, subKey, value, RRF_RT_REG_DWORD, nullptr, &keyValue, &keySize))))
    {
        return keyValue != 0;
    }

    return true;
}
