// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.Resources.h>
#include <winrt/Windows.ApplicationModel.Resources.Core.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Devices.Input.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.Metadata.h>
#include <winrt/Windows.Foundation.Numerics.h>
#include <winrt/Windows.Graphics.h>
#include <winrt/Windows.Graphics.Display.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Composition.Interactions.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.Input.Inking.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Automation.Peers.h>
#include <winrt/Windows.UI.Xaml.Automation.Provider.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Documents.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Media.Animation.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>

#include <winrt/Islands.UI.Xaml.Controls.h>
//#include <winrt/Islands.UI.Xaml.Controls.Primitives.h>
//#include <winrt/Islands.UI.Xaml.Automation.Peers.h>

class ScrollPresenter;
class ScrollPresenterAutomationPeer;
class ScrollView;

namespace winrt::Islands::UI::Xaml::Controls::implementation
{
    using ScrollView = ::ScrollView;
}

namespace winrt::Islands::UI::Xaml::Controls::Primitives::implementation
{
    using ScrollPresenter = ::ScrollPresenter;
}

namespace winrt::Islands::UI::Xaml::Automation::Peers::implementation
{
    using ScrollPresenterAutomationPeer = ::ScrollPresenterAutomationPeer;
}

namespace winrt::Islands::UI::Xaml::Controls::factory_implementation {}
namespace winrt::Islands::UI::Xaml::Controls::Primitives::factory_implementation {}
namespace winrt::Islands::UI::Xaml::Automation::Peers::factory_implementation {}

namespace winrt
{
    namespace Controls = ::winrt::Windows::UI::Xaml::Controls;

    using namespace ::winrt::Windows::ApplicationModel::Resources;
    using namespace ::winrt::Windows::ApplicationModel::Resources::Core;
    using namespace ::winrt::Windows::ApplicationModel::Core;
    using namespace ::winrt::Windows::Devices::Input;
    using namespace ::winrt::Windows::Foundation;
    using namespace ::winrt::Windows::Foundation::Collections;
    using namespace ::winrt::Windows::Foundation::Metadata;
    using namespace ::winrt::Windows::Foundation::Numerics;
    using namespace ::winrt::Windows::Graphics;
    using namespace ::winrt::Windows::Graphics::Display;
    using namespace ::winrt::Windows::System;
    using namespace ::winrt::Windows::Storage::Streams;
    using namespace ::winrt::Windows::UI;
    using namespace ::winrt::Windows::UI::Composition;
    using namespace ::winrt::Windows::UI::Composition::Interactions;
    using namespace ::winrt::Windows::UI::Core;
    using namespace ::winrt::Windows::UI::Input;
    using namespace ::winrt::Windows::UI::Text;
    using namespace ::winrt::Windows::UI::ViewManagement;
    using namespace ::winrt::Windows::UI::Xaml;
    using namespace ::winrt::Windows::UI::Xaml::Automation;
    using namespace ::winrt::Windows::UI::Xaml::Automation::Peers;
    using namespace ::winrt::Windows::UI::Xaml::Automation::Provider;
    using namespace ::winrt::Windows::UI::Xaml::Controls;
    using namespace ::winrt::Windows::UI::Xaml::Controls::Primitives;
    using namespace ::winrt::Windows::UI::Xaml::Data;
    using namespace ::winrt::Windows::UI::Xaml::Documents;
    using namespace ::winrt::Windows::UI::Xaml::Hosting;
    using namespace ::winrt::Windows::UI::Xaml::Input;
    using namespace ::winrt::Windows::UI::Xaml::Interop;
    using namespace ::winrt::Windows::UI::Xaml::Markup;
    using namespace ::winrt::Windows::UI::Xaml::Media;
    using namespace ::winrt::Windows::UI::Xaml::Media::Animation;
    using namespace ::winrt::Windows::UI::Xaml::Media::Imaging;
    using namespace ::winrt::Windows::UI::Xaml::Shapes;

    using namespace ::winrt::Islands::UI::Xaml::Controls;
    using namespace ::winrt::Islands::UI::Xaml::Controls::Primitives;
    using namespace ::winrt::Islands::UI::Xaml::Automation::Peers;

    namespace implementation
    {
        using namespace ::winrt::Islands::UI::Xaml::Controls::implementation;
        using namespace ::winrt::Islands::UI::Xaml::Controls::Primitives::implementation;
        using namespace ::winrt::Islands::UI::Xaml::Automation::Peers::implementation;
    }

    namespace factory_implementation
    {
        using namespace ::winrt::Islands::UI::Xaml::Controls::factory_implementation;
        using namespace ::winrt::Islands::UI::Xaml::Controls::Primitives::factory_implementation;
        using namespace ::winrt::Islands::UI::Xaml::Automation::Peers::factory_implementation;
    }

    using FxZoomMode = ::winrt::Windows::UI::Xaml::Controls::ZoomMode;
    using FxScrollViewer = ::winrt::Windows::UI::Xaml::Controls::ScrollViewer;
}
