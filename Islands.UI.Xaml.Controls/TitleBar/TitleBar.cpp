#include "pch.h"

#include "CppBaseIncludes.h"

import CppWinRTModules;
#include "TitleBar.h"
#include "TitleBarAutomationPeer.h"
#include "TitleBarTemplateSettings.h"
#include "TitleBarTrace.h"
#if __has_include("TitleBar.g.cpp")
#include "TitleBar.g.cpp"
#endif

bool TitleBarTrace::s_IsDebugOutputEnabled{ false };
bool TitleBarTrace::s_IsVerboseDebugOutputEnabled{ false };

namespace winrt::Islands::UI::Xaml::Controls::implementation
{

winrt::xaml::DependencyProperty TitleBar::s_titleProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_subtitleProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_iconSourceProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_leftHeaderProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_contentProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_rightHeaderProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_isBackButtonVisibleProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_isBackButtonEnabledProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_isPaneToggleButtonVisibleProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_templateSettingsProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_autoRefreshDragRegionsProperty{ nullptr };
winrt::xaml::DependencyProperty TitleBar::s_isDragRegionProperty{ nullptr };

namespace
{
    template <typename T>
    winrt::Windows::Foundation::IInspectable Box(T const& value)
    {
        return winrt::box_value(value);
    }

    winrt::xaml::PropertyMetadata Metadata(winrt::Windows::Foundation::IInspectable const& defaultValue, winrt::xaml::PropertyChangedCallback const& callback = nullptr)
    {
        return callback ? winrt::xaml::PropertyMetadata{ defaultValue, callback } : winrt::xaml::PropertyMetadata{ defaultValue };
    }

    double ValidLength(double value)
    {
        return std::isfinite(value) && value > 0.0 ? value : 0.0;
    }

    double MaxLength(double first, double second)
    {
        return std::max(ValidLength(first), ValidLength(second));
    }

    bool IsElementOrDescendantOf(winrt::xaml::DependencyObject const& candidate, winrt::xaml::DependencyObject const& ancestor)
    {
        for (auto current = candidate; current; current = winrt::xaml_media::VisualTreeHelper::GetParent(current))
        {
            if (current == ancestor)
            {
                return true;
            }
        }

        return false;
    }
}

TitleBar::TitleBar()
{
    EnsureProperties();

    SetValue(TemplateSettingsProperty(), winrt::make<TitleBarTemplateSettings>());
    DefaultStyleKey(Box(winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>()));
    if (const auto control5 = this->try_as<winrt::IControl5>())
    {
        control5.DefaultStyleResourceUri(winrt::Uri{ L"ms-appx:///Islands.UI.Xaml.Controls/Themes/generic.xaml" });
    }

    m_sizeChangedRevoker = SizeChanged(winrt::auto_revoke, { this, &TitleBar::OnSizeChanged });
    m_flowDirectionChangedToken = RegisterPropertyChangedCallback(
        winrt::xaml::FrameworkElement::FlowDirectionProperty(),
        { this, &TitleBar::OnFlowDirectionChanged });
}

TitleBar::~TitleBar()
{
    m_sizeChangedRevoker.revoke();
    m_backButtonClickRevoker.revoke();
    m_paneToggleButtonClickRevoker.revoke();
    m_contentLayoutUpdatedRevoker.revoke();

    if (m_flowDirectionChangedToken)
    {
        UnregisterPropertyChangedCallback(winrt::xaml::FrameworkElement::FlowDirectionProperty(), m_flowDirectionChangedToken);
    }
}

void TitleBar::EnsureProperties()
{
    if (!s_titleProperty)
    {
        s_titleProperty = winrt::xaml::DependencyProperty::Register(
            L"Title",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(Box(winrt::hstring{}), { &TitleBar::OnTitlePropertyChanged }));
    }

    if (!s_subtitleProperty)
    {
        s_subtitleProperty = winrt::xaml::DependencyProperty::Register(
            L"Subtitle",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(Box(winrt::hstring{}), { &TitleBar::OnSubtitlePropertyChanged }));
    }

    if (!s_iconSourceProperty)
    {
        s_iconSourceProperty = winrt::xaml::DependencyProperty::Register(
            L"IconSource",
            winrt::xaml_typename<winrt::muxc::IconSource>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(nullptr, { &TitleBar::OnIconSourcePropertyChanged }));
    }

    if (!s_leftHeaderProperty)
    {
        s_leftHeaderProperty = winrt::xaml::DependencyProperty::Register(
            L"LeftHeader",
            winrt::xaml_typename<winrt::xaml::UIElement>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(nullptr, { &TitleBar::OnLeftHeaderPropertyChanged }));
    }

    if (!s_contentProperty)
    {
        s_contentProperty = winrt::xaml::DependencyProperty::Register(
            L"Content",
            winrt::xaml_typename<winrt::xaml::UIElement>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(nullptr, { &TitleBar::OnContentPropertyChanged }));
    }

    if (!s_rightHeaderProperty)
    {
        s_rightHeaderProperty = winrt::xaml::DependencyProperty::Register(
            L"RightHeader",
            winrt::xaml_typename<winrt::xaml::UIElement>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(nullptr, { &TitleBar::OnRightHeaderPropertyChanged }));
    }

    if (!s_isBackButtonVisibleProperty)
    {
        s_isBackButtonVisibleProperty = winrt::xaml::DependencyProperty::Register(
            L"IsBackButtonVisible",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(Box(false), { &TitleBar::OnIsBackButtonVisiblePropertyChanged }));
    }

    if (!s_isBackButtonEnabledProperty)
    {
        s_isBackButtonEnabledProperty = winrt::xaml::DependencyProperty::Register(
            L"IsBackButtonEnabled",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(Box(true), { &TitleBar::OnIsBackButtonEnabledPropertyChanged }));
    }

    if (!s_isPaneToggleButtonVisibleProperty)
    {
        s_isPaneToggleButtonVisibleProperty = winrt::xaml::DependencyProperty::Register(
            L"IsPaneToggleButtonVisible",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(Box(false), { &TitleBar::OnIsPaneToggleButtonVisiblePropertyChanged }));
    }

    if (!s_templateSettingsProperty)
    {
        s_templateSettingsProperty = winrt::xaml::DependencyProperty::Register(
            L"TemplateSettings",
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBarTemplateSettings>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(nullptr));
    }

    if (!s_autoRefreshDragRegionsProperty)
    {
        s_autoRefreshDragRegionsProperty = winrt::xaml::DependencyProperty::Register(
            L"AutoRefreshDragRegions",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(Box(false), { &TitleBar::OnAutoRefreshDragRegionsPropertyChanged }));
    }

    if (!s_isDragRegionProperty)
    {
        s_isDragRegionProperty = winrt::xaml::DependencyProperty::RegisterAttached(
            L"IsDragRegion",
            winrt::xaml_typename<winrt::Windows::Foundation::IReference<bool>>(),
            winrt::xaml_typename<winrt::Islands::UI::Xaml::Controls::TitleBar>(),
            Metadata(nullptr, { &TitleBar::OnIsDragRegionPropertyChanged }));
    }
}

winrt::hstring TitleBar::Title()
{
    return winrt::unbox_value_or<winrt::hstring>(GetValue(TitleProperty()), L"");
}

void TitleBar::Title(winrt::hstring const& value)
{
    SetValue(TitleProperty(), Box(value));
}

winrt::hstring TitleBar::Subtitle()
{
    return winrt::unbox_value_or<winrt::hstring>(GetValue(SubtitleProperty()), L"");
}

void TitleBar::Subtitle(winrt::hstring const& value)
{
    SetValue(SubtitleProperty(), Box(value));
}

winrt::muxc::IconSource TitleBar::IconSource()
{
    return GetValue(IconSourceProperty()).try_as<winrt::muxc::IconSource>();
}

void TitleBar::IconSource(winrt::muxc::IconSource const& value)
{
    SetValue(IconSourceProperty(), value);
}

winrt::xaml::UIElement TitleBar::LeftHeader()
{
    return GetValue(LeftHeaderProperty()).try_as<winrt::xaml::UIElement>();
}

void TitleBar::LeftHeader(winrt::xaml::UIElement const& value)
{
    SetValue(LeftHeaderProperty(), value);
}

winrt::xaml::UIElement TitleBar::Content()
{
    return GetValue(ContentProperty()).try_as<winrt::xaml::UIElement>();
}

void TitleBar::Content(winrt::xaml::UIElement const& value)
{
    SetValue(ContentProperty(), value);
}

winrt::xaml::UIElement TitleBar::RightHeader()
{
    return GetValue(RightHeaderProperty()).try_as<winrt::xaml::UIElement>();
}

void TitleBar::RightHeader(winrt::xaml::UIElement const& value)
{
    SetValue(RightHeaderProperty(), value);
}

bool TitleBar::IsBackButtonVisible()
{
    return winrt::unbox_value_or<bool>(GetValue(IsBackButtonVisibleProperty()), false);
}

void TitleBar::IsBackButtonVisible(bool value)
{
    SetValue(IsBackButtonVisibleProperty(), Box(value));
}

bool TitleBar::IsBackButtonEnabled()
{
    return winrt::unbox_value_or<bool>(GetValue(IsBackButtonEnabledProperty()), true);
}

void TitleBar::IsBackButtonEnabled(bool value)
{
    SetValue(IsBackButtonEnabledProperty(), Box(value));
}

bool TitleBar::IsPaneToggleButtonVisible()
{
    return winrt::unbox_value_or<bool>(GetValue(IsPaneToggleButtonVisibleProperty()), false);
}

void TitleBar::IsPaneToggleButtonVisible(bool value)
{
    SetValue(IsPaneToggleButtonVisibleProperty(), Box(value));
}

winrt::Islands::UI::Xaml::Controls::TitleBarTemplateSettings TitleBar::TemplateSettings()
{
    return GetValue(TemplateSettingsProperty()).try_as<winrt::Islands::UI::Xaml::Controls::TitleBarTemplateSettings>();
}

bool TitleBar::AutoRefreshDragRegions()
{
    return winrt::unbox_value_or<bool>(GetValue(AutoRefreshDragRegionsProperty()), false);
}

void TitleBar::AutoRefreshDragRegions(bool value)
{
    SetValue(AutoRefreshDragRegionsProperty(), Box(value));
}

winrt::event_token TitleBar::BackRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::Islands::UI::Xaml::Controls::TitleBar, winrt::Windows::Foundation::IInspectable> const& handler)
{
    return m_backRequested.add(handler);
}

void TitleBar::BackRequested(winrt::event_token const& token)
{
    m_backRequested.remove(token);
}

winrt::event_token TitleBar::PaneToggleRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::Islands::UI::Xaml::Controls::TitleBar, winrt::Windows::Foundation::IInspectable> const& handler)
{
    return m_paneToggleRequested.add(handler);
}

void TitleBar::PaneToggleRequested(winrt::event_token const& token)
{
    m_paneToggleRequested.remove(token);
}

winrt::xaml::DependencyProperty TitleBar::TitleProperty()
{
    EnsureProperties();
    return s_titleProperty;
}

winrt::xaml::DependencyProperty TitleBar::SubtitleProperty()
{
    EnsureProperties();
    return s_subtitleProperty;
}

winrt::xaml::DependencyProperty TitleBar::IconSourceProperty()
{
    EnsureProperties();
    return s_iconSourceProperty;
}

winrt::xaml::DependencyProperty TitleBar::LeftHeaderProperty()
{
    EnsureProperties();
    return s_leftHeaderProperty;
}

winrt::xaml::DependencyProperty TitleBar::ContentProperty()
{
    EnsureProperties();
    return s_contentProperty;
}

winrt::xaml::DependencyProperty TitleBar::RightHeaderProperty()
{
    EnsureProperties();
    return s_rightHeaderProperty;
}

winrt::xaml::DependencyProperty TitleBar::IsBackButtonVisibleProperty()
{
    EnsureProperties();
    return s_isBackButtonVisibleProperty;
}

winrt::xaml::DependencyProperty TitleBar::IsBackButtonEnabledProperty()
{
    EnsureProperties();
    return s_isBackButtonEnabledProperty;
}

winrt::xaml::DependencyProperty TitleBar::IsPaneToggleButtonVisibleProperty()
{
    EnsureProperties();
    return s_isPaneToggleButtonVisibleProperty;
}

winrt::xaml::DependencyProperty TitleBar::TemplateSettingsProperty()
{
    EnsureProperties();
    return s_templateSettingsProperty;
}

winrt::xaml::DependencyProperty TitleBar::AutoRefreshDragRegionsProperty()
{
    EnsureProperties();
    return s_autoRefreshDragRegionsProperty;
}

winrt::xaml::DependencyProperty TitleBar::IsDragRegionProperty()
{
    EnsureProperties();
    return s_isDragRegionProperty;
}

winrt::Windows::Foundation::IReference<bool> TitleBar::GetIsDragRegion(winrt::xaml::UIElement const& element)
{
    return element.GetValue(IsDragRegionProperty()).try_as<winrt::Windows::Foundation::IReference<bool>>();
}

void TitleBar::SetIsDragRegion(winrt::xaml::UIElement const& element, winrt::Windows::Foundation::IReference<bool> const& value)
{
    element.SetValue(IsDragRegionProperty(), value);
}

void TitleBar::OnTitlePropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    if (auto owner = sender.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
    {
        winrt::get_self<TitleBar>(owner)->OnPropertyChanged(args);
    }
}

void TitleBar::OnSubtitlePropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    if (auto owner = sender.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
    {
        winrt::get_self<TitleBar>(owner)->OnPropertyChanged(args);
    }
}

void TitleBar::OnIconSourcePropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    if (auto owner = sender.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
    {
        winrt::get_self<TitleBar>(owner)->OnPropertyChanged(args);
    }
}

void TitleBar::OnLeftHeaderPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    if (auto owner = sender.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
    {
        winrt::get_self<TitleBar>(owner)->OnPropertyChanged(args);
    }
}

void TitleBar::OnContentPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    if (auto owner = sender.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
    {
        winrt::get_self<TitleBar>(owner)->OnPropertyChanged(args);
    }
}

void TitleBar::OnRightHeaderPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    if (auto owner = sender.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
    {
        winrt::get_self<TitleBar>(owner)->OnPropertyChanged(args);
    }
}

void TitleBar::OnIsBackButtonVisiblePropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    if (auto owner = sender.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
    {
        winrt::get_self<TitleBar>(owner)->OnPropertyChanged(args);
    }
}

void TitleBar::OnIsBackButtonEnabledPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    if (auto owner = sender.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
    {
        winrt::get_self<TitleBar>(owner)->OnPropertyChanged(args);
    }
}

void TitleBar::OnIsPaneToggleButtonVisiblePropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    if (auto owner = sender.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
    {
        winrt::get_self<TitleBar>(owner)->OnPropertyChanged(args);
    }
}

void TitleBar::OnAutoRefreshDragRegionsPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    if (auto owner = sender.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
    {
        winrt::get_self<TitleBar>(owner)->OnPropertyChanged(args);
    }
}

void TitleBar::OnIsDragRegionPropertyChanged(winrt::xaml::DependencyObject const& sender, winrt::xaml::DependencyPropertyChangedEventArgs const&)
{
    auto current = sender.try_as<winrt::xaml::DependencyObject>();
    while (current)
    {
        if (auto titleBar = current.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>())
        {
            auto self = winrt::get_self<TitleBar>(titleBar);
            self->UpdateInteractableElementsList();
            return;
        }

        current = winrt::xaml_media::VisualTreeHelper::GetParent(current);
    }
}

void TitleBar::OnPropertyChanged(winrt::xaml::DependencyPropertyChangedEventArgs const& args)
{
    auto property = args.Property();

    if (property == s_autoRefreshDragRegionsProperty)
    {
        UpdateAutoRefreshDragRegions();
    }
    else if (property == s_isBackButtonVisibleProperty)
    {
        UpdateBackButton();
    }
    else if (property == s_isBackButtonEnabledProperty)
    {
        UpdateBackButton();
    }
    else if (property == s_isPaneToggleButtonVisibleProperty)
    {
        UpdatePaneToggleButton();
    }
    else if (property == s_iconSourceProperty)
    {
        UpdateIcon();
    }
    else if (property == s_titleProperty)
    {
        UpdateTitle();
    }
    else if (property == s_subtitleProperty)
    {
        UpdateSubtitle();
    }
    else if (property == s_leftHeaderProperty)
    {
        UpdateLeftHeader();
    }
    else if (property == s_contentProperty)
    {
        UpdateContent();
    }
    else if (property == s_rightHeaderProperty)
    {
        UpdateRightHeader();
    }

    UpdateInteractableElementsList();
}

void TitleBar::OnApplyTemplate()
{
    __super::OnApplyTemplate();

    m_backButtonClickRevoker.revoke();
    m_paneToggleButtonClickRevoker.revoke();
    m_contentLayoutUpdatedRevoker.revoke();

    m_layoutRoot = GetTemplateChildAs<winrt::xaml::FrameworkElement>(s_layoutRootPartName);
    m_leftPaddingColumn = GetTemplateChildAs<winrt::xaml_controls::ColumnDefinition>(s_leftPaddingColumnName);
    m_rightPaddingColumn = GetTemplateChildAs<winrt::xaml_controls::ColumnDefinition>(s_rightPaddingColumnName);
    m_backButton = nullptr;
    m_paneToggleButton = nullptr;
    m_iconViewbox = nullptr;
    m_leftHeaderArea = nullptr;
    m_contentAreaGrid = nullptr;
    m_contentArea = nullptr;
    m_rightHeaderArea = nullptr;

    UpdatePadding();
    UpdateIcon();
    UpdateBackButton();
    UpdatePaneToggleButton();
    UpdateTitle();
    UpdateSubtitle();
    UpdateLeftHeader();
    UpdateContent();
    UpdateRightHeader();
    UpdateInteractableElementsList();
}

winrt::xaml_peers::AutomationPeer TitleBar::OnCreateAutomationPeer()
{
    return winrt::make<TitleBarAutomationPeer>(*this);
}

void TitleBar::GoToState(std::wstring_view stateName, bool useTransitions)
{
    winrt::xaml::VisualStateManager::GoToState(*this, winrt::hstring{ stateName }, useTransitions);
}

void TitleBar::OnSizeChanged(winrt::Windows::Foundation::IInspectable const&, winrt::xaml::SizeChangedEventArgs const& args)
{
    if (Content())
    {
        if (!m_contentArea)
        {
            m_contentArea = GetTemplateChildAs<winrt::xaml::FrameworkElement>(s_contentPresenterPartName);
        }
        if (!m_contentAreaGrid)
        {
            m_contentAreaGrid = GetTemplateChildAs<winrt::xaml_controls::Grid>(s_contentPresenterGridPartName);
        }

        if (m_contentArea && m_contentAreaGrid)
        {
            if (!m_compactModeThresholdWidth && m_contentArea.DesiredSize().Width >= m_contentAreaGrid.ActualWidth())
            {
                m_compactModeThresholdWidth = args.NewSize().Width;
                m_isCompact = true;
                GoToState(L"Compact"sv, false);
            }
            else if (m_isCompact && args.NewSize().Width >= m_compactModeThresholdWidth)
            {
                m_compactModeThresholdWidth = 0.0;
                m_isCompact = false;
                GoToState(L"Expanded"sv, false);
                UpdateTitle();
                UpdateSubtitle();
            }
        }
    }

    UpdateInteractableElementsList();
}

void TitleBar::OnFlowDirectionChanged(winrt::xaml::DependencyObject const&, winrt::xaml::DependencyProperty const&)
{
    UpdatePadding();
}

void TitleBar::OnContentLayoutUpdated(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::Foundation::IInspectable const&)
{
    UpdateInteractableElementsList();

    if (!AutoRefreshDragRegions())
    {
        m_contentLayoutUpdatedRevoker.revoke();
    }
}

void TitleBar::OnBackButtonClick(winrt::Windows::Foundation::IInspectable const&, winrt::xaml::RoutedEventArgs const&)
{
    m_backRequested(*this, nullptr);
}

void TitleBar::OnPaneToggleButtonClick(winrt::Windows::Foundation::IInspectable const&, winrt::xaml::RoutedEventArgs const&)
{
    m_paneToggleRequested(*this, nullptr);
}

void TitleBar::UpdatePadding()
{
    const bool rtl = FlowDirection() == winrt::xaml::FlowDirection::RightToLeft;

    if (m_leftPaddingColumn)
    {
        m_leftPaddingColumn.Width(winrt::xaml::GridLengthHelper::FromPixels(rtl ? m_rightCaptionInset : m_leftCaptionInset));
    }

    if (m_rightPaddingColumn)
    {
        m_rightPaddingColumn.Width(winrt::xaml::GridLengthHelper::FromPixels(rtl ? m_leftCaptionInset : m_rightCaptionInset));
    }
}

void TitleBar::UpdateIcon()
{
    if (auto settings = TemplateSettings())
    {
        settings.IconElement(IconSource() ? MakeIconElementFrom(IconSource()) : nullptr);
    }

    if (IconSource())
    {
        GoToState(m_isWindowActive ? L"IconVisible"sv : L"IconDeactivated"sv, false);
        if (!m_iconViewbox)
        {
            m_iconViewbox = GetTemplateChildAs<winrt::xaml::FrameworkElement>(s_iconViewboxPartName);
        }
    }
    else
    {
        m_iconViewbox = nullptr;
        GoToState(L"IconCollapsed"sv, false);
    }
}

void TitleBar::UpdateBackButton()
{
    if (IsBackButtonVisible())
    {
        if (!m_backButton)
        {
            LoadBackButton();
        }

        if (m_backButton)
        {
            m_backButton.Visibility(winrt::xaml::Visibility::Visible);
            m_backButton.IsEnabled(IsBackButtonEnabled());
        }

        GoToState(m_isWindowActive && IsBackButtonEnabled() ? L"BackButtonVisible"sv : L"BackButtonDeactivated"sv, false);
    }
    else
    {
        if (m_backButton)
        {
            m_backButton.Visibility(winrt::xaml::Visibility::Collapsed);
        }

        GoToState(L"BackButtonCollapsed"sv, false);
    }

    UpdateLeftHeaderSpacing();
}

void TitleBar::UpdatePaneToggleButton()
{
    if (IsPaneToggleButtonVisible())
    {
        if (!m_paneToggleButton)
        {
            LoadPaneToggleButton();
        }

        if (m_paneToggleButton)
        {
            m_paneToggleButton.Visibility(winrt::xaml::Visibility::Visible);
        }

        GoToState(m_isWindowActive ? L"PaneToggleButtonVisible"sv : L"PaneToggleButtonDeactivated"sv, false);
    }
    else
    {
        if (m_paneToggleButton)
        {
            m_paneToggleButton.Visibility(winrt::xaml::Visibility::Collapsed);
        }

        GoToState(L"PaneToggleButtonCollapsed"sv, false);
    }

    UpdateLeftHeaderSpacing();
}

void TitleBar::UpdateHeight()
{
    const bool expanded = Content() || LeftHeader() || RightHeader();
    if (m_layoutRoot)
    {
        m_layoutRoot.Height(expanded ? 48.0 : 32.0);
    }

    GoToState(expanded ? L"ExpandedHeight"sv : L"CompactHeight"sv, false);
}

void TitleBar::UpdateTitle()
{
    if (Title().empty())
    {
        GoToState(L"TitleTextCollapsed"sv, false);
    }
    else if (m_isCompact)
    {
        GoToState(L"TitleTextCollapsed"sv, false);
    }
    else
    {
        GoToState(m_isWindowActive ? L"TitleTextVisible"sv : L"TitleTextDeactivated"sv, false);
    }
}

void TitleBar::UpdateSubtitle()
{
    if (Subtitle().empty() || m_isCompact)
    {
        GoToState(L"SubtitleTextCollapsed"sv, false);
    }
    else
    {
        GoToState(m_isWindowActive ? L"SubtitleTextVisible"sv : L"SubtitleTextDeactivated"sv, false);
    }
}

void TitleBar::UpdateLeftHeader()
{
    if (LeftHeader())
    {
        if (!m_leftHeaderArea)
        {
            m_leftHeaderArea = GetTemplateChildAs<winrt::xaml::FrameworkElement>(s_leftHeaderPresenterPartName);
        }
        if (m_leftHeaderArea)
        {
            m_leftHeaderArea.Visibility(winrt::xaml::Visibility::Visible);
        }
        GoToState(m_isWindowActive ? L"LeftHeaderVisible"sv : L"LeftHeaderDeactivated"sv, false);
    }
    else
    {
        if (m_leftHeaderArea)
        {
            m_leftHeaderArea.Visibility(winrt::xaml::Visibility::Collapsed);
        }
        GoToState(L"LeftHeaderCollapsed"sv, false);
    }

    UpdateHeight();
}

void TitleBar::UpdateContent()
{
    m_contentLayoutUpdatedRevoker.revoke();

    if (Content())
    {
        if (!m_contentAreaGrid)
        {
            m_contentAreaGrid = GetTemplateChildAs<winrt::xaml_controls::Grid>(s_contentPresenterGridPartName);
        }
        if (!m_contentArea)
        {
            m_contentArea = GetTemplateChildAs<winrt::xaml::FrameworkElement>(s_contentPresenterPartName);
        }
        if (m_contentAreaGrid)
        {
            m_contentAreaGrid.Visibility(winrt::xaml::Visibility::Visible);
        }

        if (auto content = Content().try_as<winrt::xaml::FrameworkElement>())
        {
            m_contentLayoutUpdatedRevoker = content.LayoutUpdated(winrt::auto_revoke, { this, &TitleBar::OnContentLayoutUpdated });
        }

        GoToState(m_isWindowActive ? L"ContentVisible"sv : L"ContentDeactivated"sv, false);
    }
    else
    {
        if (m_contentAreaGrid)
        {
            m_contentAreaGrid.Visibility(winrt::xaml::Visibility::Collapsed);
        }
        m_contentLayoutUpdatedRevoker.revoke();
        GoToState(L"ContentCollapsed"sv, false);
    }

    UpdateHeight();
}

void TitleBar::UpdateRightHeader()
{
    if (RightHeader())
    {
        if (!m_rightHeaderArea)
        {
            m_rightHeaderArea = GetTemplateChildAs<winrt::xaml::FrameworkElement>(s_rightHeaderPresenterPartName);
        }
        if (m_rightHeaderArea)
        {
            m_rightHeaderArea.Visibility(winrt::xaml::Visibility::Visible);
        }
        GoToState(m_isWindowActive ? L"RightHeaderVisible"sv : L"RightHeaderDeactivated"sv, false);
    }
    else
    {
        if (m_rightHeaderArea)
        {
            m_rightHeaderArea.Visibility(winrt::xaml::Visibility::Collapsed);
        }
        GoToState(L"RightHeaderCollapsed"sv, false);
    }

    UpdateHeight();
}

void TitleBar::UpdateInteractableElementsList()
{
    m_interactableElements.clear();

    if (IsBackButtonVisible() && IsBackButtonEnabled())
    {
        if (!m_backButton)
        {
            LoadBackButton();
        }
        if (m_backButton)
        {
            m_interactableElements.push_back(m_backButton);
        }
    }

    if (IsPaneToggleButtonVisible())
    {
        if (!m_paneToggleButton)
        {
            LoadPaneToggleButton();
        }
        if (m_paneToggleButton)
        {
            m_interactableElements.push_back(m_paneToggleButton);
        }
    }

    if (LeftHeader())
    {
        if (!m_leftHeaderArea)
        {
            m_leftHeaderArea = GetTemplateChildAs<winrt::xaml::FrameworkElement>(s_leftHeaderPresenterPartName);
        }
        if (m_leftHeaderArea)
        {
            m_interactableElements.push_back(m_leftHeaderArea);
        }
    }

    if (Content())
    {
        if (!m_contentArea)
        {
            m_contentArea = GetTemplateChildAs<winrt::xaml::FrameworkElement>(s_contentPresenterPartName);
        }
        FindInteractableElements(m_contentArea, false);
    }

    if (RightHeader())
    {
        if (!m_rightHeaderArea)
        {
            m_rightHeaderArea = GetTemplateChildAs<winrt::xaml::FrameworkElement>(s_rightHeaderPresenterPartName);
        }
        if (m_rightHeaderArea)
        {
            m_interactableElements.push_back(m_rightHeaderArea);
        }
    }
}

void TitleBar::UpdateLeftHeaderSpacing()
{
    GoToState(IsBackButtonVisible() == IsPaneToggleButtonVisible() ? L"DefaultSpacing"sv : L"NegativeInsetSpacing"sv, false);
}

void TitleBar::UpdateAutoRefreshDragRegions()
{
    if (AutoRefreshDragRegions())
    {
        if (Content())
        {
            if (auto content = Content().try_as<winrt::xaml::FrameworkElement>())
            {
                m_contentLayoutUpdatedRevoker = content.LayoutUpdated(winrt::auto_revoke, { this, &TitleBar::OnContentLayoutUpdated });
            }
        }

        UpdateInteractableElementsList();
    }
    else
    {
        m_contentLayoutUpdatedRevoker.revoke();
    }
}

void TitleBar::ApplyActivationStates()
{
    UpdateIcon();
    UpdateBackButton();
    UpdatePaneToggleButton();
    UpdateTitle();
    UpdateSubtitle();
    UpdateLeftHeader();
    UpdateContent();
    UpdateRightHeader();
}

void TitleBar::LoadBackButton()
{
    m_backButton = GetTemplateChildAs<winrt::xaml_controls::Button>(s_backButtonPartName);

    if (m_backButton)
    {
        m_backButtonClickRevoker = m_backButton.Click(winrt::auto_revoke, { this, &TitleBar::OnBackButtonClick });

        if (winrt::xaml_automation::AutomationProperties::GetName(m_backButton).empty())
        {
            winrt::xaml_automation::AutomationProperties::SetName(m_backButton, GetLocalizedStringResource(L"NavigationBackButtonName"sv));
        }

        auto tooltip = winrt::xaml_controls::ToolTip();
        tooltip.Content(Box(GetLocalizedStringResource(L"NavigationBackButtonToolTip"sv)));
        winrt::xaml_controls::ToolTipService::SetToolTip(m_backButton, tooltip);
    }
}

void TitleBar::LoadPaneToggleButton()
{
    m_paneToggleButton = GetTemplateChildAs<winrt::xaml_controls::Button>(s_paneToggleButtonPartName);

    if (m_paneToggleButton)
    {
        m_paneToggleButtonClickRevoker = m_paneToggleButton.Click(winrt::auto_revoke, { this, &TitleBar::OnPaneToggleButtonClick });

        if (winrt::xaml_automation::AutomationProperties::GetName(m_paneToggleButton).empty())
        {
            winrt::xaml_automation::AutomationProperties::SetName(m_paneToggleButton, GetLocalizedStringResource(L"NavigationButtonToggleName"sv));
        }

        auto tooltip = winrt::xaml_controls::ToolTip();
        tooltip.Content(Box(winrt::xaml_automation::AutomationProperties::GetName(m_paneToggleButton)));
        winrt::xaml_controls::ToolTipService::SetToolTip(m_paneToggleButton, tooltip);
    }
}

void TitleBar::RecomputeDragRegions()
{
    UpdateLayout();
    UpdateInteractableElementsList();
}

void TitleBar::SetWindowActive(bool active)
{
    if (m_isWindowActive != active)
    {
        m_isWindowActive = active;
        ApplyActivationStates();
    }
}

void TitleBar::SetCaptionInsets(double left, double right)
{
    m_leftCaptionInset = std::max(0.0, left);
    m_rightCaptionInset = std::max(0.0, right);
    UpdatePadding();
}

winrt::Windows::Foundation::Rect TitleBar::GetTitleBarRootBounds()
{
    auto titleBounds = GetElementBounds(*this);
    if (titleBounds.Width <= 0.0f)
    {
        titleBounds.Width = static_cast<float>(MaxLength(ActualWidth(), Width()));
    }
    if (titleBounds.Height <= 0.0f)
    {
        titleBounds.Height = static_cast<float>(std::max(MaxLength(ActualHeight(), Height()), std::max(ValidLength(MinHeight()), 32.0)));
    }

    return titleBounds;
}

std::vector<winrt::Windows::Foundation::Rect> TitleBar::GetPassthroughRects()
{
    UpdateInteractableElementsList();

    std::vector<winrt::Windows::Foundation::Rect> rects;
    rects.reserve(m_interactableElements.size());

    for (auto const& element : m_interactableElements)
    {
        auto rect = GetElementBounds(element);
        if (rect.Width > 0.0f && rect.Height > 0.0f)
        {
            rects.push_back(rect);
        }
    }

    return rects;
}

std::vector<winrt::Windows::Foundation::Rect> TitleBar::GetIconRects()
{
    std::vector<winrt::Windows::Foundation::Rect> rects;

    if (!IconSource())
    {
        return rects;
    }

    if (!m_iconViewbox)
    {
        m_iconViewbox = GetTemplateChildAs<winrt::xaml::FrameworkElement>(s_iconViewboxPartName);
    }

    if (m_iconViewbox)
    {
        auto rect = GetElementBounds(m_iconViewbox);
        if (rect.Width > 0.0f && rect.Height > 0.0f)
        {
            rects.push_back(rect);
        }
    }

    return rects;
}

double TitleBar::RasterizationScale()
{
    if (auto root = XamlRoot())
    {
        return root.RasterizationScale();
    }

    return 1.0;
}

int32_t TitleBar::HitTest(int32_t screenX, int32_t screenY, int32_t xamlRootScreenX, int32_t xamlRootScreenY)
{
    double scale = RasterizationScale();

    winrt::Windows::Foundation::Point point{
        static_cast<float>((screenX - xamlRootScreenX) / scale),
        static_cast<float>((screenY - xamlRootScreenY) / scale)
    };

    auto titleBounds = GetTitleBarRootBounds();
    if (!ContainsPoint(titleBounds, point))
    {
        return HTNOWHERE;
    }

    for (auto const& iconRect : GetIconRects())
    {
        if (ContainsPoint(iconRect, point))
        {
            return HTSYSMENU;
        }
    }

    UpdateInteractableElementsList();

    try
    {
        for (auto const& hitElement : winrt::xaml_media::VisualTreeHelper::FindElementsInHostCoordinates(point, *this, true))
        {
            for (auto const& element : m_interactableElements)
            {
                if (IsElementOrDescendantOf(hitElement, element))
                {
                    return HTCLIENT;
                }
            }
        }
    }
    catch (...)
    {
    }

    for (auto const& element : m_interactableElements)
    {
        if (ContainsPoint(GetElementBounds(element), point))
        {
            return HTCLIENT;
        }
    }

    return HTCAPTION;
}

winrt::Windows::Foundation::Rect TitleBar::GetElementBounds(winrt::xaml::FrameworkElement const& element)
{
    if (!element)
    {
        return {};
    }

    auto const width = static_cast<float>(MaxLength(element.ActualWidth(), element.Width()));
    auto const height = static_cast<float>(std::max(MaxLength(element.ActualHeight(), element.Height()), ValidLength(element.MinHeight())));

    try
    {
        winrt::xaml::UIElement rootContent{ nullptr };
        if (auto root = element.XamlRoot())
        {
            rootContent = root.Content();
        }

        auto transform = element.TransformToVisual(rootContent);
        return transform.TransformBounds({
            0.0f,
            0.0f,
            width,
            height
        });
    }
    catch (...)
    {
        return {
            0.0f,
            0.0f,
            width,
            height
        };
    }
}

bool TitleBar::ContainsPoint(winrt::Windows::Foundation::Rect const& bounds, winrt::Windows::Foundation::Point const& point)
{
    return bounds.Width > 0 &&
        bounds.Height > 0 &&
        point.X >= bounds.X &&
        point.X < bounds.X + bounds.Width &&
        point.Y >= bounds.Y &&
        point.Y < bounds.Y + bounds.Height;
}

void TitleBar::FindInteractableElements(winrt::xaml::DependencyObject const& element, bool parentIsDragRegion)
{
    if (!element)
    {
        return;
    }

    auto uiElement = element.try_as<winrt::xaml::UIElement>();
    if (!uiElement ||
        uiElement.Visibility() != winrt::xaml::Visibility::Visible ||
        !uiElement.IsHitTestVisible())
    {
        return;
    }

    bool currentIsDragRegion = parentIsDragRegion;

    if (auto isDragRegion = winrt::Islands::UI::Xaml::Controls::TitleBar::GetIsDragRegion(uiElement))
    {
        if (!isDragRegion.Value())
        {
            if (auto frameworkElement = uiElement.try_as<winrt::xaml::FrameworkElement>())
            {
                m_interactableElements.push_back(frameworkElement);
            }
            return;
        }

        if (uiElement.try_as<winrt::xaml_controls::Control>())
        {
            return;
        }

        currentIsDragRegion = true;
    }

    if (!currentIsDragRegion)
    {
        if (auto control = uiElement.try_as<winrt::xaml_controls::Control>())
        {
            if (control.IsEnabled())
            {
                m_interactableElements.push_back(control);
                return;
            }
        }
    }

    const auto childCount = winrt::xaml_media::VisualTreeHelper::GetChildrenCount(element);
    for (int32_t i = 0; i < childCount; ++i)
    {
        FindInteractableElements(winrt::xaml_media::VisualTreeHelper::GetChild(element, i), currentIsDragRegion);
    }
}

winrt::xaml_controls::IconElement TitleBar::MakeIconElementFrom(winrt::muxc::IconSource const& iconSource)
{
    if (!iconSource)
    {
        return nullptr;
    }

    if (auto fontIconSource = iconSource.try_as<winrt::muxc::FontIconSource>())
    {
        auto icon = winrt::xaml_controls::FontIcon();
        icon.Glyph(fontIconSource.Glyph());
        icon.FontSize(fontIconSource.FontSize());
        icon.FontWeight(fontIconSource.FontWeight());
        icon.FontStyle(fontIconSource.FontStyle());
        icon.IsTextScaleFactorEnabled(fontIconSource.IsTextScaleFactorEnabled());
        icon.MirroredWhenRightToLeft(fontIconSource.MirroredWhenRightToLeft());

        if (fontIconSource.FontFamily())
        {
            icon.FontFamily(fontIconSource.FontFamily());
        }
        if (fontIconSource.Foreground())
        {
            icon.Foreground(fontIconSource.Foreground());
        }

        return icon;
    }

    if (auto symbolIconSource = iconSource.try_as<winrt::muxc::SymbolIconSource>())
    {
        auto icon = winrt::xaml_controls::SymbolIcon();
        icon.Symbol(static_cast<winrt::xaml_controls::Symbol>(static_cast<int32_t>(symbolIconSource.Symbol())));
        if (symbolIconSource.Foreground())
        {
            icon.Foreground(symbolIconSource.Foreground());
        }
        return icon;
    }

    if (auto bitmapIconSource = iconSource.try_as<winrt::muxc::BitmapIconSource>())
    {
        auto icon = winrt::xaml_controls::BitmapIcon();
        if (bitmapIconSource.UriSource())
        {
            icon.UriSource(bitmapIconSource.UriSource());
        }
        icon.ShowAsMonochrome(bitmapIconSource.ShowAsMonochrome());
        if (bitmapIconSource.Foreground())
        {
            icon.Foreground(bitmapIconSource.Foreground());
        }
        return icon;
    }

    if (auto pathIconSource = iconSource.try_as<winrt::muxc::PathIconSource>())
    {
        auto icon = winrt::xaml_controls::PathIcon();
        if (pathIconSource.Data())
        {
            icon.Data(pathIconSource.Data());
        }
        if (pathIconSource.Foreground())
        {
            icon.Foreground(pathIconSource.Foreground());
        }
        return icon;
    }

    return nullptr;
}

winrt::hstring TitleBar::GetLocalizedStringResource(std::wstring_view resourceName)
{
    try
    {
        auto loader = winrt::Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView(L"Islands.UI.Xaml.Controls/Resources");
        if (auto value = loader.GetString(winrt::hstring{ resourceName }); !value.empty())
        {
            return value;
        }
    }
    catch (...)
    {
    }

    if (resourceName == L"NavigationButtonToggleName"sv)
    {
        return L"Toggle Navigation";
    }

    return L"Back";
}

}
