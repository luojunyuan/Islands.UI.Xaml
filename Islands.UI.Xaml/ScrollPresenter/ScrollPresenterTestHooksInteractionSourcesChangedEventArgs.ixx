module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "Primitives.ScrollPresenterTestHooksInteractionSourcesChangedEventArgs.g.h"

export module ixx.ScrollPresenterTestHooksInteractionSourcesChangedEventArgs;

import inc.common;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollPresenterTestHooksInteractionSourcesChangedEventArgs :
    public winrt::Islands::UI::Xaml::Controls::Primitives::implementation::ScrollPresenterTestHooksInteractionSourcesChangedEventArgsT<ScrollPresenterTestHooksInteractionSourcesChangedEventArgs>
{
public:
    ScrollPresenterTestHooksInteractionSourcesChangedEventArgs(const winrt::Windows::UI::Composition::Interactions::CompositionInteractionSourceCollection& interactionSources);

    // IScrollPresenterTestHooksInteractionSourcesChangedEventArgs overrides
    winrt::Windows::UI::Composition::Interactions::CompositionInteractionSourceCollection InteractionSources();
        
private:
    winrt::Windows::UI::Composition::Interactions::CompositionInteractionSourceCollection m_interactionSources{ nullptr };
};


namespace winrt::Islands::UI::Xaml::Controls::Primitives::implementation { using ScrollPresenterTestHooksInteractionSourcesChangedEventArgs = ::ScrollPresenterTestHooksInteractionSourcesChangedEventArgs; }
}
