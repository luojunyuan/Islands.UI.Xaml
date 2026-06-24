// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <SDKDDKVer.h>

#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#undef GetCurrentTime

#include <unknwn.h>
#include <inspectable.h>
#include <restrictederrorinfo.h>
#include <hstring.h>
#include <windows.ui.xaml.hosting.referencetracker.h>

#include "inc/CppWinRTIncludes.h"
#include "inc/BuildMacros.h"

#ifndef MUX_ASSERT
#define MUX_ASSERT(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_NOASSUME
#define MUX_ASSERT_NOASSUME(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_MSG
#define MUX_ASSERT_MSG(condition, message) assert((condition) && (message))
#endif

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
