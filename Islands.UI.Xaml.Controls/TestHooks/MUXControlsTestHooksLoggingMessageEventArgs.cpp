// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

import std;
import winrt_base;
import winrt.Islands.UI.Xaml.Controls.Primitives;

#define WINRT_IMPORT_MODULE
#include "MUXControlsTestHooksLoggingMessageEventArgs.h"
#undef WINRT_IMPORT_MODULE

winrt::hstring MUXControlsTestHooksLoggingMessageEventArgs::Message()
{
    return m_message;
}

bool MUXControlsTestHooksLoggingMessageEventArgs::IsVerboseLevel()
{
    return m_isVerboseLevel;
}

void MUXControlsTestHooksLoggingMessageEventArgs::SetMessage(const std::wstring_view& message)
{
    m_message = message;
}

void MUXControlsTestHooksLoggingMessageEventArgs::SetIsVerboseLevel(bool isVerboseLevel)
{
    m_isVerboseLevel = isVerboseLevel;
}
