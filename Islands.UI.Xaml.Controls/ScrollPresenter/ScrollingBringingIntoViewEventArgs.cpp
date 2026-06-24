// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ScrollPresenterTrace.h"
#include "ScrollingBringingIntoViewEventArgs.h"

ScrollingBringingIntoViewEventArgs::ScrollingBringingIntoViewEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

ScrollingBringingIntoViewEventArgs::~ScrollingBringingIntoViewEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

winrt::Islands::UI::Xaml::Controls::ScrollingSnapPointsMode ScrollingBringingIntoViewEventArgs::SnapPointsMode()
{
    return m_snapPointsMode;
}

void ScrollingBringingIntoViewEventArgs::SnapPointsMode(winrt::Islands::UI::Xaml::Controls::ScrollingSnapPointsMode snapPointsMode)
{
    m_snapPointsMode = snapPointsMode;
}

winrt::Windows::UI::Xaml::BringIntoViewRequestedEventArgs ScrollingBringingIntoViewEventArgs::RequestEventArgs()
{
    return m_requestEventArgs;
}

double ScrollingBringingIntoViewEventArgs::TargetHorizontalOffset()
{
    return m_targetHorizontalOffset;
}

double ScrollingBringingIntoViewEventArgs::TargetVerticalOffset()
{
    return m_targetVerticalOffset;
}

int32_t ScrollingBringingIntoViewEventArgs::CorrelationId()
{
    return m_offsetsChangeCorrelationId;
}

bool ScrollingBringingIntoViewEventArgs::Cancel()
{
    return m_cancel;
}

void ScrollingBringingIntoViewEventArgs::Cancel(bool value)
{
    m_cancel = value;
}

void ScrollingBringingIntoViewEventArgs::OffsetsChangeCorrelationId(int32_t offsetsChangeCorrelationId)
{
    m_offsetsChangeCorrelationId = offsetsChangeCorrelationId;
}

void ScrollingBringingIntoViewEventArgs::RequestEventArgs(const winrt::Windows::UI::Xaml::BringIntoViewRequestedEventArgs& requestEventArgs)
{
    m_requestEventArgs = requestEventArgs;
}

void ScrollingBringingIntoViewEventArgs::TargetOffsets(double targetHorizontalOffset, double targetVerticalOffset)
{
    m_targetHorizontalOffset = targetHorizontalOffset;
    m_targetVerticalOffset = targetVerticalOffset;
}
