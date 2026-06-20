// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

using namespace ::winrt::Windows::Foundation;
using namespace ::winrt::Windows::Foundation::Numerics;

using namespace std::chrono_literals;
using namespace std::string_view_literals;

using ResourceIdType = const winrt::hstring &;

#include "ErrorHandling.ixx"
#include "CppWinRTHelpers.ixx"
#include "RuntimeClassHelpers.ixx"
#include "SharedHelpers.ixx"
#include "BoxHelpers.ixx"
#include "CastHelpers.ixx"
#include "event.ixx"
#include "AutoHandle.ixx"
#include "GlobalDependencyProperty.ixx"
#include "CollectionHelper.ixx"
#include "RoutedEventHelpers.ixx"
