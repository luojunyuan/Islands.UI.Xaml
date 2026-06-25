// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "CppBaseIncludes.h"

import CppWinRTModules;
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
