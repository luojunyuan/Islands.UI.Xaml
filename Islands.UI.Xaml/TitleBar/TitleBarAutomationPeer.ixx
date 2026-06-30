module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "TitleBarAutomationPeer.g.h"

export module ixx.TitleBarAutomationPeer;

import inc.common;
import winrt.Windows.System;
import ixx.TitleBar;

export
{
class TitleBarAutomationPeer :
    public ReferenceTracker<TitleBarAutomationPeer, winrt::implementation::TitleBarAutomationPeerT>
{

public:
    TitleBarAutomationPeer(winrt::TitleBar const& owner);

    // IAutomationPeerOverrides 
    winrt::AutomationControlType GetAutomationControlTypeCore();
    winrt::hstring GetClassNameCore();
    winrt::hstring GetNameCore();
};

namespace winrt::Islands::UI::Xaml::Controls::implementation
{
    using TitleBarAutomationPeer = ::TitleBarAutomationPeer;
}
}
