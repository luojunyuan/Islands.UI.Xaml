#include <windows.h>

import std;
import winrt_base;
import winrt.Windows.Foundation;
import winrt.Windows.Foundation.Collections;
import winrt.Windows.UI.Xaml;
import winrt.Windows.UI.Xaml.Automation.Peers;
import winrt.Windows.UI.Xaml.Controls;
import winrt.Microsoft.UI.Xaml.Controls;
import winrt.Islands.UI.Xaml.Controls;

namespace winrt
{
namespace xaml = Windows::UI::Xaml;
namespace xaml_peers = Windows::UI::Xaml::Automation::Peers;
namespace xaml_controls = Windows::UI::Xaml::Controls;
namespace muxc = Microsoft::UI::Xaml::Controls;
}

using namespace std::string_view_literals;

#define WINRT_IMPORT_MODULE
#include "TitleBar.h"
#include "AppWindowTitleBar.h"
#include "InputNonClientPointerSource.h"
#include "TitleBarWindowAdapter.h"
#undef WINRT_IMPORT_MODULE

#if __has_include("TitleBarWindowAdapter.g.cpp")
#include "TitleBarWindowAdapter.g.cpp"
#endif

namespace winrt::Islands::UI::Xaml::Controls::implementation
{
namespace
{
    RECT ToWindowPixels(
        winrt::Windows::Foundation::Rect const& rect,
        double scale,
        int32_t xamlRootScreenX,
        int32_t xamlRootScreenY,
        RECT const& targetWindowRect)
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

TitleBarWindowAdapter::TitleBarWindowAdapter(winrt::Islands::UI::Xaml::Controls::TitleBar const& titleBar) :
    m_windowTitleBar(winrt::make<AppWindowTitleBar>()),
    m_nonClientPointerSource(winrt::make<InputNonClientPointerSource>())
{
    SetTitleBar(titleBar);
}

TitleBarWindowAdapter::~TitleBarWindowAdapter()
{
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

winrt::Islands::UI::Xaml::Controls::AppWindowTitleBar TitleBarWindowAdapter::WindowTitleBar()
{
    return m_windowTitleBar;
}

winrt::Islands::UI::Xaml::Controls::InputNonClientPointerSource TitleBarWindowAdapter::NonClientPointerSource()
{
    return m_nonClientPointerSource;
}

void TitleBarWindowAdapter::SetTitleBar(winrt::xaml::UIElement const& titleBar)
{
    ResetWindowTitle(m_lastAppliedTitle);
    UnregisterTitleChanged();

    m_titleBarElement = titleBar;
    m_titleBar = titleBar.try_as<winrt::Islands::UI::Xaml::Controls::TitleBar>();
    m_lastObservedTitle = m_titleBar ? m_titleBar.Title() : winrt::hstring{};

    if (m_titleBar)
    {
        m_titleChangedToken = m_titleBar.RegisterPropertyChangedCallback(
            winrt::Islands::UI::Xaml::Controls::TitleBar::TitleProperty(),
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
        winrt::get_self<TitleBar>(m_titleBar)->SetWindowActive(active);
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
        winrt::get_self<TitleBar>(m_titleBar)->SetCaptionInsets(left, right);
    }
}

int32_t TitleBarWindowAdapter::HitTest(int32_t screenX, int32_t screenY, int32_t xamlRootScreenX, int32_t xamlRootScreenY)
{
    if (!m_titleBar)
    {
        return HTNOWHERE;
    }

    return winrt::get_self<TitleBar>(m_titleBar)->HitTest(screenX, screenY, xamlRootScreenX, xamlRootScreenY);
}

bool TitleBarWindowAdapter::ApplyTitleBarWindowRegion(int64_t titleBarWindowHandle, int32_t xamlRootScreenX, int32_t xamlRootScreenY)
{
    const HWND hwnd = reinterpret_cast<HWND>(titleBarWindowHandle);
    if (!hwnd)
    {
        return false;
    }

    if (!m_windowTitleBar || !m_windowTitleBar.ExtendsContentIntoTitleBar() || !m_titleBar)
    {
        SetWindowRgn(hwnd, nullptr, TRUE);
        return false;
    }

    auto titleBarImpl = winrt::get_self<TitleBar>(m_titleBar);
    auto titleRect = titleBarImpl->GetTitleBarRootBounds();
    if (titleRect.Width <= 0.0f || titleRect.Height <= 0.0f)
    {
        SetWindowRgn(hwnd, nullptr, TRUE);
        return false;
    }

    SyncNonClientRegions();

    RECT targetWindowRect{};
    if (!GetWindowRect(hwnd, &targetWindowRect))
    {
        return false;
    }

    const double scale = titleBarImpl->RasterizationScale();
    RECT titleRegionRect = ToWindowPixels(titleRect, scale, xamlRootScreenX, xamlRootScreenY, targetWindowRect);
    if (IsEmptyRect(titleRegionRect))
    {
        SetWindowRgn(hwnd, nullptr, TRUE);
        return false;
    }

    HRGN titleRegion = CreateRectRgn(titleRegionRect.left, titleRegionRect.top, titleRegionRect.right, titleRegionRect.bottom);
    if (!titleRegion)
    {
        return false;
    }

    auto sourceImpl = winrt::get_self<InputNonClientPointerSource>(m_nonClientPointerSource);
    for (auto const& passthroughRect : sourceImpl->RegionRects(winrt::Islands::UI::Xaml::Controls::NonClientRegionKind::Passthrough))
    {
        RECT passthroughRegionRect = ToWindowPixels(passthroughRect, scale, xamlRootScreenX, xamlRootScreenY, targetWindowRect);
        if (IsEmptyRect(passthroughRegionRect))
        {
            continue;
        }

        HRGN passthroughRegion = CreateRectRgn(
            passthroughRegionRect.left,
            passthroughRegionRect.top,
            passthroughRegionRect.right,
            passthroughRegionRect.bottom);
        if (!passthroughRegion)
        {
            continue;
        }

        CombineRgn(titleRegion, titleRegion, passthroughRegion, RGN_DIFF);
        DeleteObject(passthroughRegion);
    }

    if (!SetWindowRgn(hwnd, titleRegion, TRUE))
    {
        DeleteObject(titleRegion);
        return false;
    }

    return true;
}

void TitleBarWindowAdapter::UnregisterTitleChanged()
{
    if (m_titleBar && m_titleChangedToken)
    {
        m_titleBar.UnregisterPropertyChangedCallback(
            winrt::Islands::UI::Xaml::Controls::TitleBar::TitleProperty(),
            m_titleChangedToken);
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
        SetWindowTextW(hwnd, title.c_str());
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
        SetWindowTextW(hwnd, m_defaultWindowTitle.c_str());
    }

    m_lastAppliedTitle = {};
}

void TitleBarWindowAdapter::SyncNonClientRegions()
{
    if (!m_nonClientPointerSource)
    {
        return;
    }

    auto sourceImpl = winrt::get_self<InputNonClientPointerSource>(m_nonClientPointerSource);
    if (!m_titleBar)
    {
        sourceImpl->ClearRegionRects(winrt::Islands::UI::Xaml::Controls::NonClientRegionKind::Passthrough);
        sourceImpl->ClearRegionRects(winrt::Islands::UI::Xaml::Controls::NonClientRegionKind::Icon);
        return;
    }

    sourceImpl->SetRegionRectsInternal(
        winrt::Islands::UI::Xaml::Controls::NonClientRegionKind::Passthrough,
        winrt::get_self<TitleBar>(m_titleBar)->GetPassthroughRects());
    sourceImpl->SetRegionRectsInternal(
        winrt::Islands::UI::Xaml::Controls::NonClientRegionKind::Icon,
        winrt::get_self<TitleBar>(m_titleBar)->GetIconRects());
}

}
