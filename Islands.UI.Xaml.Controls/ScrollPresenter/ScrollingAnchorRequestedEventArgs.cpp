// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <SDKDDKVer.h>

#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#undef GetCurrentTime

#include <unknwn.h>
#include <inspectable.h>
#include <restrictederrorinfo.h>
#include <hstring.h>
#include <windows.ui.xaml.hosting.referencetracker.h>

#include "inc/CppWinRTIncludes.h"
#include "inc/BuildMacros.h"

#ifndef MUX_ASSERT
#define MUX_ASSERT(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_NOASSUME
#define MUX_ASSERT_NOASSUME(condition) assert(condition)
#endif

#ifndef MUX_ASSERT_MSG
#define MUX_ASSERT_MSG(condition, message) assert((condition) && (message))
#endif

#include "common.h"
#include "Vector.h"
#include "ScrollPresenter.h"
#include "ScrollPresenterTrace.h"
#include "ScrollingAnchorRequestedEventArgs.h"

ScrollingAnchorRequestedEventArgs::ScrollingAnchorRequestedEventArgs(const winrt::Islands::UI::Xaml::Controls::Primitives::ScrollPresenter& scrollPresenter)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR, METH_NAME, this, scrollPresenter);

    m_scrollPresenter.set(scrollPresenter);
}

ScrollingAnchorRequestedEventArgs::~ScrollingAnchorRequestedEventArgs()
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH, METH_NAME, this);
}

#pragma region IScrollingAnchorRequestedEventArgs

winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::UIElement> ScrollingAnchorRequestedEventArgs::AnchorCandidates()
{
    return m_anchorCandidates.get();
}

winrt::Windows::UI::Xaml::UIElement ScrollingAnchorRequestedEventArgs::AnchorElement()
{
    return m_anchorElement.get();
}

void ScrollingAnchorRequestedEventArgs::AnchorElement(winrt::Windows::UI::Xaml::UIElement const& value)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR, METH_NAME, this, value);

    const winrt::Windows::UI::Xaml::UIElement& anchorElement{ value };
    winrt::com_ptr<ScrollPresenter> scrollPresenter = winrt::get_self<ScrollPresenter>(m_scrollPresenter.get())->get_strong();

    if (!anchorElement || scrollPresenter->IsElementValidAnchor(anchorElement))
    {
        m_anchorElement.set(anchorElement);
    }
    else
    {
        throw winrt::hresult_error(E_INVALIDARG);
    }
}

#pragma endregion

winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::UIElement> ScrollingAnchorRequestedEventArgs::GetAnchorCandidates()
{
    return m_anchorCandidates.get();
}

void ScrollingAnchorRequestedEventArgs::SetAnchorCandidates(const std::vector<tracker_ref<winrt::Windows::UI::Xaml::UIElement>>& anchorCandidates)
{
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::UIElement> anchorCandidatesTmp = winrt::make<Vector<winrt::Windows::UI::Xaml::UIElement, MakeVectorParam<VectorFlag::DependencyObjectBase>()>>();
        
    for (tracker_ref<winrt::Windows::UI::Xaml::UIElement> anchorCandidate : anchorCandidates)
    {
        anchorCandidatesTmp.Append(anchorCandidate.get());
    }
    m_anchorCandidates.set(anchorCandidatesTmp);
}

winrt::Windows::UI::Xaml::UIElement ScrollingAnchorRequestedEventArgs::GetAnchorElement() const
{
    return m_anchorElement.get();
}

void ScrollingAnchorRequestedEventArgs::SetAnchorElement(const winrt::Windows::UI::Xaml::UIElement& anchorElement)
{
    m_anchorElement.set(anchorElement);
}
