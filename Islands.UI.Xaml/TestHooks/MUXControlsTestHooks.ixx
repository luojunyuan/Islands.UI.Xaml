// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

module;

#include <unknwn.h>
#include <inspectable.h>
#include "MUXControlsTestHooks.g.h"

export module ixx.MUXControlsTestHooks;

import std;
import inc.common;

import inc.WinEventLogLevels;
import ixx.MUXControlsTestHooksLoggingMessageEventArgs;

export
{
using UCHAR = unsigned char;

class MUXControlsTestHooks :
    public winrt::implementation::MUXControlsTestHooksT<MUXControlsTestHooks>
{
public:
    UCHAR GetLoggingLevelForType(const wstring_view& type);
    UCHAR GetLoggingLevelForInstance(const winrt::IInspectable& sender);
    void SetOutputDebugStringLevelForTypeImpl(const wstring_view& type, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);
    void SetLoggingLevelForTypeImpl(const wstring_view& type, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);
    void SetLoggingLevelForInstanceImpl(const winrt::IInspectable& sender, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);
    void LogMessage(const winrt::IInspectable& sender, const wstring_view& message, bool isVerboseLevel);
    winrt::event_token LoggingMessageImpl(winrt::TypedEventHandler<winrt::IInspectable, winrt::MUXControlsTestHooksLoggingMessageEventArgs> const& value);
    void LoggingMessageImpl(winrt::event_token const& token);

    static com_ptr<MUXControlsTestHooks> GetGlobalTestHooks()
    {
        if (!s_testHooks)
        {
            return {};
        }

        return s_testHooks->get_strong();
    }

    static void SetOutputDebugStringLevelForType(winrt::hstring const& type, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);
    static void SetLoggingLevelForType(winrt::hstring const& type, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);
    static void SetLoggingLevelForInstance(winrt::IInspectable const& sender, bool isLoggingInfoLevel, bool isLoggingVerboseLevel);

    static winrt::event_token LoggingMessage(winrt::TypedEventHandler<winrt::IInspectable, winrt::MUXControlsTestHooksLoggingMessageEventArgs> const& value);
    static void LoggingMessage(winrt::event_token const& token);
    
private:
    static MUXControlsTestHooks* s_testHooks;

    static void EnsureHooks();

private:
    winrt::event<winrt::TypedEventHandler<winrt::IInspectable, winrt::MUXControlsTestHooksLoggingMessageEventArgs>> m_loggingMessageEventSource;
    std::map<std::wstring /*key:Type*/, UCHAR /*value:LoggingProviderLevel*/, std::less<>> m_typeLoggingLevels;
    std::map<winrt::IInspectable /*key:Instance*/, UCHAR /*value:LoggingProviderLevel*/> m_instanceLoggingLevels;
    UCHAR m_globalLoggingLevel{ WINEVENT_LEVEL_NONE };
};
}
