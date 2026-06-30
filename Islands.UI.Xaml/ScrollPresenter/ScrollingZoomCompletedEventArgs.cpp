// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

import inc.common;
import ixx.ScrollPresenterTrace;
import ixx.ScrollingZoomCompletedEventArgs;
import std;
#include "../Telemetry/ScrollTraceMacros.h"

ScrollingZoomCompletedEventArgs::ScrollingZoomCompletedEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

ScrollingZoomCompletedEventArgs::~ScrollingZoomCompletedEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

int32_t ScrollingZoomCompletedEventArgs::CorrelationId()
{
    return m_zoomFactorChangeCorrelationId;
}

ScrollPresenterViewChangeResult ScrollingZoomCompletedEventArgs::Result()
{
    return m_result;
}

void ScrollingZoomCompletedEventArgs::ZoomFactorChangeCorrelationId(int32_t zoomFactorChangeCorrelationId)
{
    m_zoomFactorChangeCorrelationId = zoomFactorChangeCorrelationId;
}

void ScrollingZoomCompletedEventArgs::Result(ScrollPresenterViewChangeResult result)
{
    m_result = result;
}
