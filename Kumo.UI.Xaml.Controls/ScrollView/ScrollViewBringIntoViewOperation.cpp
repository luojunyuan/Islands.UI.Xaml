// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#define KUMO_USE_IMPORT_STD 1
#define KUMO_DEFER_PREAMBLE_USINGS 1
#include "KumoPreamble.ixx"
import std;
import winrt_base;
import winrt;
#include "KumoPostImports.ixx"
#include "ScrollViewBringIntoViewOperation.ixx"
#include "ScrollViewTrace.ixx"

ScrollViewBringIntoViewOperation::ScrollViewBringIntoViewOperation(winrt::UIElement const& targetElement, bool cancelBringIntoView)
{
    SCROLLVIEW_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR, METH_NAME, this, targetElement);

    m_targetElement = winrt::make_weak(targetElement);
    m_cancelBringIntoView = cancelBringIntoView;
}

ScrollViewBringIntoViewOperation::~ScrollViewBringIntoViewOperation()
{
    SCROLLVIEW_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR_INT, METH_NAME, this, m_targetElement.get(), m_ticksCount);
}

bool ScrollViewBringIntoViewOperation::HasMaxTicksCount() const
{
    MUX_ASSERT(m_ticksCount <= s_maxTicksCount);

    return m_ticksCount == s_maxTicksCount;
}

winrt::UIElement ScrollViewBringIntoViewOperation::TargetElement() const
{
    return m_targetElement.get();
}

int8_t ScrollViewBringIntoViewOperation::TicksCount() const
{
    return m_ticksCount;
}

int8_t ScrollViewBringIntoViewOperation::TickOperation()
{
    SCROLLVIEW_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR_INT, METH_NAME, this, m_targetElement.get(), m_ticksCount);

    MUX_ASSERT(m_ticksCount < s_maxTicksCount);

    return ++m_ticksCount;
}
