// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "WinEventLogLevels.h"
#include "MUXControlsTestHooksLoggingMessageEventArgs.h"

// Logging level that results in no logging at all.
#define WINEVENT_LEVEL_NONE 0x0

#include "Primitives.MUXControlsTestHooks.g.h"

class MUXControlsTestHooks :
    public winrt::Islands::UI::Xaml::Controls::Primitives::implementation::MUXControlsTestHooksT<MUXControlsTestHooks>
{
public:
    unsigned char GetLoggingLevelForType(const std::wstring_view& type);
    unsigned char GetLoggingLevelForInstance(const winrt::Windows::Foundation::IInspectable& sender);
    void SetOutputDebugStringLevelForTypeImpl(const std::wstring_view& type, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);
    void SetLoggingLevelForTypeImpl(const std::wstring_view& type, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);
    void SetLoggingLevelForInstanceImpl(const winrt::Windows::Foundation::IInspectable& sender, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);
    void LogMessage(const winrt::Windows::Foundation::IInspectable& sender, const std::wstring_view& message, bool isVerboseLevel);
    winrt::event_token LoggingMessageImpl(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Islands::UI::Xaml::Controls::Primitives::MUXControlsTestHooksLoggingMessageEventArgs> const& value);
    void LoggingMessageImpl(winrt::event_token const& token);
    winrt::event_token BuildTreeCompletedImpl(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable> const& value); // subscribe
    void BuildTreeCompletedImpl(winrt::event_token const& token); // unsubscribe
    void NotifyBuildTreeCompletedImpl();

    static winrt::com_ptr<MUXControlsTestHooks> GetGlobalTestHooks()
    {
        return s_testHooks->get_strong();
    }

    static void SetOutputDebugStringLevelForType(winrt::hstring const& type, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);
    static void SetLoggingLevelForType(winrt::hstring const& type, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);
    static void SetLoggingLevelForInstance(winrt::Windows::Foundation::IInspectable const& sender, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);

    static winrt::event_token LoggingMessage(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Islands::UI::Xaml::Controls::Primitives::MUXControlsTestHooksLoggingMessageEventArgs> const& value);
    static void LoggingMessage(winrt::event_token const& token);

    static winrt::event_token BuildTreeCompleted(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable> const& value); // subscribe
    static void BuildTreeCompleted(winrt::event_token const& token); // unsubscribe
    static void NotifyBuildTreeCompleted();
    
private:
    static MUXControlsTestHooks* s_testHooks;

    static void EnsureHooks();

private:
    winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Islands::UI::Xaml::Controls::Primitives::MUXControlsTestHooksLoggingMessageEventArgs>> m_loggingMessageEventSource;
    std::map<std::wstring /*key:Type*/, unsigned char /*value:LoggingProviderLevel*/, std::less<>> m_typeLoggingLevels;
    std::map<winrt::Windows::Foundation::IInspectable /*key:Instance*/, unsigned char /*value:LoggingProviderLevel*/> m_instanceLoggingLevels;
    unsigned char m_globalLoggingLevel{ WINEVENT_LEVEL_NONE };
    winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable>> m_buildTreeCompleted;
};
