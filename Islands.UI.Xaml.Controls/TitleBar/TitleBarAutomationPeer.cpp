#include "pch.h"
#include "TitleBar.h"
#include "TitleBarAutomationPeer.h"
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
