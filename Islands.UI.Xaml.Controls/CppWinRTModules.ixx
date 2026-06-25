module;

#include <SDKDDKVer.h>
#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>
#include <unknwn.h>
#include <inspectable.h>
#include <restrictederrorinfo.h>
#include <hstring.h>
#include <windows.ui.xaml.hosting.referencetracker.h>

export module CppWinRTModules;

export import winrt_base;
export import winrt.Windows.ApplicationModel.Resources;
export import winrt.Windows.ApplicationModel.Resources.Core;
export import winrt.Windows.ApplicationModel.Core;
export import winrt.Windows.Devices.Input;
export import winrt.Windows.Foundation;
export import winrt.Windows.Foundation.Collections;
export import winrt.Windows.Foundation.Metadata;
export import winrt.Windows.Foundation.Numerics;
export import winrt.Windows.Graphics;
export import winrt.Windows.Graphics.Display;
export import winrt.Windows.System;
export import winrt.Windows.Storage.Streams;
export import winrt.Windows.UI;
export import winrt.Windows.UI.Composition;
export import winrt.Windows.UI.Composition.Interactions;
export import winrt.Windows.UI.Core;
export import winrt.Windows.UI.Input;
export import winrt.Windows.UI.Input.Inking;
export import winrt.Windows.UI.Text;
export import winrt.Windows.UI.ViewManagement;
export import winrt.Windows.UI.Xaml;
export import winrt.Windows.UI.Xaml.Automation;
export import winrt.Windows.UI.Xaml.Automation.Peers;
export import winrt.Windows.UI.Xaml.Automation.Provider;
export import winrt.Windows.UI.Xaml.Controls;
export import winrt.Windows.UI.Xaml.Controls.Primitives;
export import winrt.Windows.UI.Xaml.Data;
export import winrt.Windows.UI.Xaml.Documents;
export import winrt.Windows.UI.Xaml.Hosting;
export import winrt.Windows.UI.Xaml.Input;
export import winrt.Windows.UI.Xaml.Interop;
export import winrt.Windows.UI.Xaml.Markup;
export import winrt.Windows.UI.Xaml.Media;
export import winrt.Windows.UI.Xaml.Media.Animation;
export import winrt.Windows.UI.Xaml.Media.Imaging;
export import winrt.Windows.UI.Xaml.Shapes;
export import winrt.Microsoft.UI.Xaml.Controls.AnimatedVisuals;
export import winrt.Microsoft.UI.Xaml.Controls;
export import winrt.Microsoft.UI.Xaml.XamlTypeInfo;
export import winrt.Islands.UI.Xaml.Controls;

export class ScrollPresenter;
export class ScrollPresenterAutomationPeer;
export class ScrollView;

export namespace winrt::Islands::UI::Xaml::Controls::implementation
{
    using ScrollView = ::ScrollView;
}

export namespace winrt::Islands::UI::Xaml::Controls::Primitives::implementation
{
    using ScrollPresenter = ::ScrollPresenter;
}

export namespace winrt::Islands::UI::Xaml::Automation::Peers::implementation
{
    using ScrollPresenterAutomationPeer = ::ScrollPresenterAutomationPeer;
}

export namespace winrt::Islands::UI::Xaml::Controls::factory_implementation {}
export namespace winrt::Islands::UI::Xaml::Controls::Primitives::factory_implementation {}
export namespace winrt::Islands::UI::Xaml::Automation::Peers::factory_implementation {}

export namespace winrt
{
    namespace xaml = Windows::UI::Xaml;
    namespace xaml_automation = Windows::UI::Xaml::Automation;
    namespace xaml_peers = Windows::UI::Xaml::Automation::Peers;
    namespace xaml_controls = Windows::UI::Xaml::Controls;
    namespace xaml_primitives = Windows::UI::Xaml::Controls::Primitives;
    namespace xaml_interop = Windows::UI::Xaml::Interop;
    namespace xaml_markup = Windows::UI::Xaml::Markup;
    namespace xaml_media = Windows::UI::Xaml::Media;
    namespace muxc = Microsoft::UI::Xaml::Controls;
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
