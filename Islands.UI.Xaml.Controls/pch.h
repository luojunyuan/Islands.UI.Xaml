#pragma once

#include <SDKDDKVer.h>

#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>

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

#undef GetCurrentTime

#include <cassert>
#include <unknwn.h>
#include <inspectable.h>
#include <restrictederrorinfo.h>
#include <hstring.h>
#include <windows.ui.xaml.hosting.referencetracker.h>

#include "inc/CppWinRTIncludes.h"
#include "inc/BuildMacros.h"

//#include <winrt/base.h>
//#include <winrt/Windows.ApplicationModel.Resources.h>
//#include <winrt/Windows.Foundation.h>
//#include <winrt/Windows.Foundation.Collections.h>
//#include <winrt/Windows.UI.Xaml.h>
//#include <winrt/Windows.UI.Xaml.Automation.h>
//#include <winrt/Windows.UI.Xaml.Automation.Peers.h>
//#include <winrt/Windows.UI.Xaml.Automation.Provider.h>
//#include <winrt/Windows.UI.Xaml.Controls.h>
//#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
//#include <winrt/Windows.UI.Xaml.Data.h>
//#include <winrt/Windows.UI.Xaml.Interop.h>
//#include <winrt/Windows.UI.Xaml.Markup.h>
//#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Controls.AnimatedVisuals.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/Islands.UI.Xaml.Controls.h>

namespace winrt
{
namespace xaml = Windows::UI::Xaml;
namespace xaml_automation = Windows::UI::Xaml::Automation;
namespace xaml_peers = Windows::UI::Xaml::Automation::Peers;
namespace xaml_controls = Windows::UI::Xaml::Controls;
namespace xaml_primitives = Windows::UI::Xaml::Controls::Primitives;
namespace xaml_interop = Windows::UI::Xaml::Interop;
namespace xaml_markup = Windows::UI::Xaml::Markup;
namespace xaml_media = Windows::UI::Xaml::Media;
namespace muxc = Microsoft::UI::Xaml::Controls;
}

using namespace std::string_view_literals;
using namespace std::chrono_literals;

//using winrt::operator co_await;

#ifndef MUX_ASSERT
#define MUX_ASSERT(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_NOASSUME
#define MUX_ASSERT_NOASSUME(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_MSG
#define MUX_ASSERT_MSG(condition, message) assert((condition) && (message))
#endif

#include "AppWindowTitleBar.h"
#include "InputNonClientPointerSource.h"
#include "TitleBar.h"
