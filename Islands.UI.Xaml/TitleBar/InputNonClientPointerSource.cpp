import std;
import inc.common;
import ixx.InputNonClientPointerSource;

#ifdef WINRT_EXPORT
#undef WINRT_EXPORT
#endif
#define WINRT_EXPORT

#include "InputNonClientPointerSource.g.cpp"

void InputNonClientPointerSource::SetRegionRects(
    winrt::NonClientRegionKind regionKind,
    winrt::IIterable<winrt::Rect> const& rects)
{
    std::vector<winrt::Rect> values;
    for (auto const& rect : rects)
    {
        values.push_back(rect);
    }

    SetRegionRectsInternal(regionKind, std::move(values));
}

void InputNonClientPointerSource::ClearRegionRects(winrt::NonClientRegionKind regionKind)
{
    SetRegionRectsInternal(regionKind, {});
}

void InputNonClientPointerSource::SetRegionRectsInternal(
    winrt::NonClientRegionKind regionKind,
    std::vector<winrt::Rect> rects)
{
    if (regionKind == winrt::NonClientRegionKind::Icon)
    {
        m_iconRects = std::move(rects);
    }
    else
    {
        m_passthroughRects = std::move(rects);
    }
}

std::vector<winrt::Rect> const& InputNonClientPointerSource::RegionRects(winrt::NonClientRegionKind regionKind) const
{
    return regionKind == winrt::NonClientRegionKind::Icon ? m_iconRects : m_passthroughRects;
}
