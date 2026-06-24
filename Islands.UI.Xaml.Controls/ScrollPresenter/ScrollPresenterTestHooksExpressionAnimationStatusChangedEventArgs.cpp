// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

import std;
import winrt_base;
import winrt.Islands.UI.Xaml.Controls.Primitives;

#define WINRT_IMPORT_MODULE
#include "ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs.h"
#undef WINRT_IMPORT_MODULE

ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs::ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs(
    bool isExpressionAnimationStarted, std::wstring_view const& propertyName)
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
