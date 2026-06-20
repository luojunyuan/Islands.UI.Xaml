#pragma once

#include <SDKDDKVer.h>

#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>

#undef GetCurrentTime

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
#include <unknwn.h>
#include <inspectable.h>
#include <restrictederrorinfo.h>
#include <hstring.h>
#include <windows.ui.xaml.hosting.referencetracker.h>

#include "inc/CppWinRTIncludes.h"
#include "inc/BuildMacros.h"

using namespace std::chrono_literals;
using namespace std::string_view_literals;

using winrt::operator co_await;

#ifndef MUX_ASSERT
#define MUX_ASSERT(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_NOASSUME
#define MUX_ASSERT_NOASSUME(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_MSG
#define MUX_ASSERT_MSG(condition, message) assert((condition) && (message))
#endif
