// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <cassert>

import std;
import winrt_base;
import winrt.Windows.Devices.Input;
import winrt.Windows.Foundation;
import winrt.Windows.Foundation.Numerics;
import winrt.Windows.Graphics;
import winrt.Windows.UI.Input;
import winrt.Windows.UI.Xaml;
import winrt.Windows.UI.Xaml.Controls;
import winrt.Windows.UI.Xaml.Controls.Primitives;
import winrt.Windows.UI.Xaml.Input;

#include "TypeLogging.h"
#include "Utils.h"

#ifndef MUX_ASSERT
#define MUX_ASSERT(condition) assert(condition)
#endif

namespace TypeLogging
{
#pragma region Common section

winrt::hstring PointerPointToString(const winrt::Windows::UI::Input::PointerPoint& pointerPoint, bool verbose)
{
    if (verbose)
    {
        return StringUtil::FormatString(L"PointerPoint: PointerId: %1!u!, Position: (%2!u!, %3!u!), IsInContact: %4!u!, PointerDeviceType: %5!u!",
            pointerPoint.PointerId(), static_cast<std::uint32_t>(pointerPoint.Position().X), static_cast<std::uint32_t>(pointerPoint.Position().Y),
            pointerPoint.IsInContact(), pointerPoint.PointerDevice().PointerDeviceType());
    }
    else
    {
        return StringUtil::FormatString(L"PointerPoint: PointerId: %1!u!, Position: (%2!u!, %3!u!)",
            pointerPoint.PointerId(), static_cast<std::uint32_t>(pointerPoint.Position().X), static_cast<std::uint32_t>(pointerPoint.Position().Y));
    }
}

winrt::hstring RectToString(const winrt::Windows::Foundation::Rect& rect)
{
    return StringUtil::FormatString(L"Rect: X: %1!i!, Y: %2!i!, W: %3!u!, H: %4!u!",
        static_cast<std::int32_t>(rect.X), static_cast<std::int32_t>(rect.Y), static_cast<std::uint32_t>(rect.Width), static_cast<std::uint32_t>(rect.Height));
}

winrt::hstring RectInt32ToString(const winrt::Windows::Graphics::RectInt32& rect)
{
    return StringUtil::FormatString(L"Rect: X: %1!i!, Y: %2!i!, W: %3!u!, H: %4!u!",
        static_cast<std::int32_t>(rect.X), static_cast<std::int32_t>(rect.Y), static_cast<std::uint32_t>(rect.Width), static_cast<std::uint32_t>(rect.Height));
}

winrt::hstring SizeToString(const winrt::Windows::Foundation::Size& size)
{
    return StringUtil::FormatString(L"Size: W: %1!u!, H: %2!u!",
        static_cast<std::uint32_t>(size.Width), static_cast<std::uint32_t>(size.Height));
}

winrt::hstring Float2ToString(const winrt::Windows::Foundation::Numerics::float2& v2)
{
    return StringUtil::FormatString(L"(%1!i!, %2!i!)", static_cast<std::int32_t>(v2.x), static_cast<std::int32_t>(v2.y));
}

winrt::hstring NullableFloatToString(const winrt::Windows::Foundation::IReference<float>& nf)
{
    if (nf)
    {
        return StringUtil::FormatString(L"%1!i!", static_cast<std::int32_t>(nf.Value()));
    }
    else
    {
        return L"null";
    }
}

winrt::hstring NullableFloat2ToString(const winrt::Windows::Foundation::IReference<winrt::Windows::Foundation::Numerics::float2>& nv2)
{
    if (nv2)
    {
        return Float2ToString(nv2.Value());
    }
    else
    {
        return L"null";
    }
}

winrt::hstring OrientationToString(const winrt::Windows::UI::Xaml::Controls::Orientation& orientation)
{
    return orientation == winrt::Windows::UI::Xaml::Controls::Orientation::Horizontal ? L"Horizontal" : L"Vertical";
}

winrt::hstring PointerDeviceTypeToString(const winrt::Windows::Devices::Input::PointerDeviceType& pointerDeviceKind)
{
    switch (pointerDeviceKind)
    {
    case winrt::Windows::Devices::Input::PointerDeviceType::Touch:
        return L"Touch";
    case winrt::Windows::Devices::Input::PointerDeviceType::Pen:
        return L"Pen";
    case winrt::Windows::Devices::Input::PointerDeviceType::Mouse:
        return L"Mouse";
    default:
        MUX_ASSERT(false);
        return L"";
    }
}

winrt::hstring PointerUpdateKindToString(const winrt::Windows::UI::Input::PointerUpdateKind& pointerUpdateKind)
{
    switch (pointerUpdateKind)
    {
    case winrt::Windows::UI::Input::PointerUpdateKind::LeftButtonPressed:
        return L"LeftButtonPressed";
    case winrt::Windows::UI::Input::PointerUpdateKind::LeftButtonReleased:
        return L"LeftButtonReleased";
    case winrt::Windows::UI::Input::PointerUpdateKind::MiddleButtonPressed:
        return L"MiddleButtonPressed";
    case winrt::Windows::UI::Input::PointerUpdateKind::MiddleButtonReleased:
        return L"MiddleButtonReleased";
    case winrt::Windows::UI::Input::PointerUpdateKind::Other:
        return L"Other";
    case winrt::Windows::UI::Input::PointerUpdateKind::RightButtonPressed:
        return L"RightButtonPressed";
    case winrt::Windows::UI::Input::PointerUpdateKind::RightButtonReleased:
        return L"RightButtonReleased";
    case winrt::Windows::UI::Input::PointerUpdateKind::XButton1Pressed:
        return L"XButton1Pressed";
    case winrt::Windows::UI::Input::PointerUpdateKind::XButton1Released:
        return L"XButton1Released";
    case winrt::Windows::UI::Input::PointerUpdateKind::XButton2Pressed:
        return L"XButton2Pressed";
    case winrt::Windows::UI::Input::PointerUpdateKind::XButton2Released:
        return L"XButton2Released";
    default:
        MUX_ASSERT(false);
        return L"";
    }
}

winrt::hstring ScrollEventTypeToString(const winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType& scrollEventType)
{
    switch (scrollEventType)
    {
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType::First:
        return L"First";
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType::Last:
        return L"Last";
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType::SmallDecrement:
        return L"SmallDecrement";
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType::SmallIncrement:
        return L"SmallIncrement";
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType::LargeDecrement:
        return L"LargeDecrement";
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType::LargeIncrement:
        return L"LargeIncrement";
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType::ThumbPosition:
        return L"ThumbPosition";
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType::ThumbTrack:
        return L"ThumbTrack";
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollEventType::EndScroll:
        return L"EndScroll";
    default:
        MUX_ASSERT(false);
        return L"";
    }
}

winrt::hstring ScrollingIndicatorModeToString(const winrt::Windows::UI::Xaml::Controls::Primitives::ScrollingIndicatorMode& indicatorMode)
{
    switch (indicatorMode)
    {
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollingIndicatorMode::None:
        return L"None";
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollingIndicatorMode::MouseIndicator:
        return L"MouseIndicator";
    case winrt::Windows::UI::Xaml::Controls::Primitives::ScrollingIndicatorMode::TouchIndicator:
        return L"TouchIndicator";
    default:
        MUX_ASSERT(false);
        return L"";
    }
}

winrt::hstring FocusStateToString(const winrt::Windows::UI::Xaml::FocusState& focusState)
{
    switch (focusState)
    {
    case winrt::Windows::UI::Xaml::FocusState::Keyboard:
        return L"Keyboard";
    case winrt::Windows::UI::Xaml::FocusState::Pointer:
        return L"Pointer";
    case winrt::Windows::UI::Xaml::FocusState::Programmatic:
        return L"Programmatic";
    case winrt::Windows::UI::Xaml::FocusState::Unfocused:
        return L"Unfocused";
    default:
        MUX_ASSERT(false);
        return L"";
    }
}

winrt::hstring KeyRoutedEventArgsToString(const winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs& eventArgs)
{
    return StringUtil::FormatString(L"KeyRoutedEventArgs: Handled: %1!u!, Key: %2!u!, OriginalKey: %3!u!",
        static_cast<std::uint32_t>(eventArgs.Handled()), static_cast<std::uint32_t>(eventArgs.Key()), static_cast<std::uint32_t>(eventArgs.OriginalKey()));
}

#pragma endregion

}
