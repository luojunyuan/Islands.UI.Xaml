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
#include "ScrollingZoomCompletedEventArgs.h"

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
