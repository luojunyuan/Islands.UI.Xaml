export module inc.WinEventLogLevels;

// From winmeta.h
export inline constexpr unsigned char WINEVENT_LEVEL_LOG_ALWAYS{ 0x0 };
export inline constexpr unsigned char WINEVENT_LEVEL_CRITICAL{ 0x1 };
export inline constexpr unsigned char WINEVENT_LEVEL_ERROR{ 0x2 };
export inline constexpr unsigned char WINEVENT_LEVEL_WARNING{ 0x3 };
export inline constexpr unsigned char WINEVENT_LEVEL_INFO{ 0x4 };
export inline constexpr unsigned char WINEVENT_LEVEL_VERBOSE{ 0x5 };
export inline constexpr unsigned char WINEVENT_LEVEL_NONE{ WINEVENT_LEVEL_LOG_ALWAYS };
