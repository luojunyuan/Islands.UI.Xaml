module;

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <SDKDDKVer.h>
#include <Windows.h>
#include <TraceLoggingProvider.h>
#include <strsafe.h>

export module ixx.TitleBarTrace;

import inc.common;
import ixx.MuxcTraceLogging;
import ixx.MUXControlsTestHooks;

namespace
{
    bool IsTitleBarTracingEnabled()
    {
        return g_IsLoggingProviderEnabled &&
            g_LoggingProviderLevel >= WINEVENT_LEVEL_INFO &&
            ((g_LoggingProviderMatchAnyKeyword & KeywordTitleBar) || g_LoggingProviderMatchAnyKeyword == 0);
    }

    bool IsTitleBarVerboseTracingEnabled()
    {
        return g_IsLoggingProviderEnabled &&
            g_LoggingProviderLevel >= WINEVENT_LEVEL_VERBOSE &&
            ((g_LoggingProviderMatchAnyKeyword & KeywordTitleBar) || g_LoggingProviderMatchAnyKeyword == 0);
    }

    bool IsTitleBarPerfTracingEnabled()
    {
        return g_IsPerfProviderEnabled &&
            g_PerfProviderLevel >= WINEVENT_LEVEL_INFO &&
            ((g_PerfProviderMatchAnyKeyword & KeywordTitleBar) || g_PerfProviderMatchAnyKeyword == 0);
    }
}

export class TitleBarTrace
{
public:
    static bool s_IsDebugOutputEnabled;
    static bool s_IsVerboseDebugOutputEnabled;

    static bool IsInfoEnabled() noexcept
    {
        return IsTitleBarTracingEnabled() || s_IsDebugOutputEnabled || s_IsVerboseDebugOutputEnabled;
    }

    static bool IsVerboseEnabled() noexcept
    {
        return IsTitleBarVerboseTracingEnabled() || s_IsVerboseDebugOutputEnabled;
    }

    static bool IsPerfEnabled() noexcept
    {
        return IsTitleBarPerfTracingEnabled();
    }

    static void Info(const winrt::IInspectable& sender, PCWSTR message, ...) noexcept
    {
        if (!IsInfoEnabled())
        {
            return;
        }

        va_list args;
        va_start(args, message);
        TraceMessage(false, IsTitleBarTracingEnabled(), s_IsDebugOutputEnabled || s_IsVerboseDebugOutputEnabled, sender, message, args);
        va_end(args);
    }

    static void Verbose(const winrt::IInspectable& sender, PCWSTR message, ...) noexcept
    {
        if (!IsVerboseEnabled())
        {
            return;
        }

        va_list args;
        va_start(args, message);
        TraceMessage(true, IsTitleBarVerboseTracingEnabled(), s_IsVerboseDebugOutputEnabled, sender, message, args);
        va_end(args);
    }

    static void Perf(PCWSTR info) noexcept
    {
        if (!IsPerfEnabled())
        {
            return;
        }

        TraceLoggingWrite(
            g_hPerfProvider,
            "TitleBarPerf",
            TraceLoggingLevel(WINEVENT_LEVEL_INFO),
            TraceLoggingKeyword(KeywordTitleBar),
            TraceLoggingWideString(info, "Info"));
    }

private:
    static void TraceMessage(
        bool isVerboseTrace,
        bool includeTraceLogging,
        bool includeDebugOutput,
        const winrt::IInspectable& sender,
        PCWSTR message,
        va_list args) noexcept
    {
        WCHAR buffer[256]{};
        if (!succeeded(StringCchVPrintfW(buffer, array_size(buffer), message, args)))
        {
            return;
        }

        if (includeTraceLogging)
        {
            if (isVerboseTrace)
            {
                TraceLoggingWrite(
                    g_hLoggingProvider,
                    "TitleBarVerbose",
                    TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
                    TraceLoggingKeyword(KeywordTitleBar),
                    TraceLoggingWideString(buffer, "Message"));
            }
            else
            {
                TraceLoggingWrite(
                    g_hLoggingProvider,
                    "TitleBarInfo",
                    TraceLoggingLevel(WINEVENT_LEVEL_INFO),
                    TraceLoggingKeyword(KeywordTitleBar),
                    TraceLoggingWideString(buffer, "Message"));
            }
        }

        if (includeDebugOutput)
        {
            OutputDebugStringW(buffer);
        }

        com_ptr<MUXControlsTestHooks> globalTestHooks = MUXControlsTestHooks::GetGlobalTestHooks();
        if (!globalTestHooks)
        {
            return;
        }

        const auto requiredLevel = isVerboseTrace ? WINEVENT_LEVEL_VERBOSE : WINEVENT_LEVEL_INFO;
        if (globalTestHooks->GetLoggingLevelForType(L"TitleBar") >= requiredLevel ||
            globalTestHooks->GetLoggingLevelForInstance(sender) >= requiredLevel)
        {
            globalTestHooks->LogMessage(sender, buffer, isVerboseTrace);
        }
    }
};
