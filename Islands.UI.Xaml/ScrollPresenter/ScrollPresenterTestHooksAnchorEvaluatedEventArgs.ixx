module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "Primitives.ScrollPresenterTestHooksAnchorEvaluatedEventArgs.g.h"

export module ixx.ScrollPresenterTestHooksAnchorEvaluatedEventArgs;

import inc.common;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollPresenterTestHooksAnchorEvaluatedEventArgs :
    public winrt::Islands::UI::Xaml::Controls::Primitives::implementation::ScrollPresenterTestHooksAnchorEvaluatedEventArgsT<ScrollPresenterTestHooksAnchorEvaluatedEventArgs>
{
public:
    ScrollPresenterTestHooksAnchorEvaluatedEventArgs(const winrt::Windows::UI::Xaml::UIElement& anchorElement, double viewportAnchorPointHorizontalOffset, double viewportAanchorPointVerticalOffset);

    // IScrollPresenterTestHooksAnchorEvaluatedEventArgs overrides
    winrt::Windows::UI::Xaml::UIElement AnchorElement();
    double ViewportAnchorPointHorizontalOffset();
    double ViewportAnchorPointVerticalOffset();

private:
    winrt::weak_ref<winrt::Windows::UI::Xaml::UIElement> m_anchorElement;
    double m_viewportAnchorPointHorizontalOffset{ 0.0 };
    double m_viewportAnchorPointVerticalOffset{ 0.0 };
};


namespace winrt::Islands::UI::Xaml::Controls::Primitives::implementation { using ScrollPresenterTestHooksAnchorEvaluatedEventArgs = ::ScrollPresenterTestHooksAnchorEvaluatedEventArgs; }
}
