// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "CppBaseIncludes.h"

import CppWinRTModules;
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
