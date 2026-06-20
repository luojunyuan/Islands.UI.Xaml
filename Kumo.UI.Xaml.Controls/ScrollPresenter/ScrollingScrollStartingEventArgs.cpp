// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#define KUMO_USE_IMPORT_STD 1
#define KUMO_DEFER_PREAMBLE_USINGS 1
#include "KumoPreamble.ixx"
import std;
import winrt_base;
import winrt;
#include "KumoPostImports.ixx"
#include "ScrollingScrollStartingEventArgs.ixx"

int32_t ScrollingScrollStartingEventArgs::CorrelationId() const
{
    return m_correlationId;
}

void ScrollingScrollStartingEventArgs::SetCorrelationId(int32_t correlationId)
{
    m_correlationId = correlationId;
}

double ScrollingScrollStartingEventArgs::HorizontalOffset() const
{
    return m_horizontalOffset;
}

void ScrollingScrollStartingEventArgs::SetHorizontalOffset(double horizontalOffset)
{
    m_horizontalOffset = horizontalOffset;
}

double ScrollingScrollStartingEventArgs::VerticalOffset() const
{
    return m_verticalOffset;
}

void ScrollingScrollStartingEventArgs::SetVerticalOffset(double verticalOffset)
{
    m_verticalOffset = verticalOffset;
}

float ScrollingScrollStartingEventArgs::ZoomFactor() const
{
    return m_zoomFactor;
}

void ScrollingScrollStartingEventArgs::SetZoomFactor(float zoomFactor)
{
    m_zoomFactor = zoomFactor;
}
