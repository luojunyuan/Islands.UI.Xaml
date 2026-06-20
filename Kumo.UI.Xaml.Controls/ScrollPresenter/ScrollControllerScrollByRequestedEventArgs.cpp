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
#include "TypeLogging.ixx"
#include "ScrollPresenterTypeLogging.ixx"
#include "ScrollControllerScrollByRequestedEventArgs.ixx"

#include "ScrollControllerScrollByRequestedEventArgs.properties.cpp"

ScrollControllerScrollByRequestedEventArgs::ScrollControllerScrollByRequestedEventArgs(
    double offsetDelta,
    winrt::ScrollingScrollOptions const& options)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR_DBL, METH_NAME, this,
        TypeLogging::ScrollOptionsToString(options).c_str(), offsetDelta);

    m_offsetDelta = offsetDelta;
    m_options = options;
}

double ScrollControllerScrollByRequestedEventArgs::OffsetDelta() const
{
    return m_offsetDelta;
}

winrt::ScrollingScrollOptions ScrollControllerScrollByRequestedEventArgs::Options() const
{
    return m_options;
}

int32_t ScrollControllerScrollByRequestedEventArgs::CorrelationId() const
{
    return m_correlationId;
}

void ScrollControllerScrollByRequestedEventArgs::CorrelationId(int32_t correlationId)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_INT, METH_NAME, this, correlationId);

    m_correlationId = correlationId;
}
