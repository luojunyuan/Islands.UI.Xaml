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
#include "ResourceAccessor.ixx"

winrt::hstring ResourceAccessor::GetLocalizedStringResource(const wstring_view& resourceName)
{
    // This component intentionally avoids Windows App SDK MRT APIs. Keep a stable
    // fallback for callers that ask for optional automation/resource strings.
    return winrt::hstring{ resourceName };
}

winrt::LoadedImageSurface ResourceAccessor::GetImageSurface(const wstring_view& assetName, winrt::Size imageSize)
{
    const std::wstring assetUri = L"ms-appx:///Kumo.UI.Xaml.Controls/Assets/" + std::wstring{ assetName } + L".png";
    return winrt::LoadedImageSurface::StartLoadFromUri(winrt::Uri{ assetUri }, imageSize);
}

winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> ResourceAccessor::GetFileContents(const wstring_view&)
{
    co_return L"";
}

winrt::IInspectable ResourceAccessor::ResourceLookup(const winrt::Control& control, const winrt::IInspectable& key)
{
    if (control && control.Resources().HasKey(key))
    {
        return control.Resources().Lookup(key);
    }

    if (const auto app = winrt::Application::Current())
    {
        return app.Resources().TryLookup(key);
    }

    return nullptr;
}
