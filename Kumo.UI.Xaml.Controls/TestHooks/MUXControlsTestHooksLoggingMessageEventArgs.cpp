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
#include "MUXControlsTestHooksLoggingMessageEventArgs.ixx"

winrt::hstring MUXControlsTestHooksLoggingMessageEventArgs::Message()
{
    return m_message;
}

bool MUXControlsTestHooksLoggingMessageEventArgs::IsVerboseLevel()
{
    return m_isVerboseLevel;
}

void MUXControlsTestHooksLoggingMessageEventArgs::SetMessage(const wstring_view& message)
{
    m_message = message;
}

void MUXControlsTestHooksLoggingMessageEventArgs::SetIsVerboseLevel(bool isVerboseLevel)
{
    m_isVerboseLevel = isVerboseLevel;
}
