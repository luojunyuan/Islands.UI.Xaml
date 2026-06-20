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
#include "ScrollingScrollOptions.ixx"

#include "ScrollingScrollOptions.properties.cpp"

ScrollingScrollOptions::ScrollingScrollOptions(
    winrt::ScrollingAnimationMode const& animationMode)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR, METH_NAME, this,
        TypeLogging::AnimationModeToString(animationMode).c_str());

    m_animationMode = animationMode;
}

ScrollingScrollOptions::ScrollingScrollOptions(
    winrt::ScrollingAnimationMode const& animationMode,
    winrt::ScrollingSnapPointsMode const& snapPointsMode)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR_STR, METH_NAME, this,
        TypeLogging::AnimationModeToString(animationMode).c_str(),
        TypeLogging::SnapPointsModeToString(snapPointsMode).c_str());

    m_animationMode = animationMode;
    m_snapPointsMode = snapPointsMode;
}

winrt::ScrollingAnimationMode ScrollingScrollOptions::AnimationMode() const
{
    return m_animationMode;
}

void ScrollingScrollOptions::AnimationMode(winrt::ScrollingAnimationMode const& animationMode)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR, METH_NAME, this,
        TypeLogging::AnimationModeToString(animationMode).c_str());

    m_animationMode = animationMode;
}

winrt::ScrollingSnapPointsMode ScrollingScrollOptions::SnapPointsMode() const
{
    return m_snapPointsMode;
}

void ScrollingScrollOptions::SnapPointsMode(winrt::ScrollingSnapPointsMode const& snapPointsMode)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_STR, METH_NAME, this,
        TypeLogging::SnapPointsModeToString(snapPointsMode).c_str());

    m_snapPointsMode = snapPointsMode;
}
