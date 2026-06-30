module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "Primitives.ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs.g.h"

export module ixx.ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs;

import inc.common;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs :
    public winrt::Islands::UI::Xaml::Controls::Primitives::implementation::ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgsT<ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs>
{
public:
    ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs(bool isExpressionAnimationStarted, std::wstring_view const& propertyName);

    // IScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs overrides
    bool IsExpressionAnimationStarted();
    winrt::hstring PropertyName();

private:
    bool m_isExpressionAnimationStarted{ false };
    winrt::hstring m_propertyName{};
};


namespace winrt::Islands::UI::Xaml::Controls::Primitives::implementation { using ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs = ::ScrollPresenterTestHooksExpressionAnimationStatusChangedEventArgs; }
}
