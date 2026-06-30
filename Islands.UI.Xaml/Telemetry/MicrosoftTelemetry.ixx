export module ixx.MicrosoftTelemetry;

import std;

export inline constexpr std::uint64_t PDT_BrowsingHistory = 0x0000000000000002u;
export inline constexpr std::uint64_t PDT_DeviceConnectivityAndConfiguration = 0x0000000000000800u;
export inline constexpr std::uint64_t PDT_InkingTypingAndSpeechUtterance = 0x0000000000020000u;
export inline constexpr std::uint64_t PDT_ProductAndServicePerformance = 0x0000000001000000u;
export inline constexpr std::uint64_t PDT_ProductAndServiceUsage = 0x0000000002000000u;
export inline constexpr std::uint64_t PDT_SoftwareSetupAndInventory = 0x0000000080000000u;

export inline constexpr std::uint64_t MICROSOFT_KEYWORD_CRITICAL_DATA = 0x0000800000000000;
export inline constexpr std::uint64_t MICROSOFT_KEYWORD_MEASURES = 0x0000400000000000;
export inline constexpr std::uint64_t MICROSOFT_KEYWORD_TELEMETRY = 0x0000200000000000;
export inline constexpr std::uint64_t MICROSOFT_KEYWORD_RESERVED_44 = 0x0000100000000000;

export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_DROP_USER_IDS = 0x00008000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_AGGREGATE = 0x00010000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_DROP_PII_EXCEPT_IP = 0x00020000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_COSTDEFERRED_LATENCY = 0x00040000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_CORE_DATA = 0x00080000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_INJECT_XTOKEN = 0x00100000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_REALTIME_LATENCY = 0x00200000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_NORMAL_LATENCY = 0x00400000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_CRITICAL_PERSISTENCE = 0x00800000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_NORMAL_PERSISTENCE = 0x01000000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_DROP_PII = 0x02000000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_HASH_PII = 0x04000000;
export inline constexpr std::uint32_t MICROSOFT_EVENTTAG_MARK_PII = 0x08000000;

export inline constexpr std::uint32_t MICROSOFT_FIELDTAG_DROP_PII = 0x04000000;
export inline constexpr std::uint32_t MICROSOFT_FIELDTAG_HASH_PII = 0x08000000;
