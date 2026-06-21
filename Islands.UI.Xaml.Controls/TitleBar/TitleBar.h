#pragma once

#include "TitleBar.g.h"

namespace winrt::Islands::UI::Xaml::Controls::implementation
{

struct TitleBar : TitleBarT<TitleBar>
{
    TitleBar();
    ~TitleBar();

    void OnApplyTemplate();
    winrt::xaml_peers::AutomationPeer OnCreateAutomationPeer();

    winrt::hstring Title();
    void Title(winrt::hstring const& value);
    winrt::hstring Subtitle();
    void Subtitle(winrt::hstring const& value);
    winrt::muxc::IconSource IconSource();
    void IconSource(winrt::muxc::IconSource const& value);
    winrt::xaml::UIElement LeftHeader();
    void LeftHeader(winrt::xaml::UIElement const& value);
    winrt::xaml::UIElement Content();
    void Content(winrt::xaml::UIElement const& value);
    winrt::xaml::UIElement RightHeader();
    void RightHeader(winrt::xaml::UIElement const& value);
    bool IsBackButtonVisible();
    void IsBackButtonVisible(bool value);
    bool IsBackButtonEnabled();
    void IsBackButtonEnabled(bool value);
    bool IsPaneToggleButtonVisible();
    void IsPaneToggleButtonVisible(bool value);
    winrt::Islands::UI::Xaml::Controls::TitleBarTemplateSettings TemplateSettings();
    bool AutoRefreshDragRegions();
    void AutoRefreshDragRegions(bool value);

    winrt::event_token BackRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::Islands::UI::Xaml::Controls::TitleBar, winrt::Windows::Foundation::IInspectable> const& handler);
    void BackRequested(winrt::event_token const& token);
    winrt::event_token PaneToggleRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::Islands::UI::Xaml::Controls::TitleBar, winrt::Windows::Foundation::IInspectable> const& handler);
    void PaneToggleRequested(winrt::event_token const& token);

    void RecomputeDragRegions();

    static winrt::xaml::DependencyProperty TitleProperty();
    static winrt::xaml::DependencyProperty SubtitleProperty();
    static winrt::xaml::DependencyProperty IconSourceProperty();
    static winrt::xaml::DependencyProperty LeftHeaderProperty();
    static winrt::xaml::DependencyProperty ContentProperty();
    static winrt::xaml::DependencyProperty RightHeaderProperty();
    static winrt::xaml::DependencyProperty IsBackButtonVisibleProperty();
    static winrt::xaml::DependencyProperty IsBackButtonEnabledProperty();
    static winrt::xaml::DependencyProperty IsPaneToggleButtonVisibleProperty();
    static winrt::xaml::DependencyProperty TemplateSettingsProperty();
    static winrt::xaml::DependencyProperty AutoRefreshDragRegionsProperty();
    static winrt::xaml::DependencyProperty IsDragRegionProperty();
    static winrt::Windows::Foundation::IReference<bool> GetIsDragRegion(winrt::xaml::UIElement const& element);
    static void SetIsDragRegion(winrt::xaml::UIElement const& element, winrt::Windows::Foundation::IReference<bool> const& value);

    void SetWindowActive(bool active);
    void SetCaptionInsets(double left, double right);
    int32_t HitTest(int32_t screenX, int32_t screenY, int32_t xamlRootScreenX, int32_t xamlRootScreenY);
    winrt::Windows::Foundation::Rect GetTitleBarRootBounds();
    std::vector<winrt::Windows::Foundation::Rect> GetPassthroughRects();
    std::vector<winrt::Windows::Foundation::Rect> GetIconRects();
    double RasterizationScale();

private:
    static void EnsureProperties();
    static void OnTitlePropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    static void OnSubtitlePropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    static void OnIconSourcePropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    static void OnLeftHeaderPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    static void OnContentPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    static void OnRightHeaderPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    static void OnIsBackButtonVisiblePropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    static void OnIsBackButtonEnabledPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    static void OnIsPaneToggleButtonVisiblePropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    static void OnAutoRefreshDragRegionsPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    static void OnIsDragRegionPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args);

    void OnPropertyChanged(winrt::xaml::DependencyPropertyChangedEventArgs const& args);
    void GoToState(std::wstring_view stateName, bool useTransitions);
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
    void UpdateInteractableElementsList();
    void UpdateLeftHeaderSpacing();
    void UpdateAutoRefreshDragRegions();
    void ApplyActivationStates();
    void FindInteractableElements(winrt::xaml::DependencyObject const& element, bool parentIsDragRegion);

    void OnBackButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::xaml::RoutedEventArgs const& args);
    void OnPaneToggleButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::xaml::RoutedEventArgs const& args);
    void OnSizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::xaml::SizeChangedEventArgs const& args);
    void OnFlowDirectionChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyProperty const& args);
    void OnContentLayoutUpdated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& args);

    void LoadBackButton();
    void LoadPaneToggleButton();

    template <typename T>
    T GetTemplateChildAs(std::wstring_view name)
    {
        if (auto child = GetTemplateChild(winrt::hstring{ name }))
        {
            return child.try_as<T>();
        }
        return nullptr;
    }

    winrt::Windows::Foundation::Rect GetElementBounds(winrt::xaml::FrameworkElement const& element);
    bool ContainsPoint(winrt::Windows::Foundation::Rect const& bounds, winrt::Windows::Foundation::Point const& point);

    static winrt::xaml_controls::IconElement MakeIconElementFrom(winrt::muxc::IconSource const& iconSource);
    static winrt::hstring GetLocalizedStringResource(std::wstring_view resourceName);

    static winrt::xaml::DependencyProperty s_titleProperty;
    static winrt::xaml::DependencyProperty s_subtitleProperty;
    static winrt::xaml::DependencyProperty s_iconSourceProperty;
    static winrt::xaml::DependencyProperty s_leftHeaderProperty;
    static winrt::xaml::DependencyProperty s_contentProperty;
    static winrt::xaml::DependencyProperty s_rightHeaderProperty;
    static winrt::xaml::DependencyProperty s_isBackButtonVisibleProperty;
    static winrt::xaml::DependencyProperty s_isBackButtonEnabledProperty;
    static winrt::xaml::DependencyProperty s_isPaneToggleButtonVisibleProperty;
    static winrt::xaml::DependencyProperty s_templateSettingsProperty;
    static winrt::xaml::DependencyProperty s_autoRefreshDragRegionsProperty;
    static winrt::xaml::DependencyProperty s_isDragRegionProperty;

    winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::Islands::UI::Xaml::Controls::TitleBar, winrt::Windows::Foundation::IInspectable>> m_backRequested;
    winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::Islands::UI::Xaml::Controls::TitleBar, winrt::Windows::Foundation::IInspectable>> m_paneToggleRequested;

    winrt::xaml::FrameworkElement::SizeChanged_revoker m_sizeChangedRevoker{};
    int64_t m_flowDirectionChangedToken{};
    winrt::xaml_controls::Button::Click_revoker m_backButtonClickRevoker{};
    winrt::xaml_controls::Button::Click_revoker m_paneToggleButtonClickRevoker{};
    winrt::xaml::FrameworkElement::LayoutUpdated_revoker m_contentLayoutUpdatedRevoker{};

    std::vector<winrt::xaml::FrameworkElement> m_interactableElements{};

    winrt::xaml::FrameworkElement m_layoutRoot{ nullptr };
    winrt::xaml_controls::ColumnDefinition m_leftPaddingColumn{ nullptr };
    winrt::xaml_controls::ColumnDefinition m_rightPaddingColumn{ nullptr };
    winrt::xaml_controls::Button m_backButton{ nullptr };
    winrt::xaml_controls::Button m_paneToggleButton{ nullptr };
    winrt::xaml::FrameworkElement m_iconViewbox{ nullptr };
    winrt::xaml::FrameworkElement m_leftHeaderArea{ nullptr };
    winrt::xaml_controls::Grid m_contentAreaGrid{ nullptr };
    winrt::xaml::FrameworkElement m_contentArea{ nullptr };
    winrt::xaml::FrameworkElement m_rightHeaderArea{ nullptr };

    double m_leftCaptionInset{};
    double m_rightCaptionInset{};
    double m_compactModeThresholdWidth{};
    bool m_isCompact{};
    bool m_isWindowActive{ true };

    static constexpr std::wstring_view s_layoutRootPartName{ L"PART_LayoutRoot"sv };
    static constexpr std::wstring_view s_leftPaddingColumnName{ L"LeftPaddingColumn"sv };
    static constexpr std::wstring_view s_rightPaddingColumnName{ L"RightPaddingColumn"sv };
    static constexpr std::wstring_view s_backButtonPartName{ L"PART_BackButton"sv };
    static constexpr std::wstring_view s_paneToggleButtonPartName{ L"PART_PaneToggleButton"sv };
    static constexpr std::wstring_view s_iconViewboxPartName{ L"PART_Icon"sv };
    static constexpr std::wstring_view s_leftHeaderPresenterPartName{ L"PART_LeftHeaderPresenter"sv };
    static constexpr std::wstring_view s_contentPresenterGridPartName{ L"PART_ContentPresenterGrid"sv };
    static constexpr std::wstring_view s_contentPresenterPartName{ L"PART_ContentPresenter"sv };
    static constexpr std::wstring_view s_rightHeaderPresenterPartName{ L"PART_RightHeaderPresenter"sv };
};

}

namespace winrt::Islands::UI::Xaml::Controls::factory_implementation
{

struct TitleBar : TitleBarT<TitleBar, implementation::TitleBar>
{
};

}
