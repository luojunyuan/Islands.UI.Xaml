module;
#include <unknwn.h>
#include <inspectable.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include "Primitives.ScrollViewTestHooks.g.h"

export module ixx.ScrollViewTestHooks;

import inc.common;
import ixx.ScrollView;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ScrollViewTestHooks :
    public winrt::Islands::UI::Xaml::Controls::Primitives::implementation::ScrollViewTestHooksT<ScrollViewTestHooks>
{
public:
    static com_ptr<ScrollViewTestHooks> GetGlobalTestHooks()
    {
        return s_testHooks;
    }

    static com_ptr<ScrollViewTestHooks> EnsureGlobalTestHooks();

    static winrt::IReference<bool> GetAutoHideScrollControllers(const winrt::ScrollView& scrollView);
    static void SetAutoHideScrollControllers(const winrt::ScrollView& scrollView, winrt::IReference<bool> value);

private:
    static com_ptr<ScrollViewTestHooks> s_testHooks;

    std::map<winrt::IScrollView, winrt::IReference<bool>> m_autoHideScrollControllersMap;
};


namespace winrt::Islands::UI::Xaml::Controls::Primitives::implementation { using ScrollViewTestHooks = ::ScrollViewTestHooks; }
}
