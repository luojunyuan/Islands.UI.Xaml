// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

import winrt_base;
import winrt.Islands.UI.Xaml.Controls.Primitives;
import winrt.Windows.UI.Composition.Interactions;

#define WINRT_IMPORT_MODULE
#include "ScrollPresenterTestHooksInteractionSourcesChangedEventArgs.h"
#undef WINRT_IMPORT_MODULE

ScrollPresenterTestHooksInteractionSourcesChangedEventArgs::ScrollPresenterTestHooksInteractionSourcesChangedEventArgs(
    const winrt::Windows::UI::Composition::Interactions::CompositionInteractionSourceCollection& interactionSources)
{
    m_interactionSources = interactionSources;
}

#pragma region IScrollPresenterTestHooksInteractionSourcesChangedEventArgs

winrt::Windows::UI::Composition::Interactions::CompositionInteractionSourceCollection ScrollPresenterTestHooksInteractionSourcesChangedEventArgs::InteractionSources()
{
    return m_interactionSources;
}

#pragma endregion
