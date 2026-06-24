import std;
import winrt_base;
import winrt.Windows.Foundation;
import winrt.Windows.UI.Xaml;
import winrt.Windows.UI.Xaml.Automation.Peers;
import winrt.Windows.UI.Xaml.Controls;
import winrt.Windows.UI.Xaml.Interop;
import winrt.Microsoft.UI.Xaml.Controls;
import winrt.Islands.UI.Xaml.Controls;

namespace winrt
{
namespace xaml = Windows::UI::Xaml;
namespace xaml_peers = Windows::UI::Xaml::Automation::Peers;
namespace xaml_controls = Windows::UI::Xaml::Controls;
namespace xaml_interop = Windows::UI::Xaml::Interop;
namespace muxc = Microsoft::UI::Xaml::Controls;
}

using namespace std::string_view_literals;

#define WINRT_IMPORT_MODULE
#include "TitleBar.h"
#include "TitleBarAutomationPeer.h"
#undef WINRT_IMPORT_MODULE

#if __has_include("TitleBarAutomationPeer.g.cpp")
#include "TitleBarAutomationPeer.g.cpp"
#endif

namespace winrt::Islands::UI::Xaml::Controls::implementation
{

TitleBarAutomationPeer::TitleBarAutomationPeer(winrt::Islands::UI::Xaml::Controls::TitleBar const& owner) :
    TitleBarAutomationPeerT<TitleBarAutomationPeer>(owner)
{
}

winrt::xaml_peers::AutomationControlType TitleBarAutomationPeer::GetAutomationControlTypeCore()
{
    return winrt::xaml_peers::AutomationControlType::TitleBar;
}

winrt::hstring TitleBarAutomationPeer::GetClassNameCore()
{
    return winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>().Name;
}

winrt::hstring TitleBarAutomationPeer::GetNameCore()
{
    winrt::hstring name = __super::GetNameCore();

    if (name.empty())
    {
        if (auto titleBar = Owner().try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
        {
            name = titleBar.Title();
        }
    }

    return name;
}

}
