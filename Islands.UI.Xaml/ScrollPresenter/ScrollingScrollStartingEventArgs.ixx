module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "ScrollingScrollStartingEventArgs.g.h"

export module ixx.ScrollingScrollStartingEventArgs;

import inc.common;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



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


namespace winrt::Islands::UI::Xaml::Controls::implementation { using ScrollingScrollStartingEventArgs = ::ScrollingScrollStartingEventArgs; }
}
