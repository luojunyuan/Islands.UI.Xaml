// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "CppBaseIncludes.h"

import CppWinRTModules;

#include "ResourceAccessor.h"

winrt::hstring ResourceAccessor::GetLocalizedStringResource(const std::wstring_view& resourceName)
{
    // This component intentionally avoids Windows App SDK MRT APIs. Keep a stable
    // fallback for callers that ask for optional automation/resource strings.
    return winrt::hstring{ resourceName };
}

winrt::Windows::UI::Xaml::Media::LoadedImageSurface ResourceAccessor::GetImageSurface(
    const std::wstring_view& assetName,
    winrt::Windows::Foundation::Size imageSize)
{
    const std::wstring assetUri = L"ms-appx:///Islands.UI.Xaml.Controls/Assets/" + std::wstring{ assetName } + L".png";
    return winrt::Windows::UI::Xaml::Media::LoadedImageSurface::StartLoadFromUri(winrt::Windows::Foundation::Uri{ assetUri }, imageSize);
}

winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> ResourceAccessor::GetFileContents(const std::wstring_view&)
{
    co_return L"";
}

winrt::Windows::Foundation::IInspectable ResourceAccessor::ResourceLookup(
    const winrt::Windows::UI::Xaml::Controls::Control& control,
    const winrt::Windows::Foundation::IInspectable& key)
{
    if (control && control.Resources().HasKey(key))
    {
        return control.Resources().Lookup(key);
    }

    if (const auto app = winrt::Windows::UI::Xaml::Application::Current())
    {
        return app.Resources().TryLookup(key);
    }

    return nullptr;
}
