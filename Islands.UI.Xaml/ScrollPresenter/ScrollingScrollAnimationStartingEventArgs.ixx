module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "ScrollingScrollAnimationStartingEventArgs.g.h"

export module ixx.ScrollingScrollAnimationStartingEventArgs;

import inc.common;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollingScrollAnimationStartingEventArgs :
    public winrt::Islands::UI::Xaml::Controls::implementation::ScrollingScrollAnimationStartingEventArgsT<ScrollingScrollAnimationStartingEventArgs>
{
public:
    ScrollingScrollAnimationStartingEventArgs();

    ~ScrollingScrollAnimationStartingEventArgs();

    // IScrollingScrollAnimationStartingEventArgs overrides
    winrt::Windows::UI::Composition::CompositionAnimation Animation();
    void Animation(winrt::Windows::UI::Composition::CompositionAnimation const& value);
    int32_t CorrelationId();
    winrt::Windows::Foundation::Numerics::float2 StartPosition();
    winrt::Windows::Foundation::Numerics::float2 EndPosition();

    void SetOffsetsChangeCorrelationId(int32_t offsetsChangeCorrelationId);
    winrt::Windows::UI::Composition::CompositionAnimation GetAnimation() const;
    void SetAnimation(const winrt::Windows::UI::Composition::CompositionAnimation& animation);
    void SetStartPosition(const winrt::Windows::Foundation::Numerics::float2& startPosition);
    void SetEndPosition(const winrt::Windows::Foundation::Numerics::float2& endPosition);

private:
    winrt::Windows::UI::Composition::CompositionAnimation m_animation{ nullptr };
    int32_t m_offsetsChangeCorrelationId{ -1 };
    winrt::Windows::Foundation::Numerics::float2 m_startPosition{ 0.0f, 0.0f };
    winrt::Windows::Foundation::Numerics::float2 m_endPosition{ 0.0f, 0.0f };
};


namespace winrt::Islands::UI::Xaml::Controls::implementation { using ScrollingScrollAnimationStartingEventArgs = ::ScrollingScrollAnimationStartingEventArgs; }
}
