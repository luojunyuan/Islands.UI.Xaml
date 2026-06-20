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
#include "ScrollPresenterTestHooksAnchorEvaluatedEventArgs.ixx"

ScrollPresenterTestHooksAnchorEvaluatedEventArgs::ScrollPresenterTestHooksAnchorEvaluatedEventArgs(
    const winrt::UIElement& anchorElement,
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

winrt::UIElement ScrollPresenterTestHooksAnchorEvaluatedEventArgs::AnchorElement()
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
