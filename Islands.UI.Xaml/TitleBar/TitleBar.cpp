// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

import std;
import inc.common;
import ixx.Utils;
import ixx.ResourceAccessor;
import ixx.TitleBar;
import ixx.TitleBar.interop;
import ixx.TitleBarTrace;
import ixx.TitleBarWindowAdapter;
import ixx.TitleBarTemplateSettings;
import ixx.TitleBarAutomationPeer;
import ixx.TypeLogging;
import ixx.RuntimeProfiler;

namespace
{
    inline constexpr PCWSTR traceMsgMeth = L"%s[0x%p]()\n";
    inline constexpr PCWSTR traceMsgMethStr = L"%s[0x%p](%s)\n";
    inline constexpr PCWSTR traceMsgMethStrInt = L"%s[0x%p](%s, %d)\n";

    std::wstring TraceMethodName(char const* functionName)
    {
        return StringUtil::Utf8ToUtf16(functionName);
    }
}

#define TRACE_MSG_METH traceMsgMeth
#define TRACE_MSG_METH_STR traceMsgMethStr
#define TRACE_MSG_METH_STR_INT traceMsgMethStrInt
#define METH_NAME TraceMethodName(__FUNCTION__).c_str()
#define TITLEBAR_TRACE_INFO(sender, message, ...) \
    do \
    { \
        if (TitleBarTrace::IsInfoEnabled()) \
        { \
            TitleBarTrace::Info(sender, message, __VA_ARGS__); \
        } \
    } while (false)
#define TITLEBAR_TRACE_VERBOSE(sender, message, ...) \
    do \
    { \
        if (TitleBarTrace::IsVerboseEnabled()) \
        { \
            TitleBarTrace::Verbose(sender, message, __VA_ARGS__); \
        } \
    } while (false)
#define TITLEBAR_TRACE_PERF(info) \
    do \
    { \
        if (TitleBarTrace::IsPerfEnabled()) \
        { \
            TitleBarTrace::Perf(info); \
        } \
    } while (false)

#if defined(DBG) || defined(_DEBUG)
#define TITLEBAR_TRACE_INFO_DBG(sender, message, ...) TITLEBAR_TRACE_INFO(sender, message, __VA_ARGS__)
#define TITLEBAR_TRACE_VERBOSE_DBG(sender, message, ...) TITLEBAR_TRACE_VERBOSE(sender, message, __VA_ARGS__)
#define TITLEBAR_TRACE_PERF_DBG(info) TITLEBAR_TRACE_PERF(info)
#else
#define TITLEBAR_TRACE_INFO_DBG(sender, message, ...)
#define TITLEBAR_TRACE_VERBOSE_DBG(sender, message, ...)
#define TITLEBAR_TRACE_PERF_DBG(info)
#endif

bool TitleBarTrace::s_IsDebugOutputEnabled{ false };
bool TitleBarTrace::s_IsVerboseDebugOutputEnabled{ false };

namespace TitleBarImplementation
{
    void RegisterWindowAdapter(winrt::TitleBar const& titleBar, TitleBarWindowAdapter* adapter)
    {
        winrt::get_self<::TitleBar>(titleBar)->RegisterWindowAdapter(adapter);
    }

    void UnregisterWindowAdapter(winrt::TitleBar const& titleBar, TitleBarWindowAdapter* adapter)
    {
        winrt::get_self<::TitleBar>(titleBar)->UnregisterWindowAdapter(adapter);
    }

    void SetWindowActive(winrt::TitleBar const& titleBar, bool active)
    {
        winrt::get_self<::TitleBar>(titleBar)->SetWindowActive(active);
    }

    void SetCaptionInsets(winrt::TitleBar const& titleBar, double left, double right)
    {
        winrt::get_self<::TitleBar>(titleBar)->SetCaptionInsets(left, right);
    }

    std::int32_t HitTest(winrt::TitleBar const& titleBar, std::int32_t screenX, std::int32_t screenY, std::int32_t xamlRootScreenX, std::int32_t xamlRootScreenY)
    {
        return winrt::get_self<::TitleBar>(titleBar)->HitTest(screenX, screenY, xamlRootScreenX, xamlRootScreenY);
    }

    winrt::Rect GetTitleBarRootBounds(winrt::TitleBar const& titleBar)
    {
        return winrt::get_self<::TitleBar>(titleBar)->GetTitleBarRootBounds();
    }

    double RasterizationScale(winrt::TitleBar const& titleBar)
    {
        return winrt::get_self<::TitleBar>(titleBar)->RasterizationScale();
    }

    std::vector<winrt::Rect> GetPassthroughRects(winrt::TitleBar const& titleBar)
    {
        return winrt::get_self<::TitleBar>(titleBar)->GetPassthroughRects();
    }

    std::vector<winrt::Rect> GetIconRects(winrt::TitleBar const& titleBar)
    {
        return winrt::get_self<::TitleBar>(titleBar)->GetIconRects();
    }
}

TitleBar::TitleBar()
{
    TITLEBAR_TRACE_INFO(nullptr, TRACE_MSG_METH, METH_NAME, this);

    [] {
#pragma warning(suppress : 28112)
        static volatile LONG counter = -1;
        if (0 == interlockedIncrement(&counter))
        {
            RuntimeProfiler::RegisterMethod(RuntimeProfiler::PG_Class, static_cast<UINT16>(RuntimeProfiler::ProfId_TitleBar), 9999, &counter);
        }
    }();

    SetValue(s_TemplateSettingsProperty, winrt::make<::TitleBarTemplateSettings>());

    winrt::IControlProtected controlProtected{ *this };
    SetDefaultStyleKeyWorker(controlProtected, GetRuntimeClassName());

    m_sizeChangedRevoker = SizeChanged(winrt::auto_revoke, { this, &TitleBar::OnSizeChanged });
    m_flowDirectionChangedToken = RegisterPropertyChangedCallback(winrt::FrameworkElement::FlowDirectionProperty(), { this, &TitleBar::OnFlowDirectionChanged });
}

TitleBar::~TitleBar()
{
    TITLEBAR_TRACE_INFO(nullptr, TRACE_MSG_METH, METH_NAME, this);

    m_sizeChangedRevoker.revoke();
    if (m_flowDirectionChangedToken)
    {
        UnregisterPropertyChangedCallback(winrt::FrameworkElement::FlowDirectionProperty(), m_flowDirectionChangedToken);
        m_flowDirectionChangedToken = 0;
    }
}

winrt::AutomationPeer TitleBar::OnCreateAutomationPeer()
{
    return winrt::make<TitleBarAutomationPeer>(*this);
}

void TitleBar::OnApplyTemplate()
{
    TITLEBAR_TRACE_INFO(*this, TRACE_MSG_METH, METH_NAME, this);

    __super::OnApplyTemplate();

    winrt::IControlProtected controlProtected{ *this };

    m_leftPaddingColumn.set(GetTemplateChildT<winrt::ColumnDefinition>(s_leftPaddingColumnName, controlProtected));
    m_rightPaddingColumn.set(GetTemplateChildT<winrt::ColumnDefinition>(s_rightPaddingColumnName, controlProtected));

    UpdateHeight();
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
    UpdateDragRegion();
    UpdateIconRegion();
}

void TitleBar::OnPropertyChanged(winrt::DependencyPropertyChangedEventArgs const& args)
{
    winrt::IDependencyProperty property = args.Property();

    if (property == s_AutoRefreshDragRegionsProperty)
    {
        UpdateAutoRefreshDragRegions();
    }
    else if (property == s_IsBackButtonVisibleProperty)
    {
        UpdateBackButton();
    }
    else if (property == s_IsBackButtonEnabledProperty)
    {
        UpdateInteractableElementsList();
    }
    else if (property == s_IsPaneToggleButtonVisibleProperty)
    {
        UpdatePaneToggleButton();
    }
    else if (property == s_IconSourceProperty)
    {
        UpdateIcon();
    }
    else if (property == s_TitleProperty)
    {
        UpdateTitle();
    }
    else if (property == s_SubtitleProperty)
    {
        UpdateSubtitle();
    }
    else if (property == s_LeftHeaderProperty)
    {
        UpdateLeftHeader();
    }
    else if (property == s_ContentProperty)
    {
        UpdateContent();
    }
    else if (property == s_RightHeaderProperty)
    {
        UpdateRightHeader();
    }

    UpdateDragRegion();
    UpdateIconRegion();
}

void TitleBar::GoToState(std::wstring_view const& stateName, bool useTransitions)
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH_STR_INT, METH_NAME, this, stateName.data(), useTransitions);

    winrt::VisualStateManager::GoToState(*this, stateName, useTransitions);
}

void TitleBar::OnSizeChanged(const winrt::IInspectable& sender, const winrt::SizeChangedEventArgs& args)
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    if (Content() != nullptr)
    {
        const auto contentArea = m_contentArea.get();
        const auto contentAreaGrid = m_contentAreaGrid.get();

        if (contentArea && contentAreaGrid)
        {
            if (!m_compactModeThresholdWidth && contentArea.DesiredSize().Width >= contentAreaGrid.ActualWidth())
            {
                m_compactModeThresholdWidth = args.NewSize().Width;
                m_isCompact = true;
                GoToState(s_compactVisualStateName, false);
            }
            else if (m_isCompact && args.NewSize().Width >= m_compactModeThresholdWidth)
            {
                m_compactModeThresholdWidth = 0.0;
                m_isCompact = false;
                GoToState(s_expandedVisualStateName, false);
                UpdateTitle();
                UpdateSubtitle();
            }
        }
    }

    UpdateDragRegion();
    UpdateIconRegion();
}

void TitleBar::OnFlowDirectionChanged(const winrt::DependencyObject& /*sender*/, const winrt::DependencyProperty& /*args*/)
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    UpdatePadding();
}

void TitleBar::OnBackButtonClick(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& args)
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    m_backRequestedEventSource(*this, nullptr);
}

void TitleBar::OnPaneToggleButtonClick(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& args)
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    m_paneToggleRequestedEventSource(*this, nullptr);
}

void TitleBar::UpdateIcon()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    auto const templateSettings = winrt::get_self<::TitleBarTemplateSettings>(TemplateSettings());
    if (auto const source = IconSource())
    {
        if (!m_iconViewbox.get())
        {
            m_iconViewbox.set(GetTemplateChildT<winrt::FrameworkElement>(s_iconViewboxPartName, *this));
        }

        // 55625016
        // AppWindowTitleBar's InputNonClientPointerSource currently resets all non-passthrough region rects on every interaction.
        // As such, we added extra event listeners to manually update the nonClientPointerSource::Icon rect as a workaround.
        if (auto const iconViewbox = m_iconViewbox.get())
        {
            m_iconLayoutUpdatedRevoker = iconViewbox.LayoutUpdated(winrt::auto_revoke, { this, &TitleBar::OnIconLayoutUpdated });
        }
        else
        {
            m_iconLayoutUpdatedRevoker.revoke();
        }

        templateSettings->IconElement(SharedHelpers::MakeIconElementFrom(source));
        GoToState(m_isWindowActive ? s_iconVisibleVisualStateName : s_iconDeactivatedVisualStateName, false);
    }
    else
    {
        m_iconLayoutUpdatedRevoker.revoke();

        templateSettings->IconElement(nullptr);
        GoToState(s_iconCollapsedVisualStateName, false);
    }

    UpdateDragRegion();
    UpdateIconRegion();
}

void TitleBar::OnIconLayoutUpdated(const winrt::IInspectable& sender, const winrt::IInspectable& args)
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    UpdateIconRegion();
}

void TitleBar::OnContentLayoutUpdated(const winrt::IInspectable& /*sender*/, const winrt::IInspectable& /*args*/)
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    // Content layout has changed (children added/removed/resized at runtime).
    // Refresh the interactable elements list and drag region.
    UpdateInteractableElementsList();
    UpdateDragRegion();

    // If auto-refresh is disabled, unsubscribe after the first update.
    // This gives us one-shot behavior: the initial layout pass updates
    // drag regions, then we stop listening to avoid repeated tree walks.
    if (!AutoRefreshDragRegions())
    {
        m_contentLayoutUpdatedRevoker.revoke();
    }
}

// Static callback for IsDragRegion attached property changes.
// Walks up the visual tree to find the parent TitleBar and triggers an update of its drag regions.
// This handles dynamic changes to IsDragRegion at runtime (including hot reload scenarios).
// 
// Note: If element is not yet in the visual tree (e.g., during initial XAML parsing),
// GetParent returns null and we exit immediately. The TitleBar will discover the
// IsDragRegion value later via FindInteractableElements() during layout updates.
void TitleBar::OnIsDragRegionPropertyChanged(
    winrt::DependencyObject const& sender,
    winrt::DependencyPropertyChangedEventArgs const& /*args*/)
{
    // Walk up from sender to find the owning TitleBar and refresh its drag regions.
    // Note: If multiple elements have their IsDragRegion changed at the same time,
    // this will result in duplicate work. A future optimization could defer the update
    // using CompositionTarget.Rendered to coalesce multiple changes into a single pass.
    auto current = sender.try_as<winrt::DependencyObject>();
    while (current)
    {
        if (auto titleBar = current.try_as<winrt::TitleBar>())
        {
            if (auto titleBarImpl = winrt::get_self<TitleBar>(titleBar))
            {
                titleBarImpl->UpdateInteractableElementsList();
                titleBarImpl->UpdateDragRegion();
            }
            return;
        }
        current = winrt::VisualTreeHelper::GetParent(current);
    }
}

void TitleBar::UpdateBackButton()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    if (IsBackButtonVisible())
    {
        if (!m_backButton.get())
        {
            LoadBackButton();
        }

        GoToState(m_isWindowActive && IsBackButtonEnabled() ? s_backButtonVisibleVisualStateName : s_backButtonDeactivatedVisualStateName, false);
    }
    else
    {
        GoToState(s_backButtonCollapsedVisualStateName, false);
    }
    
    UpdateInteractableElementsList();
    UpdateLeftHeaderSpacing();
}

void TitleBar::UpdatePaneToggleButton()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    if (IsPaneToggleButtonVisible())
    {
        if (!m_paneToggleButton.get())
        {
            LoadPaneToggleButton();
        }

        GoToState(m_isWindowActive ? s_paneToggleButtonVisibleVisualStateName : s_paneToggleButtonDeactivatedVisualStateName, false);
    }
    else
    {
        GoToState(s_paneToggleButtonCollapsedVisualStateName, false);
    }

    UpdateInteractableElementsList();
    UpdateLeftHeaderSpacing();
}

void TitleBar::UpdateHeight()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    GoToState((Content() == nullptr && LeftHeader() == nullptr && RightHeader() == nullptr) ?
        s_compactHeightVisualStateName : s_expandedHeightVisualStateName,
        false);
}

void TitleBar::UpdatePadding()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    if (const auto leftColumn = m_leftPaddingColumn.get())
    {
        leftColumn.Width(winrt::GridLengthHelper::FromPixels(FlowDirection() == winrt::FlowDirection::RightToLeft ? m_rightCaptionInset : m_leftCaptionInset));
    }

    if (const auto rightColumn = m_rightPaddingColumn.get())
    {
        rightColumn.Width(winrt::GridLengthHelper::FromPixels(FlowDirection() == winrt::FlowDirection::RightToLeft ? m_leftCaptionInset : m_rightCaptionInset));
    }
}

void TitleBar::UpdateTitle()
{
    const winrt::hstring titleText = Title();

    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH_STR, METH_NAME, this, titleText.c_str());

    if (titleText.empty())
    {
        GoToState(s_titleTextCollapsedVisualStateName, false);
        return;
    }

    GoToState(m_isCompact ? s_titleTextCollapsedVisualStateName : (m_isWindowActive ? s_titleTextVisibleVisualStateName : s_titleTextDeactivatedVisualStateName), false);
}

void TitleBar::UpdateSubtitle()
{
    const winrt::hstring subTitleText = Subtitle();

    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH_STR, METH_NAME, this, subTitleText.c_str());

    if (subTitleText.empty())
    {
        GoToState(s_subtitleTextCollapsedVisualStateName, false);
    }
    else
    {
        GoToState(m_isCompact ? s_subtitleTextCollapsedVisualStateName : (m_isWindowActive ? s_subtitleTextVisibleVisualStateName : s_subtitleTextDeactivatedVisualStateName), false);
    }
}

void TitleBar::UpdateLeftHeader()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    if (LeftHeader() == nullptr)
    {
        GoToState(s_leftHeaderCollapsedVisualStateName, false);
    }
    else
    {
        if (!m_leftHeaderArea.get())
        {
            m_leftHeaderArea.set(GetTemplateChildT<winrt::FrameworkElement>(s_leftHeaderPresenterPartName, *this));
        }
        GoToState(m_isWindowActive ? s_leftHeaderVisibleVisualStateName : s_leftHeaderDeactivatedVisualStateName, false);
    }

    UpdateHeight();
    UpdateInteractableElementsList();
}

void TitleBar::UpdateContent()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    // Revoke previous handler
    m_contentLayoutUpdatedRevoker.revoke();

    if (Content() == nullptr)
    {
        GoToState(s_contentCollapsedVisualStateName, false);
    }
    else
    {
        if (!m_contentArea.get())
        {
            winrt::IControlProtected controlProtected{ *this };

            m_contentAreaGrid.set(GetTemplateChildT<winrt::Grid>(s_contentPresenterGridPartName, controlProtected));
            m_contentArea.set(GetTemplateChildT<winrt::FrameworkElement>(s_contentPresenterPartName, controlProtected));
        }

        // Always subscribe to LayoutUpdated which fires after Loaded + Measure + Arrange,
        // ensuring elements have valid bounds. If AutoRefreshDragRegions is false, the
        // handler will self-unregister after the first update (one-shot behavior).
        if (const auto content = Content().try_as<winrt::FrameworkElement>())
        {
            m_contentLayoutUpdatedRevoker = content.LayoutUpdated(winrt::auto_revoke, { this, &TitleBar::OnContentLayoutUpdated });
        }

        GoToState(m_isWindowActive ? s_contentVisibleVisualStateName : s_contentDeactivatedVisualStateName, false);
    }

    UpdateHeight();
    UpdateInteractableElementsList();
}

void TitleBar::UpdateRightHeader()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    if (RightHeader() == nullptr)
    {
        GoToState(s_rightHeaderCollapsedVisualStateName, false);
    }
    else
    {
        if (!m_rightHeaderArea.get())
        {
            m_rightHeaderArea.set(GetTemplateChildT<winrt::FrameworkElement>(s_rightHeaderPresenterPartName, *this));
        }
        GoToState(m_isWindowActive ? s_rightHeaderVisibleVisualStateName : s_rightHeaderDeactivatedVisualStateName, false);
    }

    UpdateHeight();
    UpdateInteractableElementsList();
}

void TitleBar::UpdateDragRegion()
{
    UpdateInteractableElementsList();

    if (m_windowAdapter)
    {
        m_windowAdapter->SyncNonClientRegions();
    }
}

void TitleBar::UpdateIconRegion()
{
    if (IconSource() && !m_iconViewbox.get())
    {
        m_iconViewbox.set(GetTemplateChildT<winrt::FrameworkElement>(s_iconViewboxPartName, *this));
    }

    if (m_windowAdapter)
    {
        m_windowAdapter->SyncNonClientRegions();
    }
}

void TitleBar::UpdateInteractableElementsList()
{
    m_interactableElementsList.clear();

    if (IsBackButtonVisible() && IsBackButtonEnabled())
    {
        if (const auto backButton = m_backButton.get())
        {
            TITLEBAR_TRACE_VERBOSE_DBG(*this, TRACE_MSG_METH_STR, METH_NAME, this, L"Append backButton to m_interactableElementsList");

            m_interactableElementsList.push_back(backButton);
        }
    }

    if (IsPaneToggleButtonVisible())
    {
        if (const auto paneToggleButton = m_paneToggleButton.get())
        {
            TITLEBAR_TRACE_VERBOSE_DBG(*this, TRACE_MSG_METH_STR, METH_NAME, this, L"Append paneToggleButton to m_interactableElementsList");

            m_interactableElementsList.push_back(paneToggleButton);
        }
    }

    if (LeftHeader() != nullptr)
    {
        if (const auto leftHeaderArea = m_leftHeaderArea.get())
        {
            TITLEBAR_TRACE_VERBOSE_DBG(*this, TRACE_MSG_METH_STR, METH_NAME, this, L"Append headerArea to m_interactableElementsList");

            m_interactableElementsList.push_back(leftHeaderArea);
        }
    }

    if (Content() != nullptr)
    {
        if (const auto contentArea = m_contentArea.get())
        {
            TITLEBAR_TRACE_VERBOSE_DBG(*this, TRACE_MSG_METH_STR, METH_NAME, this, L"Find controls in contentArea");

            // Recursively find interactive controls, respecting IsDragRegion
            FindInteractableElements(contentArea, false);
        }
    }

    if (RightHeader() != nullptr)
    {
        if (const auto rightHeaderArea = m_rightHeaderArea.get())
        {
            TITLEBAR_TRACE_VERBOSE_DBG(*this, TRACE_MSG_METH_STR, METH_NAME, this, L"Append footerArea to m_interactableElementsList");

            m_interactableElementsList.push_back(rightHeaderArea);
        }
    }

    TITLEBAR_TRACE_VERBOSE_DBG(*this, TRACE_MSG_METH_STR_INT, METH_NAME, this,
        L"m_interactableElementsList Size:",
        m_interactableElementsList.size());
}

void TitleBar::UpdateLeftHeaderSpacing()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    GoToState(
        IsBackButtonVisible() == IsPaneToggleButtonVisible() ?
        s_defaultSpacingVisualStateName : s_negativeInsetVisualStateName,
        false);
}

void TitleBar::RecomputeDragRegions()
{
    TITLEBAR_TRACE_INFO(*this, TRACE_MSG_METH, METH_NAME, this);

    // Force a synchronous layout pass so the visual tree reflects any
    // recently added/removed children and elements have valid bounds.
    UpdateLayout();

    UpdateInteractableElementsList();
    UpdateDragRegion();
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
    m_leftCaptionInset = (std::max)(0.0, left);
    m_rightCaptionInset = (std::max)(0.0, right);
    UpdatePadding();
}

winrt::Rect TitleBar::GetTitleBarRootBounds()
{
    auto titleBounds = GetElementBounds(*this);
    if (titleBounds.Width <= 0.0f)
    {
        titleBounds.Width = static_cast<float>(MaxLength(ActualWidth(), Width()));
    }
    if (titleBounds.Height <= 0.0f)
    {
        titleBounds.Height = static_cast<float>((std::max)(MaxLength(ActualHeight(), Height()), (std::max)(ValidLength(MinHeight()), 32.0)));
    }

    return titleBounds;
}

std::vector<winrt::Rect> TitleBar::GetPassthroughRects()
{
    UpdateInteractableElementsList();

    std::vector<winrt::Rect> rects;
    rects.reserve(m_interactableElementsList.size());

    for (auto const& element : m_interactableElementsList)
    {
        auto rect = GetElementBounds(element);
        if (rect.Width > 0.0f && rect.Height > 0.0f)
        {
            rects.push_back(rect);
        }
    }

    return rects;
}

std::vector<winrt::Rect> TitleBar::GetIconRects()
{
    std::vector<winrt::Rect> rects;

    if (!IconSource())
    {
        return rects;
    }

    if (!m_iconViewbox.get())
    {
        m_iconViewbox.set(GetTemplateChildT<winrt::FrameworkElement>(s_iconViewboxPartName, *this));
    }

    if (const auto iconViewbox = m_iconViewbox.get())
    {
        auto rect = GetElementBounds(iconViewbox);
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

void TitleBar::RegisterWindowAdapter(TitleBarWindowAdapter* adapter)
{
    m_windowAdapter = adapter;
    UpdateDragRegion();
    UpdateIconRegion();
}

void TitleBar::UnregisterWindowAdapter(TitleBarWindowAdapter* adapter)
{
    if (m_windowAdapter == adapter)
    {
        m_windowAdapter = nullptr;
    }
}

int32_t TitleBar::HitTest(int32_t screenX, int32_t screenY, int32_t xamlRootScreenX, int32_t xamlRootScreenY)
{
    double scale = RasterizationScale();

    winrt::Point point{
        static_cast<float>((screenX - xamlRootScreenX) / scale),
        static_cast<float>((screenY - xamlRootScreenY) / scale)
    };

    auto titleBounds = GetTitleBarRootBounds();
    if (!ContainsPoint(titleBounds, point))
    {
        return hitTestNowhere;
    }

    for (auto const& iconRect : GetIconRects())
    {
        if (ContainsPoint(iconRect, point))
        {
            return hitTestSysMenu;
        }
    }

    UpdateInteractableElementsList();

    try
    {
        for (auto const& hitElement : winrt::VisualTreeHelper::FindElementsInHostCoordinates(point, *this, true))
        {
            for (auto const& element : m_interactableElementsList)
            {
                if (IsElementOrDescendantOf(hitElement, element))
                {
                    return hitTestClient;
                }
            }
        }
    }
    catch (...)
    {
    }

    for (auto const& element : m_interactableElementsList)
    {
        if (ContainsPoint(GetElementBounds(element), point))
        {
            return hitTestClient;
        }
    }

    return hitTestCaption;
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

winrt::Rect TitleBar::GetElementBounds(winrt::FrameworkElement const& element)
{
    if (!element)
    {
        return {};
    }

    const auto width = static_cast<float>(MaxLength(element.ActualWidth(), element.Width()));
    const auto height = static_cast<float>((std::max)(MaxLength(element.ActualHeight(), element.Height()), ValidLength(element.MinHeight())));

    try
    {
        winrt::UIElement rootContent{ nullptr };
        if (auto root = element.XamlRoot())
        {
            rootContent = root.Content();
        }

        return element.TransformToVisual(rootContent).TransformBounds({ 0.0f, 0.0f, width, height });
    }
    catch (...)
    {
        return { 0.0f, 0.0f, width, height };
    }
}

bool TitleBar::ContainsPoint(winrt::Rect const& bounds, winrt::Point const& point)
{
    return bounds.Width > 0 &&
        bounds.Height > 0 &&
        point.X >= bounds.X &&
        point.X < bounds.X + bounds.Width &&
        point.Y >= bounds.Y &&
        point.Y < bounds.Y + bounds.Height;
}

double TitleBar::ValidLength(double value)
{
    return std::isfinite(value) && value > 0.0 ? value : 0.0;
}

double TitleBar::MaxLength(double first, double second)
{
    return (std::max)(ValidLength(first), ValidLength(second));
}

bool TitleBar::IsElementOrDescendantOf(winrt::DependencyObject const& candidate, winrt::DependencyObject const& ancestor)
{
    for (auto current = candidate; current; current = winrt::VisualTreeHelper::GetParent(current))
    {
        if (current == ancestor)
        {
            return true;
        }
    }

    return false;
}

void TitleBar::UpdateAutoRefreshDragRegions()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    if (AutoRefreshDragRegions())
    {
        // Re-subscribe to LayoutUpdated if not already subscribed
        // (it may have been revoked by the one-shot unregister in OnContentLayoutUpdated).
        if (Content() != nullptr)
        {
            if (const auto content = Content().try_as<winrt::FrameworkElement>())
            {
                m_contentLayoutUpdatedRevoker = content.LayoutUpdated(winrt::auto_revoke, { this, &TitleBar::OnContentLayoutUpdated });
            }
        }

        // Recompute interactable elements now so drag regions are current immediately.
        // Note: UpdateDragRegion() is not called here because OnPropertyChanged already
        // calls it unconditionally after this method returns.
        UpdateInteractableElementsList();
    }
    else
    {
        // App opted out of automatic refresh — stop listening.
        m_contentLayoutUpdatedRevoker.revoke();
    }
}

void TitleBar::LoadBackButton()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    m_backButton.set(GetTemplateChildT<winrt::Button>(s_backButtonPartName, *this));

    if (const auto backButton = m_backButton.get())
    {
        m_backButtonClickRevoker = backButton.Click(winrt::auto_revoke, { this, &TitleBar::OnBackButtonClick });

        // Do localization for the back button
        if (winrt::AutomationProperties::GetName(backButton).empty())
        {
            const auto backButtonName = ResourceAccessor::GetLocalizedStringResource(SR_NavigationBackButtonName);
            winrt::AutomationProperties::SetName(backButton, backButtonName);
        }

        // Setup the tooltip for the back button
        const auto tooltip = winrt::ToolTip();
        const auto backButtonTooltipText = ResourceAccessor::GetLocalizedStringResource(SR_NavigationBackButtonToolTip);
        tooltip.Content(box_value(backButtonTooltipText));
        winrt::ToolTipService::SetToolTip(backButton, tooltip);
    }
}

void TitleBar::LoadPaneToggleButton()
{
    TITLEBAR_TRACE_VERBOSE(*this, TRACE_MSG_METH, METH_NAME, this);

    m_paneToggleButton.set(GetTemplateChildT<winrt::Button>(s_paneToggleButtonPartName, *this));

    if (const auto paneToggleButton = m_paneToggleButton.get())
    {
        m_paneToggleButtonClickRevoker = paneToggleButton.Click(winrt::auto_revoke, { this, &TitleBar::OnPaneToggleButtonClick });

        // Do localization for paneToggleButton
        if (winrt::AutomationProperties::GetName(paneToggleButton).empty())
        {
            const auto paneToggleButtonName = ResourceAccessor::GetLocalizedStringResource(SR_NavigationButtonToggleName);
            winrt::AutomationProperties::SetName(paneToggleButton, paneToggleButtonName);
        }

        // Setup the tooltip for the paneToggleButton
        const auto tooltip = winrt::ToolTip();
        tooltip.Content(box_value(winrt::AutomationProperties::GetName(paneToggleButton)));
        winrt::ToolTipService::SetToolTip(paneToggleButton, tooltip);
    }
}

void TitleBar::FindInteractableElements(const winrt::DependencyObject& element, bool parentIsDragRegion)
{
    if (!element)
    {
        return;
    }

    auto const uiElement = element.try_as<winrt::UIElement>();

    // All children from VisualTreeHelper should be UIElements; bail out if not.
    if (!uiElement)
    {
        return;
    }

    // Skip elements that are not visible or not hit-testable.
    // Note: UIElement.IsHitTestVisible() is a separate property and does NOT reflect Visibility.
    // We must check Visibility explicitly to skip Collapsed elements.
    if (uiElement.Visibility() != winrt::Visibility::Visible || !uiElement.IsHitTestVisible())
    {
        return;
    }

    bool currentIsDragRegion = parentIsDragRegion;

    // Check if IsDragRegion is explicitly set (non-null) on this element.
    // IReference<bool>: null = unset, false = clickable, true = draggable.
    auto const isDragRegion = winrt::TitleBar::GetIsDragRegion(uiElement);
    if (isDragRegion != nullptr)
    {
        if (!isDragRegion.Value())
        {
            // IsDragRegion=false: Add this entire element as interactable and stop recursing
            // into its children (the element's bounds cover all its internal elements).
            if (auto const fe = uiElement.try_as<winrt::FrameworkElement>())
            {
                TITLEBAR_TRACE_VERBOSE_DBG(*this, TRACE_MSG_METH_STR, METH_NAME, this,
                    fe.Name().empty() ? L"(element with IsDragRegion=false)" : fe.Name().c_str());
                m_interactableElementsList.push_back(fe);
            }
            return;
        }

        // IsDragRegion=true: This element is explicitly marked as a drag region.
        // If it's a Control, treat the entire control as draggable — don't recurse
        // into its template children. Only recurse for non-Control containers (e.g. Panel)
        // where children may override with IsDragRegion=false.
        if (uiElement.try_as<winrt::Control>())
        {
            TITLEBAR_TRACE_VERBOSE_DBG(*this, TRACE_MSG_METH_STR, METH_NAME, this, L"Control with IsDragRegion=true, skipping subtree");
            return;
        }

        TITLEBAR_TRACE_VERBOSE_DBG(*this, TRACE_MSG_METH_STR, METH_NAME, this, L"Element with IsDragRegion=true, recursing children");
        currentIsDragRegion = true;
    }

    // Check if this element is an interactive control (Button, TextBox, ComboBox, etc.)
    // Only apply auto-detection when not inside a parent with IsDragRegion=true.
    if (!currentIsDragRegion)
    {
        if (auto const control = uiElement.try_as<winrt::Control>())
        {
            if (control.IsEnabled())
            {
                // Add enabled control as interactable. Don't recurse into children —
                // the control's bounds already cover all its internal elements.
                TITLEBAR_TRACE_VERBOSE_DBG(*this, TRACE_MSG_METH_STR, METH_NAME, this,
                    control.Name().empty() ? L"(unnamed control)" : control.Name().c_str());
                m_interactableElementsList.push_back(control);
                return;
            }
            // Disabled controls: fall through to recurse into children,
            // propagating currentIsDragRegion to preserve ancestor intent.
        }
    }

    // Recursively process all children in the visual tree (for Panels, disabled controls, etc.)
    const auto childCount = winrt::VisualTreeHelper::GetChildrenCount(element);
    for (int i = 0; i < childCount; i++)
    {
        FindInteractableElements(winrt::VisualTreeHelper::GetChild(element, i), currentIsDragRegion);
    }
}
