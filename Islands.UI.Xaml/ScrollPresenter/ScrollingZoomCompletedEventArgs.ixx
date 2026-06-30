module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "ScrollingZoomCompletedEventArgs.g.h"

export module ixx.ScrollingZoomCompletedEventArgs;

import inc.common;
import ixx.ViewChangeBase;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollingZoomCompletedEventArgs :
    public winrt::Islands::UI::Xaml::Controls::implementation::ScrollingZoomCompletedEventArgsT<ScrollingZoomCompletedEventArgs>
{
public:
    ScrollingZoomCompletedEventArgs();

    ~ScrollingZoomCompletedEventArgs();

    // IScrollingZoomCompletedEventArgs overrides
    int32_t CorrelationId();
    ScrollPresenterViewChangeResult Result();

    void ZoomFactorChangeCorrelationId(int32_t zoomFactorChangeCorrelationId);
    void Result(ScrollPresenterViewChangeResult result);

private:
    int32_t m_zoomFactorChangeCorrelationId{ -1 };
    ScrollPresenterViewChangeResult m_result{ ScrollPresenterViewChangeResult::Completed };
};


namespace winrt::Islands::UI::Xaml::Controls::implementation { using ScrollingZoomCompletedEventArgs = ::ScrollingZoomCompletedEventArgs; }
}
