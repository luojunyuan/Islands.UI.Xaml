// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#define KUMO_USE_IMPORT_STD 1
#define KUMO_DEFER_PREAMBLE_USINGS 1
#include "KumoPreamble.ixx"
import std;
import winrt_base;
import winrt;
#include "KumoPostImports.ixx"
#include "common.ixx"
#include "ScrollPresenterTestHooksInteractionSourcesChangedEventArgs.ixx"

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
