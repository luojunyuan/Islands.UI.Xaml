#pragma once

#include "TitleBarAutomationPeer.g.h"

namespace winrt::Islands::UI::Xaml::Controls::implementation
{

struct TitleBarAutomationPeer : TitleBarAutomationPeerT<TitleBarAutomationPeer>
{
    TitleBarAutomationPeer(winrt::Islands::UI::Xaml::Controls::TitleBar const& owner);

    winrt::xaml_peers::AutomationControlType GetAutomationControlTypeCore();
    winrt::hstring GetClassNameCore();
    winrt::hstring GetNameCore();
};

}

namespace winrt::Islands::UI::Xaml::Controls::factory_implementation
{

struct TitleBarAutomationPeer : TitleBarAutomationPeerT<TitleBarAutomationPeer, implementation::TitleBarAutomationPeer>
{
};

}
