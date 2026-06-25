// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "CppBaseIncludes.h"

import CppWinRTModules;
#include "ScrollPresenterTrace.h"
#include "ScrollingZoomStartingEventArgs.h"

ScrollingZoomStartingEventArgs::ScrollingZoomStartingEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

ScrollingZoomStartingEventArgs::~ScrollingZoomStartingEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

int32_t ScrollingZoomStartingEventArgs::CorrelationId() const
{
    return m_correlationId;
}

void ScrollingZoomStartingEventArgs::SetCorrelationId(int32_t correlationId)
{
    m_correlationId = correlationId;
}

double ScrollingZoomStartingEventArgs::HorizontalOffset() const
{
    return m_horizontalOffset;
}

void ScrollingZoomStartingEventArgs::SetHorizontalOffset(double horizontalOffset)
{
    m_horizontalOffset = horizontalOffset;
}

double ScrollingZoomStartingEventArgs::VerticalOffset() const
{
    return m_verticalOffset;
}

void ScrollingZoomStartingEventArgs::SetVerticalOffset(double verticalOffset)
{
    m_verticalOffset = verticalOffset;
}

float ScrollingZoomStartingEventArgs::ZoomFactor() const
{
    return m_zoomFactor;
}

void ScrollingZoomStartingEventArgs::SetZoomFactor(float zoomFactor)
{
    m_zoomFactor = zoomFactor;
}
