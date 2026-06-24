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

#include "ScrollViewBringIntoViewOperation.h"
#include "ScrollViewTrace.h"

ScrollViewBringIntoViewOperation::ScrollViewBringIntoViewOperation(winrt::UIElement const& targetElement, bool cancelBringIntoView)
{
    SCROLLVIEW_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR, METH_NAME, this, targetElement);

    m_targetElement = winrt::make_weak(targetElement);
    m_cancelBringIntoView = cancelBringIntoView;
}

ScrollViewBringIntoViewOperation::~ScrollViewBringIntoViewOperation()
{
    SCROLLVIEW_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR_INT, METH_NAME, this, m_targetElement.get(), m_ticksCount);
}

bool ScrollViewBringIntoViewOperation::HasMaxTicksCount() const
{
    MUX_ASSERT(m_ticksCount <= s_maxTicksCount);

    return m_ticksCount == s_maxTicksCount;
}

winrt::UIElement ScrollViewBringIntoViewOperation::TargetElement() const
{
    return m_targetElement.get();
}

int8_t ScrollViewBringIntoViewOperation::TicksCount() const
{
    return m_ticksCount;
}

int8_t ScrollViewBringIntoViewOperation::TickOperation()
{
    SCROLLVIEW_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR_INT, METH_NAME, this, m_targetElement.get(), m_ticksCount);

    MUX_ASSERT(m_ticksCount < s_maxTicksCount);

    return ++m_ticksCount;
}
