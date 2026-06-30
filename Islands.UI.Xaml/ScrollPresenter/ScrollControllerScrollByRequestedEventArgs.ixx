module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "Primitives.ScrollControllerScrollByRequestedEventArgs.g.h"

export module ixx.ScrollControllerScrollByRequestedEventArgs;

import inc.common;
import std;
#include "../Telemetry/ScrollTraceMacros.h"

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollControllerScrollByRequestedEventArgs :
    public winrt::Islands::UI::Xaml::Controls::Primitives::implementation::ScrollControllerScrollByRequestedEventArgsT<ScrollControllerScrollByRequestedEventArgs>
{
public:
    ~ScrollControllerScrollByRequestedEventArgs()
    {
        SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
    }

    ScrollControllerScrollByRequestedEventArgs(
        double offsetDelta,
        winrt::ScrollingScrollOptions const & options);

    double OffsetDelta() const;
    winrt::ScrollingScrollOptions Options() const;
    int32_t CorrelationId() const;
    void CorrelationId(int32_t correlationId);

private:
    double m_offsetDelta{ 0.0 };
    winrt::ScrollingScrollOptions m_options{ nullptr };
    int32_t m_correlationId{ -1 };
};


namespace winrt::Islands::UI::Xaml::Controls::Primitives::implementation { using ScrollControllerScrollByRequestedEventArgs = ::ScrollControllerScrollByRequestedEventArgs; }
}
