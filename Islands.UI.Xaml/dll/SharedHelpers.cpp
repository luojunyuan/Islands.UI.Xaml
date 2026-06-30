// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

module inc.common;

bool SharedHelpers::IsAnimationsEnabled()
{
    return winrt::UISettings().AnimationsEnabled();
}

bool SharedHelpers::DoRectsIntersect(const winrt::Rect& rect1, const winrt::Rect& rect2)
{
    return !(rect1.Width <= 0 || rect1.Height <= 0 || rect2.Width <= 0 || rect2.Height <= 0) &&
        rect2.X <= rect1.X + rect1.Width &&
        rect2.X + rect2.Width >= rect1.X &&
        rect2.Y <= rect1.Y + rect1.Height &&
        rect2.Y + rect2.Height >= rect1.Y;
}

bool SharedHelpers::IsAncestor(
    const winrt::DependencyObject& child,
    const winrt::DependencyObject& parent,
    bool checkVisibility)
{
    if (!child || !parent || child == parent)
    {
        return false;
    }

    auto isCollapsed = [](const winrt::DependencyObject& object)
    {
        if (const auto element = object.try_as<winrt::IUIElement>())
        {
            return element.Visibility() == winrt::Visibility::Collapsed;
        }

        return false;
    };

    if (checkVisibility && (isCollapsed(parent) || isCollapsed(child)))
    {
        return false;
    }

    winrt::DependencyObject current = winrt::VisualTreeHelper::GetParent(child);
    while (current)
    {
        if (checkVisibility && isCollapsed(current))
        {
            return false;
        }

        if (current == parent)
        {
            return true;
        }

        current = winrt::VisualTreeHelper::GetParent(current);
    }

    return false;
}

winrt::IconElement SharedHelpers::MakeIconElementFrom(winrt::IconSource const& iconSource)
{
    if (!iconSource)
    {
        return nullptr;
    }

    if (auto fontIconSource = iconSource.try_as<winrt::Microsoft::UI::Xaml::Controls::FontIconSource>())
    {
        auto icon = winrt::FontIcon();
        icon.Glyph(fontIconSource.Glyph());
        icon.FontSize(fontIconSource.FontSize());
        icon.FontWeight(fontIconSource.FontWeight());
        icon.FontStyle(fontIconSource.FontStyle());
        icon.IsTextScaleFactorEnabled(fontIconSource.IsTextScaleFactorEnabled());
        icon.MirroredWhenRightToLeft(fontIconSource.MirroredWhenRightToLeft());

        if (fontIconSource.FontFamily())
        {
            icon.FontFamily(fontIconSource.FontFamily());
        }
        if (fontIconSource.Foreground())
        {
            icon.Foreground(fontIconSource.Foreground());
        }

        return icon;
    }

    if (auto symbolIconSource = iconSource.try_as<winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource>())
    {
        auto icon = winrt::SymbolIcon();
        icon.Symbol(static_cast<winrt::Symbol>(static_cast<int32_t>(symbolIconSource.Symbol())));
        if (symbolIconSource.Foreground())
        {
            icon.Foreground(symbolIconSource.Foreground());
        }
        return icon;
    }

    if (auto bitmapIconSource = iconSource.try_as<winrt::Microsoft::UI::Xaml::Controls::BitmapIconSource>())
    {
        auto icon = winrt::BitmapIcon();
        if (bitmapIconSource.UriSource())
        {
            icon.UriSource(bitmapIconSource.UriSource());
        }
        icon.ShowAsMonochrome(bitmapIconSource.ShowAsMonochrome());
        if (bitmapIconSource.Foreground())
        {
            icon.Foreground(bitmapIconSource.Foreground());
        }
        return icon;
    }

    if (auto pathIconSource = iconSource.try_as<winrt::Microsoft::UI::Xaml::Controls::PathIconSource>())
    {
        auto icon = winrt::PathIcon();
        if (pathIconSource.Data())
        {
            icon.Data(pathIconSource.Data());
        }
        if (pathIconSource.Foreground())
        {
            icon.Foreground(pathIconSource.Foreground());
        }
        return icon;
    }

    return nullptr;
}
