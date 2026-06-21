#include "pch.h"
#include "InputNonClientPointerSource.h"
#if __has_include("InputNonClientPointerSource.g.cpp")
#include "InputNonClientPointerSource.g.cpp"
#endif

namespace winrt::Islands::UI::Xaml::Controls::implementation
{

void InputNonClientPointerSource::SetRegionRects(
    winrt::Islands::UI::Xaml::Controls::NonClientRegionKind regionKind,
    winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::Rect> const& rects)
{
    std::vector<winrt::Windows::Foundation::Rect> values;
    for (auto const& rect : rects)
    {
        values.push_back(rect);
    }

    SetRegionRectsInternal(regionKind, std::move(values));
}

void InputNonClientPointerSource::ClearRegionRects(winrt::Islands::UI::Xaml::Controls::NonClientRegionKind regionKind)
{
    SetRegionRectsInternal(regionKind, {});
}

void InputNonClientPointerSource::SetRegionRectsInternal(
    winrt::Islands::UI::Xaml::Controls::NonClientRegionKind regionKind,
    std::vector<winrt::Windows::Foundation::Rect> rects)
{
    if (regionKind == winrt::Islands::UI::Xaml::Controls::NonClientRegionKind::Icon)
    {
        m_iconRects = std::move(rects);
    }
    else
    {
        m_passthroughRects = std::move(rects);
    }
}

std::vector<winrt::Windows::Foundation::Rect> const& InputNonClientPointerSource::RegionRects(
    winrt::Islands::UI::Xaml::Controls::NonClientRegionKind regionKind) const
{
    return regionKind == winrt::Islands::UI::Xaml::Controls::NonClientRegionKind::Icon ?
        m_iconRects :
        m_passthroughRects;
}

}
