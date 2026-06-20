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
#include "ViewChange.ixx"

ViewChange::ViewChange(
    ScrollPresenterViewKind viewKind,
    winrt::IInspectable const& options)
    : m_viewKind(viewKind)
    , m_options(options)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR_STR, METH_NAME, this,
        options,
        TypeLogging::ScrollPresenterViewKindToString(viewKind).c_str());
}

ViewChange::~ViewChange()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}
