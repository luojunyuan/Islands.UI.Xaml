module;
#include "TitleBarWindowAdapter.g.h"

export module ixx.TitleBarWindowAdapter;

import inc.common;
import ixx.AppWindowTitleBar;
import ixx.InputNonClientPointerSource;

export
{
class TitleBarWindowAdapter :
    public winrt::implementation::TitleBarWindowAdapterT<TitleBarWindowAdapter>
{
public:
    TitleBarWindowAdapter(winrt::TitleBar const& titleBar);
    ~TitleBarWindowAdapter();

    int64_t WindowHandle();
    void WindowHandle(int64_t value);
    winrt::AppWindowTitleBar WindowTitleBar();
    winrt::InputNonClientPointerSource NonClientPointerSource();

    void SetTitleBar(winrt::UIElement const& titleBar);
    void NotifyWindowActivated(bool active);
    void SetCaptionInsets(double left, double right);
    int32_t HitTest(int32_t screenX, int32_t screenY, int32_t xamlRootScreenX, int32_t xamlRootScreenY);
    bool ApplyTitleBarWindowRegion(int64_t titleBarWindowHandle, int32_t xamlRootScreenX, int32_t xamlRootScreenY);
    winrt::event_token NonClientRegionsChanged(winrt::TypedEventHandler<winrt::TitleBarWindowAdapter, winrt::IInspectable> const& value);
    void NonClientRegionsChanged(winrt::event_token const& token);
    void SyncNonClientRegions();

private:
    void UnregisterTitleChanged();
    void OnTitleChanged();
    void SyncWindowTitle();
    void EnsureDefaultWindowTitle();
    void ApplyWindowTitle(winrt::hstring const& title);
    void ResetWindowTitle(winrt::hstring const& lastAppliedTitle);
    void NotifyNonClientRegionsChanged();
    void ReapplyCachedTitleBarWindowRegion();

    winrt::UIElement m_titleBarElement{ nullptr };
    winrt::TitleBar m_titleBar{ nullptr };
    winrt::AppWindowTitleBar m_windowTitleBar{ nullptr };
    winrt::InputNonClientPointerSource m_nonClientPointerSource{ nullptr };
    ::event<winrt::TypedEventHandler<winrt::TitleBarWindowAdapter, winrt::IInspectable>> m_nonClientRegionsChangedEventSource;
    winrt::Rect m_titleBarRootBounds{};
    winrt::hstring m_defaultWindowTitle{};
    winrt::hstring m_lastObservedTitle{};
    winrt::hstring m_lastAppliedTitle{};
    int64_t m_windowHandle{};
    int64_t m_lastTitleBarWindowHandle{};
    int64_t m_titleChangedToken{};
    int32_t m_lastXamlRootScreenX{};
    int32_t m_lastXamlRootScreenY{};
    bool m_hasDefaultWindowTitle{};
    bool m_hasTitleBarWindowRegionTarget{};
    bool m_isApplyingTitleBarWindowRegion{};
};

namespace winrt::Islands::UI::Xaml::Controls::implementation
{
    using TitleBarWindowAdapter = ::TitleBarWindowAdapter;
}

namespace winrt::Islands::UI::Xaml::Controls::factory_implementation
{
    struct TitleBarWindowAdapter : TitleBarWindowAdapterT<TitleBarWindowAdapter, implementation::TitleBarWindowAdapter>
    {
    };
}
}
