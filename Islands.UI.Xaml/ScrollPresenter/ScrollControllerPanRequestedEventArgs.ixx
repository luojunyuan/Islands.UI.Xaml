module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "Primitives.ScrollControllerPanRequestedEventArgs.g.h"

export module ixx.ScrollControllerPanRequestedEventArgs;

import inc.common;
import std;
#include "../Telemetry/ScrollTraceMacros.h"

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollControllerPanRequestedEventArgs :
    public winrt::Islands::UI::Xaml::Controls::Primitives::implementation::ScrollControllerPanRequestedEventArgsT<ScrollControllerPanRequestedEventArgs>
{
public:
    ~ScrollControllerPanRequestedEventArgs()
    {
        SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
    }

    ScrollControllerPanRequestedEventArgs(
        const winrt::PointerPoint& pointerPoint);

    winrt::PointerPoint PointerPoint() const;
    bool Handled() const;
    void Handled(bool handled); 

private:
    winrt::PointerPoint m_pointerPoint{ nullptr };
    bool m_handled{ false };
};


namespace winrt::Islands::UI::Xaml::Controls::Primitives::implementation { using ScrollControllerPanRequestedEventArgs = ::ScrollControllerPanRequestedEventArgs; }
}
