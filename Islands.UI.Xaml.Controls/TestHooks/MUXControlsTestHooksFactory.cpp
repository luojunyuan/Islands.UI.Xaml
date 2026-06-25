// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "CppBaseIncludes.h"

import CppWinRTModules;

#define WINRT_IMPORT_MODULE
#include "MUXControlsTestHooks.h"
#undef WINRT_IMPORT_MODULE

MUXControlsTestHooks* MUXControlsTestHooks::s_testHooks = nullptr;

void MUXControlsTestHooks::EnsureHooks()
{
    if (!s_testHooks)
    {
        s_testHooks = winrt::make_self<MUXControlsTestHooks>().detach();
    }
}

void MUXControlsTestHooks::SetOutputDebugStringLevelForType(winrt::hstring const& type, bool isLoggingInfoLevel, bool isLoggingVerboseLevel)
{
    EnsureHooks();
    s_testHooks->SetOutputDebugStringLevelForTypeImpl(type, isLoggingInfoLevel, isLoggingVerboseLevel);
}

void MUXControlsTestHooks::SetLoggingLevelForType(winrt::hstring const& type, bool isLoggingInfoLevel, bool isLoggingVerboseLevel)
{
    EnsureHooks();
    s_testHooks->SetLoggingLevelForTypeImpl(type, isLoggingInfoLevel, isLoggingVerboseLevel);
}

void MUXControlsTestHooks::SetLoggingLevelForInstance(
    winrt::Windows::Foundation::IInspectable const& sender,
    bool isLoggingInfoLevel,
    bool isLoggingVerboseLevel)
{
    EnsureHooks();
    s_testHooks->SetLoggingLevelForInstanceImpl(sender, isLoggingInfoLevel, isLoggingVerboseLevel);
}

winrt::event_token MUXControlsTestHooks::LoggingMessage(
    winrt::Windows::Foundation::TypedEventHandler<
        winrt::Windows::Foundation::IInspectable,
        winrt::Islands::UI::Xaml::Controls::Primitives::MUXControlsTestHooksLoggingMessageEventArgs> const& value)
{
    EnsureHooks();
    return s_testHooks->LoggingMessageImpl(value);
}

void MUXControlsTestHooks::LoggingMessage(winrt::event_token const& token)
{
    if (s_testHooks)
    {
        s_testHooks->LoggingMessageImpl(token);
    }
}
