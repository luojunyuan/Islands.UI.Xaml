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
#include "OffsetsChange.ixx"

OffsetsChange::OffsetsChange(
    double zoomedHorizontalOffset,
    double zoomedVerticalOffset,
    ScrollPresenterViewKind offsetsKind,
    winrt::IInspectable const& options) :
        m_zoomedHorizontalOffset(zoomedHorizontalOffset),
        m_zoomedVerticalOffset(zoomedVerticalOffset),
        ViewChange(offsetsKind, options)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_DBL_DBL, METH_NAME, this,
        zoomedHorizontalOffset, zoomedVerticalOffset);
}

OffsetsChange::~OffsetsChange()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

void OffsetsChange::ZoomedHorizontalOffset(double zoomedHorizontalOffset)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_DBL, METH_NAME, this, zoomedHorizontalOffset);

    m_zoomedHorizontalOffset = zoomedHorizontalOffset;
}

void OffsetsChange::ZoomedVerticalOffset(double zoomedVerticalOffset)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_DBL, METH_NAME, this, zoomedVerticalOffset);

    m_zoomedVerticalOffset = zoomedVerticalOffset;
}
