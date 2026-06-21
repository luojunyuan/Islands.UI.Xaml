// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

class ResourceAccessor final
{
private:
    ResourceAccessor() = delete;

public:
    static winrt::hstring GetLocalizedStringResource(const wstring_view& resourceName);
    static winrt::LoadedImageSurface GetImageSurface(const wstring_view& assetName, winrt::Size imageSize);
    static winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> GetFileContents(const wstring_view& assetFileName);
    static winrt::IInspectable ResourceLookup(const winrt::Control& control, const winrt::IInspectable& key);

    static bool IsResourceIdNull(ResourceIdType resourceId)
    {
        return resourceId.empty();
    }
};
