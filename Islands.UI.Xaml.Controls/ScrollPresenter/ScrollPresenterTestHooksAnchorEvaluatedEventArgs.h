// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Primitives.ScrollPresenterTestHooksAnchorEvaluatedEventArgs.g.h"

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
