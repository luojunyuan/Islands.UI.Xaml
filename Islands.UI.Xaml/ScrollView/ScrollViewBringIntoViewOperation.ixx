export module ixx.ScrollViewBringIntoViewOperation;

import inc.common;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.


class ScrollViewBringIntoViewOperation
{
public:
    ScrollViewBringIntoViewOperation(winrt::UIElement const& targetElement, bool cancelBringIntoView);
    ~ScrollViewBringIntoViewOperation();

    bool HasMaxTicksCount() const;
    winrt::UIElement TargetElement() const;
    std::int8_t TicksCount() const;
    std::int8_t TickOperation();

    bool ShouldCancelBringIntoView()
    {
        return m_cancelBringIntoView;
    }

private:
    // Number of UI thread ticks allowed before this expected bring-into-view operation is no
    // longer expected and removed from the ScrollView's m_bringIntoViewOperations list.
    static constexpr std::int8_t s_maxTicksCount{ 3 };

    std::int8_t m_ticksCount{ 0 };
    winrt::weak_ref<winrt::UIElement> m_targetElement;
    bool m_cancelBringIntoView;
};


}
