module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "TitleBar.g.h"

export module ixx.TitleBar;

import std;
import inc.common;
import winrt.Windows.System;
import ixx.TitleBar.properties;
import ixx.TitleBarWindowAdapter;

export
{
class TitleBar :
    public ReferenceTracker<TitleBar, winrt::implementation::TitleBarT>,
    public TitleBarProperties
{

public:
    TitleBar();
    virtual ~TitleBar();

    // IFrameworkElement
    void OnApplyTemplate();

    // UIElement
    winrt::AutomationPeer OnCreateAutomationPeer();

    void OnPropertyChanged(winrt::DependencyPropertyChangedEventArgs const& args);

    // Public API for manual drag region refresh
    void RecomputeDragRegions();
    void SetWindowActive(bool active);
    void SetCaptionInsets(double left, double right);
    int32_t HitTest(int32_t screenX, int32_t screenY, int32_t xamlRootScreenX, int32_t xamlRootScreenY);
    winrt::Rect GetTitleBarRootBounds();
    std::vector<winrt::Rect> GetPassthroughRects();
    std::vector<winrt::Rect> GetIconRects();
    double RasterizationScale();
    void RegisterWindowAdapter(TitleBarWindowAdapter* adapter);
    void UnregisterWindowAdapter(TitleBarWindowAdapter* adapter);

    // Static callback for IsDragRegion attached property changes
    static void OnIsDragRegionPropertyChanged(
        winrt::DependencyObject const& sender,
        winrt::DependencyPropertyChangedEventArgs const& args);

private:
    void GoToState(std::wstring_view const& stateName, bool useTransitions);
    void UpdatePadding();
    void UpdateIcon();
    void UpdateBackButton();
    void UpdatePaneToggleButton();
    void UpdateHeight();
    void UpdateTitle();
    void UpdateSubtitle();
    void UpdateLeftHeader();
    void UpdateContent();
    void UpdateRightHeader();
    void UpdateDragRegion();
    void UpdateIconRegion();
    void UpdateInteractableElementsList();
    void UpdateLeftHeaderSpacing();
    void UpdateAutoRefreshDragRegions();

    void OnBackButtonClick(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& args);
    void OnPaneToggleButtonClick(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& args);
    void OnSizeChanged(const winrt::IInspectable& sender, const winrt::SizeChangedEventArgs& args);
    void OnFlowDirectionChanged(const winrt::DependencyObject& sender, const winrt::DependencyProperty& args);
    void OnIconLayoutUpdated(const winrt::IInspectable& sender, const winrt::IInspectable& args);
    void OnContentLayoutUpdated(const winrt::IInspectable& sender, const winrt::IInspectable& args);
    void FindInteractableElements(const winrt::DependencyObject& element, bool parentIsDragRegion);

    void LoadBackButton();
    void LoadPaneToggleButton();

    void ApplyActivationStates();
    winrt::Rect GetElementBounds(winrt::FrameworkElement const& element);
    static bool ContainsPoint(winrt::Rect const& bounds, winrt::Point const& point);
    static double ValidLength(double value);
    static double MaxLength(double first, double second);
    static bool IsElementOrDescendantOf(winrt::DependencyObject const& candidate, winrt::DependencyObject const& ancestor);

    winrt::Button::Click_revoker m_backButtonClickRevoker{};
    winrt::Button::Click_revoker m_paneToggleButtonClickRevoker{};
    winrt::FrameworkElement::SizeChanged_revoker m_sizeChangedRevoker;
    winrt::FrameworkElement::LayoutUpdated_revoker m_iconLayoutUpdatedRevoker{};
    winrt::FrameworkElement::LayoutUpdated_revoker m_contentLayoutUpdatedRevoker{};
    int64_t m_flowDirectionChangedToken{};

    std::list<winrt::FrameworkElement> m_interactableElementsList{};

    tracker_ref<winrt::ColumnDefinition> m_leftPaddingColumn{ this };
    tracker_ref<winrt::ColumnDefinition> m_rightPaddingColumn{ this };
    tracker_ref<winrt::Button> m_backButton{ this };
    tracker_ref<winrt::Button> m_paneToggleButton{ this };
    tracker_ref<winrt::FrameworkElement> m_iconViewbox{ this };
    tracker_ref<winrt::Grid> m_contentAreaGrid{ this };
    tracker_ref<winrt::FrameworkElement> m_leftHeaderArea{ this };
    tracker_ref<winrt::FrameworkElement> m_contentArea{ this };
    tracker_ref<winrt::FrameworkElement> m_rightHeaderArea{ this };

    double m_leftCaptionInset{ 0.0 };
    double m_rightCaptionInset{ 0.0 };
    double m_compactModeThresholdWidth{ 0.0 };
    bool m_isCompact{ false };
    bool m_isWindowActive{ true };
    TitleBarWindowAdapter* m_windowAdapter{};

    static constexpr std::wstring_view s_leftPaddingColumnName{ L"LeftPaddingColumn"sv };
    static constexpr std::wstring_view s_rightPaddingColumnName{ L"RightPaddingColumn"sv };
    static constexpr std::wstring_view s_layoutRootPartName{ L"PART_LayoutRoot"sv };
    static constexpr std::wstring_view s_backButtonPartName{ L"PART_BackButton"sv };
    static constexpr std::wstring_view s_paneToggleButtonPartName{ L"PART_PaneToggleButton"sv };
    static constexpr std::wstring_view s_iconViewboxPartName{ L"PART_Icon"sv };
    static constexpr std::wstring_view s_leftHeaderPresenterPartName{ L"PART_LeftHeaderPresenter"sv };
    static constexpr std::wstring_view s_contentPresenterGridPartName{ L"PART_ContentPresenterGrid"sv };
    static constexpr std::wstring_view s_contentPresenterPartName{ L"PART_ContentPresenter"sv };
    static constexpr std::wstring_view s_rightHeaderPresenterPartName{ L"PART_RightHeaderPresenter"sv };

    static constexpr std::wstring_view s_compactVisualStateName{ L"Compact"sv };
    static constexpr std::wstring_view s_expandedVisualStateName{ L"Expanded"sv };
    static constexpr std::wstring_view s_compactHeightVisualStateName{ L"CompactHeight"sv };
    static constexpr std::wstring_view s_expandedHeightVisualStateName{ L"ExpandedHeight"sv };
    static constexpr std::wstring_view s_defaultSpacingVisualStateName{ L"DefaultSpacing"sv };
    static constexpr std::wstring_view s_negativeInsetVisualStateName{ L"NegativeInsetSpacing"sv };
    static constexpr std::wstring_view s_iconVisibleVisualStateName{ L"IconVisible"sv };
    static constexpr std::wstring_view s_iconCollapsedVisualStateName{ L"IconCollapsed"sv };
    static constexpr std::wstring_view s_iconDeactivatedVisualStateName{ L"IconDeactivated"sv };
    static constexpr std::wstring_view s_backButtonVisibleVisualStateName{ L"BackButtonVisible"sv };
    static constexpr std::wstring_view s_backButtonCollapsedVisualStateName{ L"BackButtonCollapsed"sv };
    static constexpr std::wstring_view s_backButtonDeactivatedVisualStateName{ L"BackButtonDeactivated"sv };
    static constexpr std::wstring_view s_paneToggleButtonVisibleVisualStateName{ L"PaneToggleButtonVisible"sv };
    static constexpr std::wstring_view s_paneToggleButtonCollapsedVisualStateName{ L"PaneToggleButtonCollapsed"sv };
    static constexpr std::wstring_view s_paneToggleButtonDeactivatedVisualStateName{ L"PaneToggleButtonDeactivated"sv };
    static constexpr std::wstring_view s_titleTextVisibleVisualStateName{ L"TitleTextVisible"sv };
    static constexpr std::wstring_view s_titleTextCollapsedVisualStateName{ L"TitleTextCollapsed"sv };
    static constexpr std::wstring_view s_titleTextDeactivatedVisualStateName{ L"TitleTextDeactivated"sv };
    static constexpr std::wstring_view s_subtitleTextVisibleVisualStateName{ L"SubtitleTextVisible"sv };
    static constexpr std::wstring_view s_subtitleTextCollapsedVisualStateName{ L"SubtitleTextCollapsed"sv };
    static constexpr std::wstring_view s_subtitleTextDeactivatedVisualStateName{ L"SubtitleTextDeactivated"sv };
    static constexpr std::wstring_view s_leftHeaderVisibleVisualStateName{ L"LeftHeaderVisible"sv };
    static constexpr std::wstring_view s_leftHeaderCollapsedVisualStateName{ L"LeftHeaderCollapsed"sv };
    static constexpr std::wstring_view s_leftHeaderDeactivatedVisualStateName{ L"LeftHeaderDeactivated"sv };
    static constexpr std::wstring_view s_contentVisibleVisualStateName{ L"ContentVisible"sv };
    static constexpr std::wstring_view s_contentCollapsedVisualStateName{ L"ContentCollapsed"sv };
    static constexpr std::wstring_view s_contentDeactivatedVisualStateName{ L"ContentDeactivated"sv };
    static constexpr std::wstring_view s_rightHeaderVisibleVisualStateName{ L"RightHeaderVisible"sv };
    static constexpr std::wstring_view s_rightHeaderCollapsedVisualStateName{ L"RightHeaderCollapsed"sv };
    static constexpr std::wstring_view s_rightHeaderDeactivatedVisualStateName{ L"RightHeaderDeactivated"sv };
};

namespace winrt::Islands::UI::Xaml::Controls::implementation
{
    using TitleBar = ::TitleBar;
}

}
