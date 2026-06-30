import std;
import inc.common;
import ixx.AppWindowTitleBar;

#ifdef WINRT_EXPORT
#undef WINRT_EXPORT
#endif
#define WINRT_EXPORT

#include "AppWindowTitleBar.g.cpp"

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
    m_leftInset = (std::max)(0.0, value);
}

double AppWindowTitleBar::RightInset()
{
    return m_rightInset;
}

void AppWindowTitleBar::RightInset(double value)
{
    m_rightInset = (std::max)(0.0, value);
}
