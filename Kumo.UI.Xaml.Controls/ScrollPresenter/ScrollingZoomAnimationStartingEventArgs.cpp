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
#include "ResourceAccessor.ixx"
#include "ScrollPresenterTrace.ixx"
#include "ScrollingZoomAnimationStartingEventArgs.ixx"

winrt::float2 ScrollingZoomAnimationStartingEventArgs::CenterPoint()
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

winrt::CompositionAnimation ScrollingZoomAnimationStartingEventArgs::Animation()
{
    return m_animation;
}

void ScrollingZoomAnimationStartingEventArgs::Animation(winrt::CompositionAnimation const& value)
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

winrt::CompositionAnimation ScrollingZoomAnimationStartingEventArgs::GetAnimation() const
{
    return m_animation;
}

void ScrollingZoomAnimationStartingEventArgs::SetAnimation(const winrt::CompositionAnimation& animation)
{
    m_animation = animation;
}

void ScrollingZoomAnimationStartingEventArgs::SetCenterPoint(const winrt::float2& centerPoint)
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
