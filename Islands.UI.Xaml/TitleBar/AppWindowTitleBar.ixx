module;

#include "AppWindowTitleBar.g.h"

export module ixx.AppWindowTitleBar;

import std;
import inc.common;

export
{
class AppWindowTitleBar :
    public winrt::implementation::AppWindowTitleBarT<AppWindowTitleBar>
{
public:
    AppWindowTitleBar() = default;

    bool ExtendsContentIntoTitleBar();
    void ExtendsContentIntoTitleBar(bool value);

    double LeftInset();
    void LeftInset(double value);

    double RightInset();
    void RightInset(double value);

private:
    bool m_extendsContentIntoTitleBar{};
    double m_leftInset{};
    double m_rightInset{};
};

namespace winrt::Islands::UI::Xaml::Controls::implementation
{
    using AppWindowTitleBar = ::AppWindowTitleBar;
}

namespace winrt::Islands::UI::Xaml::Controls::factory_implementation
{
    struct AppWindowTitleBar : AppWindowTitleBarT<AppWindowTitleBar, implementation::AppWindowTitleBar>
    {
    };
}
}
