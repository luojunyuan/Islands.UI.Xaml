#pragma once

#include "AppWindowTitleBar.g.h"

namespace winrt::Islands::UI::Xaml::Controls::implementation
{

struct AppWindowTitleBar : AppWindowTitleBarT<AppWindowTitleBar>
{
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

}

namespace winrt::Islands::UI::Xaml::Controls::factory_implementation
{

struct AppWindowTitleBar : AppWindowTitleBarT<AppWindowTitleBar, implementation::AppWindowTitleBar>
{
};

}
