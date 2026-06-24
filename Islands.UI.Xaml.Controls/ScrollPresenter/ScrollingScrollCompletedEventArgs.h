// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "ViewChangeBase.h"
#include "ScrollingScrollCompletedEventArgs.g.h"

class ScrollingScrollCompletedEventArgs :
    public winrt::Islands::UI::Xaml::Controls::implementation::ScrollingScrollCompletedEventArgsT<ScrollingScrollCompletedEventArgs>
{
public:
    ScrollingScrollCompletedEventArgs();

    ~ScrollingScrollCompletedEventArgs();

    // IScrollingScrollCompletedEventArgs overrides
    int32_t CorrelationId();
    ScrollPresenterViewChangeResult Result();

    void OffsetsChangeCorrelationId(int32_t offsetsChangeCorrelationId);
    void Result(ScrollPresenterViewChangeResult result);

private:
    int32_t m_offsetsChangeCorrelationId{ -1 };
    ScrollPresenterViewChangeResult m_result{ ScrollPresenterViewChangeResult::Completed };
};
