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
#include "ScrollingZoomAnimationStartingEventArgs.h"

ScrollingZoomAnimationStartingEventArgs::ScrollingZoomAnimationStartingEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

ScrollingZoomAnimationStartingEventArgs::~ScrollingZoomAnimationStartingEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

winrt::Windows::Foundation::Numerics::float2 ScrollingZoomAnimationStartingEventArgs::CenterPoint()
{
    return m_centerPoint;
}

float ScrollingZoomAnimationStartingEventArgs::StartZoomFactor()
{
    return m_startZoomFactor;
}

float ScrollingZoomAnimationStartingEventArgs::EndZoomFactor()
{
    return m_endZoomFactor;
}

winrt::Windows::UI::Composition::CompositionAnimation ScrollingZoomAnimationStartingEventArgs::Animation()
{
    return m_animation;
}

void ScrollingZoomAnimationStartingEventArgs::Animation(winrt::Windows::UI::Composition::CompositionAnimation const& value)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR, METH_NAME, this, value);
    if (!value)
    {
        throw winrt::hresult_invalid_argument(L"Animation cannot be set to null.");
    }
    m_animation = value;
}

int32_t ScrollingZoomAnimationStartingEventArgs::CorrelationId()
{
    return m_zoomFactorChangeCorrelationId;
}

void ScrollingZoomAnimationStartingEventArgs::SetZoomFactorChangeCorrelationId(int32_t zoomFactorChangeCorrelationId)
{
    m_zoomFactorChangeCorrelationId = zoomFactorChangeCorrelationId;
}

winrt::Windows::UI::Composition::CompositionAnimation ScrollingZoomAnimationStartingEventArgs::GetAnimation() const
{
    return m_animation;
}

void ScrollingZoomAnimationStartingEventArgs::SetAnimation(const winrt::Windows::UI::Composition::CompositionAnimation& animation)
{
    m_animation = animation;
}

void ScrollingZoomAnimationStartingEventArgs::SetCenterPoint(const winrt::Windows::Foundation::Numerics::float2& centerPoint)
{
    m_centerPoint = centerPoint;
}

void ScrollingZoomAnimationStartingEventArgs::SetStartZoomFactor(const float& startZoomFactor)
{
    m_startZoomFactor = startZoomFactor;
}

void ScrollingZoomAnimationStartingEventArgs::SetEndZoomFactor(const float& endZoomFactor)
{
    m_endZoomFactor = endZoomFactor;
}
