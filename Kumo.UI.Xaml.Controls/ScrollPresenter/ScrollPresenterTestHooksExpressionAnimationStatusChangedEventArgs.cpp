// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#define KUMO_USE_IMPORT_STD 1
#define KUMO_DEFER_PREAMBLE_USINGS 1
#include "KumoPreamble.ixx"
import std;
import winrt_base;
import winrt;
#include "KumoPostImports.ixx"
#include "common.ixx"
#include "ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs.ixx"

ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs::ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs(
    bool isExpressionAnimationStarted, wstring_view const& propertyName)
{
    m_isExpressionAnimationStarted = isExpressionAnimationStarted;
    m_propertyName = propertyName.data();
}

#pragma region IScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs

bool ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs::IsExpressionAnimationStarted()
{
    return m_isExpressionAnimationStarted;
}

winrt::hstring ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs::PropertyName()
{
    return m_propertyName;
}

#pragma endregion
