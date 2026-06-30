// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

import inc.common;
import ixx.ScrollPresenterTrace;
import ixx.ScrollingScrollCompletedEventArgs;
import std;
#include "../Telemetry/ScrollTraceMacros.h"

ScrollingScrollCompletedEventArgs::ScrollingScrollCompletedEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

ScrollingScrollCompletedEventArgs::~ScrollingScrollCompletedEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

int32_t ScrollingScrollCompletedEventArgs::CorrelationId()
{
    return m_offsetsChangeCorrelationId;
}

ScrollPresenterViewChangeResult ScrollingScrollCompletedEventArgs::Result()
{
    return m_result;
}

void ScrollingScrollCompletedEventArgs::OffsetsChangeCorrelationId(int32_t offsetsChangeCorrelationId)
{
    m_offsetsChangeCorrelationId = offsetsChangeCorrelationId;
}

void ScrollingScrollCompletedEventArgs::Result(ScrollPresenterViewChangeResult result)
{
    m_result = result;
}
