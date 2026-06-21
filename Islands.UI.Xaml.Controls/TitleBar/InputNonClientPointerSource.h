#pragma once

#include "InputNonClientPointerSource.g.h"

namespace winrt::Islands::UI::Xaml::Controls::implementation
{

struct InputNonClientPointerSource : InputNonClientPointerSourceT<InputNonClientPointerSource>
{
    InputNonClientPointerSource() = default;

    void SetRegionRects(
        winrt::Islands::UI::Xaml::Controls::NonClientRegionKind regionKind,
        winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::Rect> const& rects);
    void ClearRegionRects(winrt::Islands::UI::Xaml::Controls::NonClientRegionKind regionKind);

    void SetRegionRectsInternal(
        winrt::Islands::UI::Xaml::Controls::NonClientRegionKind regionKind,
        std::vector<winrt::Windows::Foundation::Rect> rects);
    std::vector<winrt::Windows::Foundation::Rect> const& RegionRects(
        winrt::Islands::UI::Xaml::Controls::NonClientRegionKind regionKind) const;

private:
    std::vector<winrt::Windows::Foundation::Rect> m_passthroughRects;
    std::vector<winrt::Windows::Foundation::Rect> m_iconRects;
};

}

namespace winrt::Islands::UI::Xaml::Controls::factory_implementation
{

struct InputNonClientPointerSource : InputNonClientPointerSourceT<InputNonClientPointerSource, implementation::InputNonClientPointerSource>
{
};

}
