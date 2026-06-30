import ixx.ScrollPresenterTestHooksAnchorEvaluatedEventArgs;

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

import winrt_base;
import winrt.Islands.UI.Xaml.Controls.Primitives;
import winrt.Windows.UI.Xaml;

#ifdef WINRT_IMPORT_MODULE
#undef WINRT_IMPORT_MODULE
#endif

ScrollPresenterTestHooksAnchorEvaluatedEventArgs::ScrollPresenterTestHooksAnchorEvaluatedEventArgs(
    const winrt::Windows::UI::Xaml::UIElement& anchorElement,
    double viewportAnchorPointHorizontalOffset,
    double viewportAnchorPointVerticalOffset)
{
    if (anchorElement)
    {
        m_anchorElement = winrt::make_weak(anchorElement);
    }
    m_viewportAnchorPointHorizontalOffset = viewportAnchorPointHorizontalOffset;
    m_viewportAnchorPointVerticalOffset = viewportAnchorPointVerticalOffset;
}

#pragma region IScrollPresenterTestHooksAnchorEvaluatedEventArgs

winrt::Windows::UI::Xaml::UIElement ScrollPresenterTestHooksAnchorEvaluatedEventArgs::AnchorElement()
{
    return m_anchorElement.get();
}

double ScrollPresenterTestHooksAnchorEvaluatedEventArgs::ViewportAnchorPointHorizontalOffset()
{
    return m_viewportAnchorPointHorizontalOffset;
}

double ScrollPresenterTestHooksAnchorEvaluatedEventArgs::ViewportAnchorPointVerticalOffset()
{
    return m_viewportAnchorPointVerticalOffset;
}

#pragma endregion
