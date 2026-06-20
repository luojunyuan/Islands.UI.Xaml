#include "pch.h"
#include "MuxcTraceLogging.h"

TRACELOGGING_DEFINE_PROVIDER(
    g_hTelemetryProvider,
    "Islands.UI.Xaml.Controls",
    (0x1f32d4ba, 0x0604, 0x4f91, 0xa8, 0x8f, 0x77, 0x16, 0x02, 0xf6, 0x35, 0x01));

TRACELOGGING_DEFINE_PROVIDER(
    g_hPerfProvider,
    "Islands.UI.Xaml.Controls.Perf",
    (0xe5b05f67, 0x7ef2, 0x4ac9, 0x87, 0xf2, 0x84, 0xbc, 0xaa, 0x34, 0x40, 0x11));

TRACELOGGING_DEFINE_PROVIDER(
    g_hLoggingProvider,
    "Islands.UI.Xaml.Controls.Debug",
    (0x76a9de77, 0xc7bf, 0x4336, 0x9a, 0xf2, 0x57, 0xc8, 0x20, 0x96, 0xaa, 0x22));

TRACELOGGING_DEFINE_PROVIDER(
    XamlTelemetryLogging,
    "Microsoft-Windows-XAML",
    (0x531a35ab, 0x63ce, 0x4bcf, 0xaa, 0x98, 0xf8, 0x8c, 0x7a, 0x89, 0xe4, 0x55));

bool g_IsTelemetryProviderEnabled{};
UCHAR g_TelemetryProviderLevel{};
ULONGLONG g_TelemetryProviderMatchAnyKeyword{};
GUID g_TelemetryProviderActivityId{};

bool g_IsPerfProviderEnabled{};
UCHAR g_PerfProviderLevel{};
ULONGLONG g_PerfProviderMatchAnyKeyword{};
GUID g_PerfProviderActivityId{};

bool g_IsLoggingProviderEnabled{};
UCHAR g_LoggingProviderLevel{};
ULONGLONG g_LoggingProviderMatchAnyKeyword{};
GUID g_LoggingProviderActivityId{};

void RegisterTraceLogging()
{
    TraceLoggingRegister(g_hTelemetryProvider);
    TraceLoggingRegister(g_hPerfProvider);
    TraceLoggingRegister(g_hLoggingProvider);
    TraceLoggingRegister(XamlTelemetryLogging);
}

void UnRegisterTraceLogging()
{
    TraceLoggingUnregister(XamlTelemetryLogging);
    TraceLoggingUnregister(g_hLoggingProvider);
    TraceLoggingUnregister(g_hPerfProvider);
    TraceLoggingUnregister(g_hTelemetryProvider);
}
