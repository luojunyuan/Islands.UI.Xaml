// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "ScrollingZoomAnimationStartingEventArgs.g.h"

class ScrollingZoomAnimationStartingEventArgs :
    public winrt::Islands::UI::Xaml::Controls::implementation::ScrollingZoomAnimationStartingEventArgsT<ScrollingZoomAnimationStartingEventArgs>
{
public:
    ScrollingZoomAnimationStartingEventArgs();

    ~ScrollingZoomAnimationStartingEventArgs();

    // IScrollingZoomAnimationStartingEventArgs overrides
    winrt::Windows::Foundation::Numerics::float2 CenterPoint();
    float StartZoomFactor();
    float EndZoomFactor();
    winrt::Windows::UI::Composition::CompositionAnimation Animation();
    void Animation(winrt::Windows::UI::Composition::CompositionAnimation const& value);
    int32_t CorrelationId();

    void SetZoomFactorChangeCorrelationId(int32_t zoomFactorChangeCorrelationId);
    winrt::Windows::UI::Composition::CompositionAnimation GetAnimation() const;
    void SetAnimation(const winrt::Windows::UI::Composition::CompositionAnimation& animation);
    void SetCenterPoint(const winrt::Windows::Foundation::Numerics::float2& centerPoint);
    void SetStartZoomFactor(const float& startZoomFactor);
    void SetEndZoomFactor(const float& endZoomFactor);

private:
    winrt::Windows::UI::Composition::CompositionAnimation m_animation{ nullptr };
    winrt::Windows::Foundation::Numerics::float2 m_centerPoint{ };
    float m_startZoomFactor{ 1.0f };
    float m_endZoomFactor{ 1.0f };
    int32_t m_zoomFactorChangeCorrelationId{ -1 };
};
