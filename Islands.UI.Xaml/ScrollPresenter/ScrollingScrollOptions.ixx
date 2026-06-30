module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "ScrollingScrollOptions.g.h"

export module ixx.ScrollingScrollOptions;

import inc.common;
import std;
#include "../Telemetry/ScrollTraceMacros.h"

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollingScrollOptions :
    public winrt::Islands::UI::Xaml::Controls::implementation::ScrollingScrollOptionsT<ScrollingScrollOptions>
{
public:
    ScrollingScrollOptions(winrt::ScrollingAnimationMode const& animationMode);
    ScrollingScrollOptions(winrt::ScrollingAnimationMode const& animationMode, winrt::ScrollingSnapPointsMode const& snapPointsMode);

    ~ScrollingScrollOptions()
    {
        SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
    }

    static constexpr winrt::ScrollingAnimationMode s_defaultAnimationMode{ winrt::ScrollingAnimationMode::Auto };
    static constexpr winrt::ScrollingSnapPointsMode s_defaultSnapPointsMode{ winrt::ScrollingSnapPointsMode::Default };

    winrt::ScrollingAnimationMode AnimationMode() const;
    void AnimationMode(winrt::ScrollingAnimationMode const& animationMode);

    winrt::ScrollingSnapPointsMode SnapPointsMode() const;
    void SnapPointsMode(winrt::ScrollingSnapPointsMode const& snapPointsMode);

private:
    winrt::ScrollingAnimationMode m_animationMode{ s_defaultAnimationMode };
    winrt::ScrollingSnapPointsMode m_snapPointsMode{ s_defaultSnapPointsMode };
};


namespace winrt::Islands::UI::Xaml::Controls::implementation { using ScrollingScrollOptions = ::ScrollingScrollOptions; }
}
