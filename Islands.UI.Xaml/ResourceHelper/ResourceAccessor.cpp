// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

import std;
import inc.common;
import ixx.ResourceAccessor;

#define LOC_PREFIX L"Microsoft.UI.Xaml"
#define LOC_PREFIX_WINUI L"Microsoft.UI.Xaml"

PCWSTR ResourceAccessor::c_resourceLoc{ LOC_PREFIX L"/Resources" };
PCWSTR ResourceAccessor::c_assetLoc{ L"Files/" LOC_PREFIX L"/Assets"};
PCWSTR ResourceAccessor::c_resourceLocWinUI{ LOC_PREFIX_WINUI L"/Resources" };

winrt::Windows::ApplicationModel::Resources::Core::ResourceManager ResourceAccessor::m_resourceManagerWinRT{ nullptr };

winrt::Windows::ApplicationModel::Resources::Core::ResourceMap ResourceAccessor::GetAssetMap()
{
    return ResourceAccessor::GetResourceManager().MainResourceMap().GetSubtree(ResourceAccessor::c_assetLoc);
}

winrt::Windows::ApplicationModel::Resources::Core::ResourceMap ResourceAccessor::GetResourceMap()
{
    return ResourceAccessor::GetResourceManager().MainResourceMap().GetSubtree(ResourceAccessor::c_resourceLoc);
}

winrt::Windows::ApplicationModel::Resources::Core::ResourceManager ResourceAccessor::GetResourceManagerImpl()
{
    winrt::hstring frameworkInstallLocation;
    if (m_resourceManagerWinRT == nullptr)
    {
        // if (SharedHelpers::IsInFrameworkPackage(frameworkInstallLocation))
        // {
        //     ResourceAccessor::m_resourceManagerWinRT = winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager(frameworkInstallLocation + L"\\resources.pri");
        // }
        // else
        // {
        ResourceAccessor::m_resourceManagerWinRT = winrt::Windows::ApplicationModel::Resources::Core::ResourceManager::Current();
        // }
    }

    return m_resourceManagerWinRT;
}

winrt::Windows::ApplicationModel::Resources::Core::ResourceManager ResourceAccessor::GetResourceManager()
{
    auto static resourceManager = ResourceAccessor::GetResourceManagerImpl();
    return resourceManager;
}

winrt::Windows::ApplicationModel::Resources::Core::ResourceContext ResourceAccessor::GetResourceContext()
{
    //auto static m_resourceContextWinRT = ResourceAccessor::GetResourceManager().CreateResourceContext();
    auto static m_resourceContextWinRT = winrt::Windows::ApplicationModel::Resources::Core::ResourceContext::GetForViewIndependentUse();
    return m_resourceContextWinRT;
}


winrt::hstring ResourceAccessor::GetLocalizedStringResource(const wstring_view& resourceName)
{
    try
    {
        static auto mrt_lifted_resourceMap = GetResourceMap();
        static auto mrt_lifted_resourceContext = GetResourceContext();

        if (mrt_lifted_resourceMap)
        {
            if (const auto resourceCandidate = mrt_lifted_resourceMap.GetValue(resourceName, mrt_lifted_resourceContext))
            {
                return resourceCandidate.ValueAsString();
            }
        }
    }
    catch (...)
    {
    }

    return winrt::hstring{ resourceName };
}

winrt::LoadedImageSurface ResourceAccessor::GetImageSurface(const wstring_view& assetName, winrt::Size imageSize)
{
    auto imageUri = winrt::Uri{ std::wstring(L"ms-resource:///Files/Microsoft.UI.Xaml/Assets/") + std::wstring(assetName.data()) + std::wstring(L".png") };
    return winrt::LoadedImageSurface::StartLoadFromUri(imageUri, imageSize);
}

winrt::IAsyncOperation<winrt::hstring> ResourceAccessor::GetFileContents(const wstring_view& assetFileName)
{
    static auto mrt_lifted_assetMap = GetAssetMap();
    static auto mrt_lifted_resourceContext = GetResourceContext();
    auto filePath = mrt_lifted_assetMap.GetValue(assetFileName, mrt_lifted_resourceContext).ValueAsString();
    auto file = co_await winrt::StorageFile::GetFileFromPathAsync(filePath);
    auto fileBuffer = co_await winrt::FileIO::ReadBufferAsync(file);
    auto fileReader = winrt::DataReader::FromBuffer(fileBuffer);
    co_return fileReader.ReadString(fileReader.UnconsumedBufferLength());
}

winrt::IInspectable ResourceAccessor::ResourceLookup(const winrt::Control& control, const winrt::IInspectable& key)
{
    return control.Resources().HasKey(key) ? control.Resources().Lookup(key) : winrt::Application::Current().Resources().TryLookup(key);
}
