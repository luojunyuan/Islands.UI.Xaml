module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "Primitives.ScrollControllerAddScrollVelocityRequestedEventArgs.g.h"

export module ixx.ScrollControllerAddScrollVelocityRequestedEventArgs;

import inc.common;
import std;
#include "../Telemetry/ScrollTraceMacros.h"

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollControllerAddScrollVelocityRequestedEventArgs :
    public winrt::Islands::UI::Xaml::Controls::Primitives::implementation::ScrollControllerAddScrollVelocityRequestedEventArgsT<ScrollControllerAddScrollVelocityRequestedEventArgs>
{
public:
    ~ScrollControllerAddScrollVelocityRequestedEventArgs()
    {
        SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
    }

    ScrollControllerAddScrollVelocityRequestedEventArgs(
        float offsetVelocity,
        winrt::IReference<float> inertiaDecayRate);

    float OffsetVelocity() const;
    winrt::IReference<float> InertiaDecayRate() const;
    int32_t CorrelationId() const;
    void CorrelationId(int32_t correlationId);

private:
    float m_offsetVelocity{ 0.0f };
    winrt::IReference<float> m_inertiaDecayRate{};
    int32_t m_correlationId{ -1 };
};


namespace winrt::Islands::UI::Xaml::Controls::Primitives::implementation { using ScrollControllerAddScrollVelocityRequestedEventArgs = ::ScrollControllerAddScrollVelocityRequestedEventArgs; }
}
