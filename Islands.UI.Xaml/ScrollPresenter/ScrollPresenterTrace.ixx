module;

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <SDKDDKVer.h>
#include <Windows.h>
#include <TraceLoggingProvider.h>
#include <strsafe.h>

export module ixx.ScrollPresenterTrace;

import inc.common;
import ixx.MUXControlsTestHooks;
import ixx.MuxcTraceLogging;
import ixx.Utils;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



inline bool IsScrollPresenterTracingEnabled()
{
    return g_IsLoggingProviderEnabled &&
        g_LoggingProviderLevel >= WINEVENT_LEVEL_INFO &&
        (g_LoggingProviderMatchAnyKeyword & KeywordScrollPresenter || g_LoggingProviderMatchAnyKeyword == 0);
}

inline bool IsScrollPresenterVerboseTracingEnabled()
{
    return g_IsLoggingProviderEnabled &&
        g_LoggingProviderLevel >= WINEVENT_LEVEL_VERBOSE &&
        (g_LoggingProviderMatchAnyKeyword & KeywordScrollPresenter || g_LoggingProviderMatchAnyKeyword == 0);
}

inline bool IsScrollPresenterPerfTracingEnabled()
{
    return g_IsPerfProviderEnabled &&
        g_PerfProviderLevel >= WINEVENT_LEVEL_INFO &&
        (g_PerfProviderMatchAnyKeyword & KeywordScrollPresenter || g_PerfProviderMatchAnyKeyword == 0);
}

#define SCROLLPRESENTER_TRACE_INFO_ENABLED(includeTraceLogging, sender, message, ...) \
ScrollPresenterTrace::TraceInfo(includeTraceLogging, sender, message, __VA_ARGS__); \

#define SCROLLPRESENTER_TRACE_INFO(sender, message, ...) \
if (IsScrollPresenterTracingEnabled()) \
{ \
    SCROLLPRESENTER_TRACE_INFO_ENABLED(true /*includeTraceLogging*/, sender, message, __VA_ARGS__); \
} \
else if (ScrollPresenterTrace::s_IsDebugOutputEnabled || ScrollPresenterTrace::s_IsVerboseDebugOutputEnabled) \
{ \
    SCROLLPRESENTER_TRACE_INFO_ENABLED(false /*includeTraceLogging*/, sender, message, __VA_ARGS__); \
} \

#define SCROLLPRESENTER_TRACE_VERBOSE_ENABLED(includeTraceLogging, sender, message, ...) \
ScrollPresenterTrace::TraceVerbose(includeTraceLogging, sender, message, __VA_ARGS__); \

#define SCROLLPRESENTER_TRACE_VERBOSE(sender, message, ...) \
if (IsScrollPresenterVerboseTracingEnabled()) \
{ \
    SCROLLPRESENTER_TRACE_VERBOSE_ENABLED(true /*includeTraceLogging*/, sender, message, __VA_ARGS__); \
} \
else if (ScrollPresenterTrace::s_IsVerboseDebugOutputEnabled) \
{ \
    SCROLLPRESENTER_TRACE_VERBOSE_ENABLED(false /*includeTraceLogging*/, sender, message, __VA_ARGS__); \
} \

#define SCROLLPRESENTER_TRACE_PERF(info) \
if (IsScrollPresenterPerfTracingEnabled()) \
{ \
    ScrollPresenterTrace::TracePerfInfo(info); \
} \

#ifdef DBG
#define SCROLLPRESENTER_TRACE_INFO_DBG(sender, message, ...)    SCROLLPRESENTER_TRACE_INFO(sender, message, __VA_ARGS__)
#define SCROLLPRESENTER_TRACE_VERBOSE_DBG(sender, message, ...) SCROLLPRESENTER_TRACE_VERBOSE(sender, message, __VA_ARGS__)
#define SCROLLPRESENTER_TRACE_PERF_DBG(info)                    SCROLLPRESENTER_TRACE_PERF(info)
#else
#define SCROLLPRESENTER_TRACE_INFO_DBG(sender, message, ...)
#define SCROLLPRESENTER_TRACE_VERBOSE_DBG(sender, message, ...)
#define SCROLLPRESENTER_TRACE_PERF_DBG(info)
#endif // DBG

class ScrollPresenterTrace
{
public:
    static bool s_IsDebugOutputEnabled;
    static bool s_IsVerboseDebugOutputEnabled;

    static void TraceInfo(bool includeTraceLogging, const winrt::IInspectable& sender, PCWSTR message, ...) noexcept
    {
        va_list args;
        va_start(args, message);
        WCHAR buffer[384]{};
        if (SUCCEEDED(StringCchVPrintfW(buffer, ARRAYSIZE(buffer), message, args)))
        {
            if (includeTraceLogging)
            {
                // TraceViewers
                // http://toolbox/pef
                // http://fastetw/index.aspx
                TraceLoggingWrite(
                    g_hLoggingProvider,
                    "ScrollPresenterInfo" /* eventName */,
                    TraceLoggingLevel(WINEVENT_LEVEL_INFO),
                    TraceLoggingKeyword(KeywordScrollPresenter),
                    TraceLoggingWideString(buffer, "Message"));
            }

            if (s_IsDebugOutputEnabled)
            {
                OutputDebugStringW(buffer);
            }

            com_ptr<MUXControlsTestHooks> globalTestHooks = MUXControlsTestHooks::GetGlobalTestHooks();

            if (globalTestHooks &&
                (globalTestHooks->GetLoggingLevelForType(L"ScrollPresenter") >= WINEVENT_LEVEL_INFO || globalTestHooks->GetLoggingLevelForInstance(sender) >= WINEVENT_LEVEL_INFO))
            {
                globalTestHooks->LogMessage(sender, buffer, false /*isVerboseLevel*/);
            }
        }
        va_end(args);
    }

    static void TraceVerbose(bool includeTraceLogging, const winrt::IInspectable& sender, PCWSTR message, ...) noexcept
    {
        va_list args;
        va_start(args, message);
        WCHAR buffer[1024]{};
        const HRESULT hr = StringCchVPrintfW(buffer, ARRAYSIZE(buffer), message, args);
        if (SUCCEEDED(hr) || hr == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
        {
            if (includeTraceLogging)
            {
                // TraceViewers
                // http://toolbox/pef
                // http://fastetw/index.aspx
                TraceLoggingWrite(
                    g_hLoggingProvider,
                    "ScrollPresenterVerbose" /* eventName */,
                    TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
                    TraceLoggingKeyword(KeywordScrollPresenter),
                    TraceLoggingWideString(buffer, "Message"));
            }

            if (s_IsDebugOutputEnabled || s_IsVerboseDebugOutputEnabled)
            {
                OutputDebugStringW(buffer);
            }

            com_ptr<MUXControlsTestHooks> globalTestHooks = MUXControlsTestHooks::GetGlobalTestHooks();

            if (globalTestHooks &&
                (globalTestHooks->GetLoggingLevelForType(L"ScrollPresenter") >= WINEVENT_LEVEL_VERBOSE || globalTestHooks->GetLoggingLevelForInstance(sender) >= WINEVENT_LEVEL_VERBOSE))
            {
                globalTestHooks->LogMessage(sender, buffer, true /*isVerboseLevel*/);
            }
        }
        va_end(args);
    }

    static void TracePerfInfo(PCWSTR info) noexcept
    {
        // TraceViewers
        // http://toolbox/pef
        // http://fastetw/index.aspx
        TraceLoggingWrite(
            g_hPerfProvider,
            "ScrollPresenterPerf" /* eventName */,
            TraceLoggingLevel(WINEVENT_LEVEL_INFO),
            TraceLoggingKeyword(KeywordScrollPresenter),
            TraceLoggingWideString(info, "Info"));
    }
};

}
