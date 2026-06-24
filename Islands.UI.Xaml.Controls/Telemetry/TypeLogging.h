// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace TypeLogging
{
    winrt::hstring KeyRoutedEventArgsToString(const winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs& eventArgs);
    winrt::hstring PointerPointToString(const winrt::Windows::UI::Input::PointerPoint& pointerPoint, bool verbose = false);
    winrt::hstring PointerDeviceTypeToString(const winrt::Windows::Devices::Input::PointerDeviceType& pointerDeviceKind);
    winrt::hstring PointerUpdateKindToString(const winrt::Windows::UI::Input::PointerUpdateKind& pointerUpdateKind);
    winrt::hstring RectToString(const winrt::Windows::Foundation::Rect& rect);
    winrt::hstring RectInt32ToString(const winrt::Windows::Graphics::RectInt32& rect);
    winrt::hstring SizeToString(const winrt::Windows::Foundation::Size& size);
    winrt::hstring Float2ToString(const winrt::Windows::Foundation::Numerics::float2& v2);
    winrt::hstring NullableFloatToString(const winrt::Windows::Foundation::IReference<float>& nf);
    winrt::hstring NullableFloat2ToString(const winrt::Windows::Foundation::IReference<winrt::Windows::Foundation::Numerics::float2>& nv2);
    winrt::hstring OrientationToString(const winrt::Windows::UI::Xaml::Controls::Orientation& orientation);
    winrt::hstring ScrollEventTypeToString(const winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType& scrollEventType);
    winrt::hstring ScrollingIndicatorModeToString(const winrt::Windows::UI::Xaml::Controls::Primitives::ScrollingIndicatorMode& indicatorMode);
    winrt::hstring FocusStateToString(const winrt::Windows::UI::Xaml::FocusState& focusState);
}

