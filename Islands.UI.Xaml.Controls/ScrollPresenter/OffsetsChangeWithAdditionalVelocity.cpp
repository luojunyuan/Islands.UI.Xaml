// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <SDKDDKVer.h>

#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#undef GetCurrentTime

#include <unknwn.h>
#include <inspectable.h>
#include <restrictederrorinfo.h>
#include <hstring.h>
#include <windows.ui.xaml.hosting.referencetracker.h>

#include "inc/CppWinRTIncludes.h"
#include "inc/BuildMacros.h"

#ifndef MUX_ASSERT
#define MUX_ASSERT(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_NOASSUME
#define MUX_ASSERT_NOASSUME(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_MSG
#define MUX_ASSERT_MSG(condition, message) assert((condition) && (message))
#endif

#include "TypeLogging.h"
#include "ScrollPresenterTrace.h"
#include "OffsetsChangeWithAdditionalVelocity.h"

OffsetsChangeWithAdditionalVelocity::OffsetsChangeWithAdditionalVelocity(
    winrt::float2 offsetsVelocity,
    winrt::float2 anticipatedOffsetsChange,
    winrt::IReference<winrt::float2> inertiaDecayRate) :
        m_offsetsVelocity(offsetsVelocity),
        m_anticipatedOffsetsChange(anticipatedOffsetsChange),
        m_inertiaDecayRate(inertiaDecayRate)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR_STR_STR, METH_NAME, this,
        TypeLogging::Float2ToString(offsetsVelocity).c_str(),
        TypeLogging::Float2ToString(anticipatedOffsetsChange).c_str(),
        TypeLogging::NullableFloat2ToString(inertiaDecayRate).c_str());
}

OffsetsChangeWithAdditionalVelocity::~OffsetsChangeWithAdditionalVelocity()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

void OffsetsChangeWithAdditionalVelocity::OffsetsVelocity(winrt::float2 const& offsetsVelocity)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR, METH_NAME, this, TypeLogging::Float2ToString(offsetsVelocity).c_str());

    m_offsetsVelocity = offsetsVelocity;
}

void OffsetsChangeWithAdditionalVelocity::AnticipatedOffsetsChange(winrt::float2 const& anticipatedOffsetsChange)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR, METH_NAME, this, TypeLogging::Float2ToString(anticipatedOffsetsChange).c_str());

    m_anticipatedOffsetsChange = anticipatedOffsetsChange;
}

void OffsetsChangeWithAdditionalVelocity::InertiaDecayRate(winrt::IReference<winrt::float2> const& inertiaDecayRate)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR, METH_NAME, this, TypeLogging::NullableFloat2ToString(inertiaDecayRate).c_str());

    m_inertiaDecayRate = inertiaDecayRate;
}
