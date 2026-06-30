import std;
import inc.common;
import ixx.AppWindowTitleBar;
import ixx.InputNonClientPointerSource;
import ixx.TitleBar.interop;
import ixx.TitleBarWindowAdapter;

#ifdef WINRT_EXPORT
#undef WINRT_EXPORT
#endif
#define WINRT_EXPORT

#include "TitleBarWindowAdapter.g.cpp"

namespace
{
    RECT ToWindowPixels(winrt::Rect const& rect, double scale, int32_t xamlRootScreenX, int32_t xamlRootScreenY, RECT const& targetWindowRect)
    {
        const auto left = static_cast<int>(std::floor(xamlRootScreenX + rect.X * scale - targetWindowRect.left));
        const auto top = static_cast<int>(std::floor(xamlRootScreenY + rect.Y * scale - targetWindowRect.top));
        const auto right = static_cast<int>(std::ceil(xamlRootScreenX + (rect.X + rect.Width) * scale - targetWindowRect.left));
        const auto bottom = static_cast<int>(std::ceil(xamlRootScreenY + (rect.Y + rect.Height) * scale - targetWindowRect.top));
        return { left, top, right, bottom };
    }

    bool IsEmptyRect(RECT const& rect)
    {
        return rect.right <= rect.left || rect.bottom <= rect.top;
    }

    bool AreRectsEqual(winrt::Rect const& first, winrt::Rect const& second)
    {
        return first.X == second.X &&
            first.Y == second.Y &&
            first.Width == second.Width &&
            first.Height == second.Height;
    }

    bool AreRegionRectsEqual(std::vector<winrt::Rect> const& first, std::vector<winrt::Rect> const& second)
    {
        if (first.size() != second.size())
        {
            return false;
        }

        for (size_t i = 0; i < first.size(); ++i)
        {
            if (!AreRectsEqual(first[i], second[i]))
            {
                return false;
            }
        }

        return true;
    }

    winrt::hstring GetWindowTitle(HWND hwnd)
    {
        if (!hwnd)
        {
            return {};
        }

        const int length = GetWindowTextLengthW(hwnd);
        if (length <= 0)
        {
            return {};
        }

        std::wstring title(static_cast<size_t>(length) + 1, L'\0');
        const int copied = GetWindowTextW(hwnd, title.data(), static_cast<int>(title.size()));
        if (copied <= 0)
        {
            return {};
        }

        title.resize(static_cast<size_t>(copied));
        return winrt::hstring{ title };
    }
}

TitleBarWindowAdapter::TitleBarWindowAdapter(winrt::TitleBar const& titleBar) :
    m_windowTitleBar(winrt::make<::AppWindowTitleBar>()),
    m_nonClientPointerSource(winrt::make<::InputNonClientPointerSource>())
{
    SetTitleBar(titleBar);
}

TitleBarWindowAdapter::~TitleBarWindowAdapter()
{
    if (m_titleBar)
    {
        TitleBarImplementation::UnregisterWindowAdapter(m_titleBar, this);
    }

    ResetWindowTitle(m_lastAppliedTitle);
    UnregisterTitleChanged();
}

int64_t TitleBarWindowAdapter::WindowHandle()
{
    return m_windowHandle;
}

void TitleBarWindowAdapter::WindowHandle(int64_t value)
{
    if (m_windowHandle != value)
    {
        ResetWindowTitle(m_lastAppliedTitle);
        m_windowHandle = value;
        m_defaultWindowTitle = {};
        m_lastAppliedTitle = {};
        m_hasDefaultWindowTitle = false;
    }

    SyncWindowTitle();
}

winrt::AppWindowTitleBar TitleBarWindowAdapter::WindowTitleBar()
{
    return m_windowTitleBar;
}

winrt::InputNonClientPointerSource TitleBarWindowAdapter::NonClientPointerSource()
{
    return m_nonClientPointerSource;
}

void TitleBarWindowAdapter::SetTitleBar(winrt::UIElement const& titleBar)
{
    if (m_titleBar)
    {
        TitleBarImplementation::UnregisterWindowAdapter(m_titleBar, this);
    }

    ResetWindowTitle(m_lastAppliedTitle);
    UnregisterTitleChanged();

    m_titleBarElement = titleBar;
    m_titleBar = titleBar.try_as<winrt::TitleBar>();
    m_lastObservedTitle = m_titleBar ? m_titleBar.Title() : winrt::hstring{};

    if (m_titleBar)
    {
        TitleBarImplementation::RegisterWindowAdapter(m_titleBar, this);

        m_titleChangedToken = m_titleBar.RegisterPropertyChangedCallback(
            winrt::TitleBar::TitleProperty(),
            [this](auto&&, auto&&)
            {
                OnTitleChanged();
            });
    }

    SyncWindowTitle();
    SyncNonClientRegions();
}

void TitleBarWindowAdapter::NotifyWindowActivated(bool active)
{
    if (m_titleBar)
    {
        TitleBarImplementation::SetWindowActive(m_titleBar, active);
    }
}

void TitleBarWindowAdapter::SetCaptionInsets(double left, double right)
{
    if (m_windowTitleBar)
    {
        m_windowTitleBar.LeftInset(left);
        m_windowTitleBar.RightInset(right);
    }

    if (m_titleBar)
    {
        TitleBarImplementation::SetCaptionInsets(m_titleBar, left, right);
    }
}

int32_t TitleBarWindowAdapter::HitTest(int32_t screenX, int32_t screenY, int32_t xamlRootScreenX, int32_t xamlRootScreenY)
{
    return m_titleBar ? TitleBarImplementation::HitTest(m_titleBar, screenX, screenY, xamlRootScreenX, xamlRootScreenY) : hitTestNowhere;
}

bool TitleBarWindowAdapter::ApplyTitleBarWindowRegion(int64_t titleBarWindowHandle, int32_t xamlRootScreenX, int32_t xamlRootScreenY)
{
    const HWND hwnd = reinterpret_cast<HWND>(titleBarWindowHandle);
    if (!hwnd)
    {
        m_hasTitleBarWindowRegionTarget = false;
        m_lastTitleBarWindowHandle = 0;
        return false;
    }

    m_hasTitleBarWindowRegionTarget = true;
    m_lastTitleBarWindowHandle = titleBarWindowHandle;
    m_lastXamlRootScreenX = xamlRootScreenX;
    m_lastXamlRootScreenY = xamlRootScreenY;

    if (!m_windowTitleBar || !m_windowTitleBar.ExtendsContentIntoTitleBar() || !m_titleBar)
    {
        SetWindowRgn(hwnd, nullptr, win32True);
        return false;
    }

    auto titleRect = TitleBarImplementation::GetTitleBarRootBounds(m_titleBar);
    if (titleRect.Width <= 0.0f || titleRect.Height <= 0.0f)
    {
        SetWindowRgn(hwnd, nullptr, win32True);
        return false;
    }

    m_isApplyingTitleBarWindowRegion = true;
    SyncNonClientRegions();
    m_isApplyingTitleBarWindowRegion = false;

    RECT targetWindowRect{};
    if (!getWindowRect(hwnd, &targetWindowRect))
    {
        return false;
    }

    const double scale = TitleBarImplementation::RasterizationScale(m_titleBar);
    RECT titleRegionRect = ToWindowPixels(titleRect, scale, xamlRootScreenX, xamlRootScreenY, targetWindowRect);
    if (IsEmptyRect(titleRegionRect))
    {
        SetWindowRgn(hwnd, nullptr, win32True);
        return false;
    }

    HRGN titleRegion = createRectRgn(titleRegionRect.left, titleRegionRect.top, titleRegionRect.right, titleRegionRect.bottom);
    if (!titleRegion)
    {
        return false;
    }

    auto sourceImpl = winrt::get_self<::InputNonClientPointerSource>(m_nonClientPointerSource);
    for (auto const& passthroughRect : sourceImpl->RegionRects(winrt::NonClientRegionKind::Passthrough))
    {
        RECT passthroughRegionRect = ToWindowPixels(passthroughRect, scale, xamlRootScreenX, xamlRootScreenY, targetWindowRect);
        if (IsEmptyRect(passthroughRegionRect))
        {
            continue;
        }

        HRGN passthroughRegion = createRectRgn(
            passthroughRegionRect.left,
            passthroughRegionRect.top,
            passthroughRegionRect.right,
            passthroughRegionRect.bottom);
        if (!passthroughRegion)
        {
            continue;
        }

        combineRgn(titleRegion, titleRegion, passthroughRegion, regionDiff);
        DeleteObject(passthroughRegion);
    }

    if (!SetWindowRgn(hwnd, titleRegion, win32True))
    {
        DeleteObject(titleRegion);
        return false;
    }

    return true;
}

winrt::event_token TitleBarWindowAdapter::NonClientRegionsChanged(winrt::TypedEventHandler<winrt::TitleBarWindowAdapter, winrt::IInspectable> const& value)
{
    return m_nonClientRegionsChangedEventSource.add(value);
}

void TitleBarWindowAdapter::NonClientRegionsChanged(winrt::event_token const& token)
{
    m_nonClientRegionsChangedEventSource.remove(token);
}

void TitleBarWindowAdapter::UnregisterTitleChanged()
{
    if (m_titleBar && m_titleChangedToken)
    {
        m_titleBar.UnregisterPropertyChangedCallback(winrt::TitleBar::TitleProperty(), m_titleChangedToken);
        m_titleChangedToken = 0;
    }
}

void TitleBarWindowAdapter::OnTitleChanged()
{
    if (!m_titleBar)
    {
        return;
    }

    const auto oldTitle = m_lastObservedTitle;
    const auto newTitle = m_titleBar.Title();
    m_lastObservedTitle = newTitle;

    if (!oldTitle.empty() && newTitle.empty())
    {
        ResetWindowTitle(oldTitle);
    }
    else if (!newTitle.empty())
    {
        ApplyWindowTitle(newTitle);
    }
}

void TitleBarWindowAdapter::SyncWindowTitle()
{
    if (!m_titleBar)
    {
        return;
    }

    const auto title = m_titleBar.Title();
    m_lastObservedTitle = title;

    if (!title.empty())
    {
        ApplyWindowTitle(title);
    }
}

void TitleBarWindowAdapter::EnsureDefaultWindowTitle()
{
    if (!m_hasDefaultWindowTitle && m_windowHandle)
    {
        m_defaultWindowTitle = GetWindowTitle(reinterpret_cast<HWND>(m_windowHandle));
        m_hasDefaultWindowTitle = true;
    }
}

void TitleBarWindowAdapter::ApplyWindowTitle(winrt::hstring const& title)
{
    if (!m_windowHandle || title.empty())
    {
        return;
    }

    EnsureDefaultWindowTitle();

    const HWND hwnd = reinterpret_cast<HWND>(m_windowHandle);
    if (GetWindowTitle(hwnd) != title)
    {
        setWindowText(hwnd, title.c_str());
    }

    m_lastAppliedTitle = title;
}

void TitleBarWindowAdapter::ResetWindowTitle(winrt::hstring const& lastAppliedTitle)
{
    if (!m_windowHandle || lastAppliedTitle.empty() || !m_hasDefaultWindowTitle)
    {
        return;
    }

    const HWND hwnd = reinterpret_cast<HWND>(m_windowHandle);
    if (GetWindowTitle(hwnd) == lastAppliedTitle)
    {
        setWindowText(hwnd, m_defaultWindowTitle.c_str());
    }

    m_lastAppliedTitle = {};
}

void TitleBarWindowAdapter::NotifyNonClientRegionsChanged()
{
    m_nonClientRegionsChangedEventSource(*this, nullptr);

    if (!m_isApplyingTitleBarWindowRegion)
    {
        ReapplyCachedTitleBarWindowRegion();
    }
}

void TitleBarWindowAdapter::ReapplyCachedTitleBarWindowRegion()
{
    if (!m_hasTitleBarWindowRegionTarget || !m_lastTitleBarWindowHandle)
    {
        return;
    }

    ApplyTitleBarWindowRegion(m_lastTitleBarWindowHandle, m_lastXamlRootScreenX, m_lastXamlRootScreenY);
}

void TitleBarWindowAdapter::SyncNonClientRegions()
{
    if (!m_nonClientPointerSource)
    {
        return;
    }

    auto sourceImpl = winrt::get_self<::InputNonClientPointerSource>(m_nonClientPointerSource);
    if (!m_titleBar)
    {
        const bool changed =
            !AreRectsEqual(m_titleBarRootBounds, {}) ||
            !sourceImpl->RegionRects(winrt::NonClientRegionKind::Passthrough).empty() ||
            !sourceImpl->RegionRects(winrt::NonClientRegionKind::Icon).empty();

        if (changed)
        {
            m_titleBarRootBounds = {};
            sourceImpl->ClearRegionRects(winrt::NonClientRegionKind::Passthrough);
            sourceImpl->ClearRegionRects(winrt::NonClientRegionKind::Icon);
            NotifyNonClientRegionsChanged();
        }

        return;
    }

    auto titleBarRootBounds = TitleBarImplementation::GetTitleBarRootBounds(m_titleBar);
    auto passthroughRects = TitleBarImplementation::GetPassthroughRects(m_titleBar);
    auto iconRects = TitleBarImplementation::GetIconRects(m_titleBar);
    const bool changed =
        !AreRectsEqual(m_titleBarRootBounds, titleBarRootBounds) ||
        !AreRegionRectsEqual(sourceImpl->RegionRects(winrt::NonClientRegionKind::Passthrough), passthroughRects) ||
        !AreRegionRectsEqual(sourceImpl->RegionRects(winrt::NonClientRegionKind::Icon), iconRects);

    if (!changed)
    {
        return;
    }

    m_titleBarRootBounds = titleBarRootBounds;
    sourceImpl->SetRegionRectsInternal(winrt::NonClientRegionKind::Passthrough, std::move(passthroughRects));
    sourceImpl->SetRegionRectsInternal(winrt::NonClientRegionKind::Icon, std::move(iconRects));
    NotifyNonClientRegionsChanged();
}
