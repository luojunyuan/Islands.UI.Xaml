// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

class ResourceAccessor final
{
private:
    ResourceAccessor() = delete;

public:
    static winrt::hstring GetLocalizedStringResource(const std::wstring_view& resourceName);
    static winrt::Windows::UI::Xaml::Media::LoadedImageSurface GetImageSurface(const std::wstring_view& assetName, winrt::Windows::Foundation::Size imageSize);
    static winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> GetFileContents(const std::wstring_view& assetFileName);
    static winrt::Windows::Foundation::IInspectable ResourceLookup(
        const winrt::Windows::UI::Xaml::Controls::Control& control,
        const winrt::Windows::Foundation::IInspectable& key);

    static bool IsResourceIdNull(const winrt::hstring& resourceId)
    {
        return resourceId.empty();
    }
};
