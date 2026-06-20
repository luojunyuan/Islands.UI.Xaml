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
#include "ScrollPresenterTypeLogging.ixx"
#include "ZoomFactorChange.ixx"

ZoomFactorChange::ZoomFactorChange(
    float zoomFactor,
    winrt::IReference<winrt::float2> centerPoint,
    ScrollPresenterViewKind zoomFactorKind,
    winrt::IInspectable const& options) :
        m_zoomFactor(zoomFactor),
        m_centerPoint(centerPoint),
        ViewChange(zoomFactorKind, options)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR_FLT, METH_NAME, this,
        TypeLogging::NullableFloat2ToString(centerPoint).c_str(), zoomFactor);
}

ZoomFactorChange::~ZoomFactorChange()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}
