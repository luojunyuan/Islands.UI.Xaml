module;

#include <cassert>

export module CppWinRTModules;

export import winrt_base;
export import winrt.Windows.Foundation;
export import winrt.Windows.Foundation.Numerics;
export import winrt.Windows.Graphics;
export import winrt.Windows.Devices.Input;
export import winrt.Windows.UI.Input;
export import winrt.Windows.UI.Xaml;
export import winrt.Windows.UI.Xaml.Controls;
export import winrt.Windows.UI.Xaml.Controls.Primitives;
export import winrt.Windows.UI.Xaml.Input;
export import winrt.Microsoft.UI.Xaml.Controls;
export import winrt.Microsoft.UI.Xaml.Controls.AnimatedVisuals;
export import winrt.Islands.UI.Xaml.Controls;
export import winrt.Islands.UI.Xaml.Controls.Primitives;
export import winrt.Islands.UI.Xaml.Automation.Peers;

export namespace winrt::Islands::UI::Xaml::Controls
{
    namespace implementation {}
    namespace factory_implementation {}
}

export namespace winrt::Islands::UI::Xaml::Controls::Primitives
{
    namespace implementation {}
    namespace factory_implementation {}
}

export namespace winrt::Islands::UI::Xaml::Automation::Peers
{
    namespace implementation {}
    namespace factory_implementation {}
}

export namespace winrt
{
    namespace implementation = ::winrt::Islands::UI::Xaml::Controls::implementation;
    namespace factory_implementation = ::winrt::Islands::UI::Xaml::Controls::factory_implementation;

    using namespace ::winrt::Windows::Devices::Input;
    using namespace ::winrt::Windows::Foundation;
    using namespace ::winrt::Windows::Foundation::Numerics;
    using namespace ::winrt::Windows::Graphics;
    using namespace ::winrt::Windows::UI::Input;
    using namespace ::winrt::Windows::UI::Xaml;
    using namespace ::winrt::Windows::UI::Xaml::Controls;
    using namespace ::winrt::Windows::UI::Xaml::Controls::Primitives;
    using namespace ::winrt::Windows::UI::Xaml::Input;
    using IconSource = ::winrt::Microsoft::UI::Xaml::Controls::IconSource;
    using AppWindowTitleBar = ::winrt::Islands::UI::Xaml::Controls::AppWindowTitleBar;
    using InputNonClientPointerSource = ::winrt::Islands::UI::Xaml::Controls::InputNonClientPointerSource;
    using MUXControlsTestHooks = ::winrt::Islands::UI::Xaml::Controls::MUXControlsTestHooks;
    using MUXControlsTestHooksLoggingMessageEventArgs = ::winrt::Islands::UI::Xaml::Controls::MUXControlsTestHooksLoggingMessageEventArgs;
    using NonClientRegionKind = ::winrt::Islands::UI::Xaml::Controls::NonClientRegionKind;
    using TitleBar = ::winrt::Islands::UI::Xaml::Controls::TitleBar;
    using TitleBarAutomationPeer = ::winrt::Islands::UI::Xaml::Controls::TitleBarAutomationPeer;
    using TitleBarTemplateSettings = ::winrt::Islands::UI::Xaml::Controls::TitleBarTemplateSettings;
    using TitleBarWindowAdapter = ::winrt::Islands::UI::Xaml::Controls::TitleBarWindowAdapter;
    using IScrollView = ::winrt::Islands::UI::Xaml::Controls::IScrollView;
    using ScrollPresenterAutomationPeer = ::winrt::Islands::UI::Xaml::Automation::Peers::ScrollPresenterAutomationPeer;
    using ScrollView = ::winrt::Islands::UI::Xaml::Controls::ScrollView;
    using ScrollViewTestHooks = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollViewTestHooks;
    using ScrollPresenter = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollPresenter;
    using ScrollPresenterTestHooks = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollPresenterTestHooks;
    using ScrollControllerAddScrollVelocityRequestedEventArgs = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollControllerAddScrollVelocityRequestedEventArgs;
    using ScrollControllerPanRequestedEventArgs = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollControllerPanRequestedEventArgs;
    using ScrollControllerScrollByRequestedEventArgs = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollControllerScrollByRequestedEventArgs;
    using ScrollControllerScrollToRequestedEventArgs = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollControllerScrollToRequestedEventArgs;
    using IScrollController = ::winrt::Islands::UI::Xaml::Controls::Primitives::IScrollController;
    using IScrollControllerPanningInfo = ::winrt::Islands::UI::Xaml::Controls::Primitives::IScrollControllerPanningInfo;
    using RepeatedScrollSnapPoint = ::winrt::Islands::UI::Xaml::Controls::Primitives::RepeatedScrollSnapPoint;
    using RepeatedZoomSnapPoint = ::winrt::Islands::UI::Xaml::Controls::Primitives::RepeatedZoomSnapPoint;
    using ScrollSnapPoint = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollSnapPoint;
    using ScrollSnapPointBase = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollSnapPointBase;
    using ScrollSnapPointsAlignment = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollSnapPointsAlignment;
    using SnapPointBase = ::winrt::Islands::UI::Xaml::Controls::Primitives::SnapPointBase;
    using ZoomSnapPoint = ::winrt::Islands::UI::Xaml::Controls::Primitives::ZoomSnapPoint;
    using ZoomSnapPointBase = ::winrt::Islands::UI::Xaml::Controls::Primitives::ZoomSnapPointBase;
    using ScrollingAnimationMode = ::winrt::Islands::UI::Xaml::Controls::ScrollingAnimationMode;
    using ScrollingChainMode = ::winrt::Islands::UI::Xaml::Controls::ScrollingChainMode;
    using ScrollingContentOrientation = ::winrt::Islands::UI::Xaml::Controls::ScrollingContentOrientation;
    using ScrollingInputKinds = ::winrt::Islands::UI::Xaml::Controls::ScrollingInputKinds;
    using ScrollingInteractionState = ::winrt::Islands::UI::Xaml::Controls::ScrollingInteractionState;
    using ScrollingRailMode = ::winrt::Islands::UI::Xaml::Controls::ScrollingRailMode;
    using ScrollingScrollBarVisibility = ::winrt::Islands::UI::Xaml::Controls::ScrollingScrollBarVisibility;
    using ScrollingScrollMode = ::winrt::Islands::UI::Xaml::Controls::ScrollingScrollMode;
    using ScrollingScrollOptions = ::winrt::Islands::UI::Xaml::Controls::ScrollingScrollOptions;
    using ScrollingSnapPointsMode = ::winrt::Islands::UI::Xaml::Controls::ScrollingSnapPointsMode;
    using ScrollingZoomMode = ::winrt::Islands::UI::Xaml::Controls::ScrollingZoomMode;
    using ScrollingZoomOptions = ::winrt::Islands::UI::Xaml::Controls::ScrollingZoomOptions;
}

export template <typename T>
inline void MUX_ASSERT(T const& condition)
{
    assert(static_cast<bool>(condition));
}
