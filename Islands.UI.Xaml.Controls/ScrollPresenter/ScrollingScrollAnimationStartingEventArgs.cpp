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
#include "ScrollingScrollAnimationStartingEventArgs.h"

ScrollingScrollAnimationStartingEventArgs::ScrollingScrollAnimationStartingEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

ScrollingScrollAnimationStartingEventArgs::~ScrollingScrollAnimationStartingEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

winrt::Windows::UI::Composition::CompositionAnimation ScrollingScrollAnimationStartingEventArgs::Animation()
{
    return m_animation;
}

void ScrollingScrollAnimationStartingEventArgs::Animation(winrt::Windows::UI::Composition::CompositionAnimation const& value)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR, METH_NAME, this, value);
    if (!value)
    {
        throw winrt::hresult_invalid_argument(L"Animation cannot be set to null.");
    }
    m_animation = value;
}

int32_t ScrollingScrollAnimationStartingEventArgs::CorrelationId()
{
    return m_offsetsChangeCorrelationId;
}

winrt::Windows::Foundation::Numerics::float2 ScrollingScrollAnimationStartingEventArgs::StartPosition()
{
    return m_startPosition;
}

winrt::Windows::Foundation::Numerics::float2 ScrollingScrollAnimationStartingEventArgs::EndPosition()
{
    return m_endPosition;
}

void ScrollingScrollAnimationStartingEventArgs::SetOffsetsChangeCorrelationId(int32_t offsetsChangeCorrelationId)
{
    m_offsetsChangeCorrelationId = offsetsChangeCorrelationId;
}

winrt::Windows::UI::Composition::CompositionAnimation ScrollingScrollAnimationStartingEventArgs::GetAnimation() const
{
    return m_animation;
}

void ScrollingScrollAnimationStartingEventArgs::SetAnimation(const winrt::Windows::UI::Composition::CompositionAnimation& animation)
{
    m_animation = animation;
}


void ScrollingScrollAnimationStartingEventArgs::SetStartPosition(const winrt::Windows::Foundation::Numerics::float2& startPosition)
{
    m_startPosition = startPosition;
}


void ScrollingScrollAnimationStartingEventArgs::SetEndPosition(const winrt::Windows::Foundation::Numerics::float2& endPosition)
{
    m_endPosition = endPosition;
}
