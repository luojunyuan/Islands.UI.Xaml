#include "pch.h"
#include "AppWindowTitleBar.h"
#if __has_include("AppWindowTitleBar.g.cpp")
#include "AppWindowTitleBar.g.cpp"
#endif

namespace winrt::Islands::UI::Xaml::Controls::implementation
{

bool AppWindowTitleBar::ExtendsContentIntoTitleBar()
{
    return m_extendsContentIntoTitleBar;
}

void AppWindowTitleBar::ExtendsContentIntoTitleBar(bool value)
{
    m_extendsContentIntoTitleBar = value;
}

double AppWindowTitleBar::LeftInset()
{
    return m_leftInset;
}

void AppWindowTitleBar::LeftInset(double value)
{
    m_leftInset = std::max(0.0, value);
}

double AppWindowTitleBar::RightInset()
{
    return m_rightInset;
}

void AppWindowTitleBar::RightInset(double value)
{
    m_rightInset = std::max(0.0, value);
}

}
