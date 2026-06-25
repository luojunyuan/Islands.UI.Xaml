// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <cassert>

#define MUXCONTROLS_NAMESPACE Islands::UI::Xaml::Controls
#define WINRT_MUXC_NAMESPACE winrt::Islands::UI::Xaml::Controls
#define WINRT_MUXM_NAMESPACE winrt::Windows::UI::Xaml::Media


#define MUXCONTROLSROOT_NAMESPACE_STR L"Islands.UI.Xaml"
#define MUXCONTROLSMEDIA_NAMESPACE_STR L"Windows.UI.Xaml.Media"

#ifndef MUX_ASSERT
#define MUX_ASSERT(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_NOASSUME
#define MUX_ASSERT_NOASSUME(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_MSG
#define MUX_ASSERT_MSG(condition, message) assert((condition) && (message))
#endif
