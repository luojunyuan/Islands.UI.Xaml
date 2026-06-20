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
#include "TypeLogging.ixx"
#include "ScrollPresenterTrace.ixx"
#include "ScrollControllerPanRequestedEventArgs.ixx"

#include "ScrollControllerPanRequestedEventArgs.properties.cpp"

ScrollControllerPanRequestedEventArgs::ScrollControllerPanRequestedEventArgs(
    const winrt::PointerPoint& pointerPoint)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR, METH_NAME, this, TypeLogging::PointerPointToString(pointerPoint).c_str());

    m_pointerPoint = pointerPoint;
}

winrt::PointerPoint ScrollControllerPanRequestedEventArgs::PointerPoint() const
{
    return m_pointerPoint;
}

bool ScrollControllerPanRequestedEventArgs::Handled() const
{
    return m_handled;
}

void ScrollControllerPanRequestedEventArgs::Handled(bool handled)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_INT, METH_NAME, this, handled);
    m_handled = handled;
}
