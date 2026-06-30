module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "ScrollingAnchorRequestedEventArgs.g.h"

export module ixx.ScrollingAnchorRequestedEventArgs;

import inc.common;
import inc.tracker_ref;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollingAnchorRequestedEventArgs :
    public ReferenceTracker<ScrollingAnchorRequestedEventArgs, winrt::Islands::UI::Xaml::Controls::implementation::ScrollingAnchorRequestedEventArgsT, winrt::composable, winrt::composing>
{
public:
    ~ScrollingAnchorRequestedEventArgs();

    ScrollingAnchorRequestedEventArgs(const winrt::Islands::UI::Xaml::Controls::Primitives::ScrollPresenter& scrollPresenter);

#pragma region IScrollingAnchorRequestedEventArgs
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::UIElement> AnchorCandidates();
    winrt::Windows::UI::Xaml::UIElement AnchorElement();
    void AnchorElement(winrt::Windows::UI::Xaml::UIElement const& value);
#pragma endregion

    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::UIElement> GetAnchorCandidates();
    void SetAnchorCandidates(const std::vector<tracker_ref<winrt::Windows::UI::Xaml::UIElement>>& anchorCandidates);

    winrt::Windows::UI::Xaml::UIElement GetAnchorElement() const;
    void SetAnchorElement(const winrt::Windows::UI::Xaml::UIElement& anchorElement);

private:
    tracker_ref<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::UIElement>> m_anchorCandidates{ this };
    tracker_ref<winrt::Windows::UI::Xaml::UIElement> m_anchorElement{ this };
    tracker_ref<winrt::Islands::UI::Xaml::Controls::Primitives::ScrollPresenter> m_scrollPresenter{ this };
};


namespace winrt::Islands::UI::Xaml::Controls::implementation { using ScrollingAnchorRequestedEventArgs = ::ScrollingAnchorRequestedEventArgs; }
}
