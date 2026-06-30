export module ixx.TitleBar.interop;

import std;
import inc.common;
import ixx.TitleBarWindowAdapter;

export namespace TitleBarImplementation
{
    void RegisterWindowAdapter(winrt::TitleBar const& titleBar, TitleBarWindowAdapter* adapter);
    void UnregisterWindowAdapter(winrt::TitleBar const& titleBar, TitleBarWindowAdapter* adapter);
    void SetWindowActive(winrt::TitleBar const& titleBar, bool active);
    void SetCaptionInsets(winrt::TitleBar const& titleBar, double left, double right);
    std::int32_t HitTest(winrt::TitleBar const& titleBar, std::int32_t screenX, std::int32_t screenY, std::int32_t xamlRootScreenX, std::int32_t xamlRootScreenY);
    winrt::Rect GetTitleBarRootBounds(winrt::TitleBar const& titleBar);
    double RasterizationScale(winrt::TitleBar const& titleBar);
    std::vector<winrt::Rect> GetPassthroughRects(winrt::TitleBar const& titleBar);
    std::vector<winrt::Rect> GetIconRects(winrt::TitleBar const& titleBar);
}
