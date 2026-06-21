#pragma once

#include <SDKDDKVer.h>

#include <windows.h>
#include <windowsx.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#undef GetCurrentTime

#include <unknwn.h>
#include <restrictederrorinfo.h>
#include <hstring.h>
#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.Resources.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Automation.Peers.h>
#include <winrt/Windows.UI.Xaml.Automation.Provider.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.h>
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

#include "AppWindowTitleBar.h"
#include "InputNonClientPointerSource.h"
#include "TitleBar.h"
