module;

#include "InputNonClientPointerSource.g.h"

export module ixx.InputNonClientPointerSource;

import std;
import inc.common;

export
{
class InputNonClientPointerSource :
    public winrt::implementation::InputNonClientPointerSourceT<InputNonClientPointerSource>
{
public:
    InputNonClientPointerSource() = default;

    void SetRegionRects(
        winrt::NonClientRegionKind regionKind,
        winrt::IIterable<winrt::Rect> const& rects);
    void ClearRegionRects(winrt::NonClientRegionKind regionKind);

    void SetRegionRectsInternal(winrt::NonClientRegionKind regionKind, std::vector<winrt::Rect> rects);
    std::vector<winrt::Rect> const& RegionRects(winrt::NonClientRegionKind regionKind) const;

private:
    std::vector<winrt::Rect> m_passthroughRects;
    std::vector<winrt::Rect> m_iconRects;
};

namespace winrt::Islands::UI::Xaml::Controls::implementation
{
    using InputNonClientPointerSource = ::InputNonClientPointerSource;
}

namespace winrt::Islands::UI::Xaml::Controls::factory_implementation
{
    struct InputNonClientPointerSource : InputNonClientPointerSourceT<InputNonClientPointerSource, implementation::InputNonClientPointerSource>
    {
    };
}
}
