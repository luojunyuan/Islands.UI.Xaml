#pragma once

#include <SDKDDKVer.h>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 0
#endif
#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 0
#endif
#ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 0
#endif

#ifdef KUMO_USE_IMPORT_STD
#ifndef WINRT_IMPORT_MODULE
#define WINRT_IMPORT_MODULE
#endif
#ifndef INFINITY
#define INFINITY (std::numeric_limits<double>::infinity())
#endif
#ifndef NAN
#define NAN (std::numeric_limits<double>::quiet_NaN())
#endif
#ifndef isnan
#define isnan std::isnan
#endif
#ifndef isinf
#define isinf std::isinf
#endif
#ifndef isfinite
#define isfinite std::isfinite
#endif
#endif

#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>

#ifndef KUMO_USE_IMPORT_STD
#include <algorithm>
#include <array>
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
#include <cassert>
#endif

#undef GetCurrentTime


#include <unknwn.h>
#include <inspectable.h>
#include <restrictederrorinfo.h>
#include <hstring.h>
#include <windows.ui.xaml.hosting.referencetracker.h>

#ifndef KUMO_DEFER_PREAMBLE_USINGS
#include "inc/CppWinRTIncludes.ixx"
#endif
#include "inc/BuildMacros.ixx"

#ifndef KUMO_DEFER_PREAMBLE_USINGS
using namespace std::chrono_literals;
using namespace std::string_view_literals;

using winrt::operator co_await;
#endif

#ifndef MUX_ASSERT
#ifdef _DEBUG
#define MUX_ASSERT(condition) do { if (!(condition)) { __debugbreak(); } } while (false)
#else
#define MUX_ASSERT(condition) ((void)0)
#endif
#endif

#ifndef MUX_ASSERT_NOASSUME
#define MUX_ASSERT_NOASSUME(condition) MUX_ASSERT(condition)
#endif

#ifndef MUX_ASSERT_MSG
#define MUX_ASSERT_MSG(condition, message) MUX_ASSERT(condition)
#endif
