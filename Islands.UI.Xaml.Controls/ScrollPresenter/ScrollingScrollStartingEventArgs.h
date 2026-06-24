// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "ScrollingScrollStartingEventArgs.g.h"

class ScrollingScrollStartingEventArgs :
    public winrt::Islands::UI::Xaml::Controls::implementation::ScrollingScrollStartingEventArgsT<ScrollingScrollStartingEventArgs>
{
public:
    ScrollingScrollStartingEventArgs();

    ~ScrollingScrollStartingEventArgs();

    // IScrollingScrollStartingEventArgs overrides
    int32_t CorrelationId() const;
    double HorizontalOffset() const;
    double VerticalOffset() const;
    float ZoomFactor() const;

    void SetCorrelationId(int32_t correlationId);
    void SetHorizontalOffset(double horizontalOffset);
    void SetVerticalOffset(double verticalOffset);
    void SetZoomFactor(float zoomFactor);

private:
    int32_t m_correlationId{ -1 };
    double m_horizontalOffset{};
    double m_verticalOffset{};
    float m_zoomFactor{};
};
