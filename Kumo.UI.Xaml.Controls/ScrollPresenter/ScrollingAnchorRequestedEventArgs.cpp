// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#define KUMO_USE_IMPORT_STD 1
#define KUMO_DEFER_PREAMBLE_USINGS 1
#include "KumoPreamble.ixx"
import std;
import winrt_base;
import winrt;
#include "KumoPostImports.ixx"
#include "common.ixx"
#include "Vector.ixx"
#include "ScrollPresenter.ixx"
#include "ScrollPresenterTrace.ixx"
#include "ScrollingAnchorRequestedEventArgs.ixx"

ScrollingAnchorRequestedEventArgs::ScrollingAnchorRequestedEventArgs(const winrt::ScrollPresenter& scrollPresenter)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR, METH_NAME, this, scrollPresenter);

    m_scrollPresenter.set(scrollPresenter);
}

#pragma region IScrollingAnchorRequestedEventArgs

winrt::IVector<winrt::UIElement> ScrollingAnchorRequestedEventArgs::AnchorCandidates()
{
    return m_anchorCandidates.get();
}

winrt::UIElement ScrollingAnchorRequestedEventArgs::AnchorElement()
{
    return m_anchorElement.get();
}

void ScrollingAnchorRequestedEventArgs::AnchorElement(winrt::UIElement const& value)
{
    SCROLLPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR, METH_NAME, this, value);

    const winrt::UIElement& anchorElement{ value };
    com_ptr<ScrollPresenter> scrollPresenter = winrt::get_self<ScrollPresenter>(m_scrollPresenter.get())->get_strong();

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

winrt::IVector<winrt::UIElement> ScrollingAnchorRequestedEventArgs::GetAnchorCandidates()
{
    return m_anchorCandidates.get();
}

void ScrollingAnchorRequestedEventArgs::SetAnchorCandidates(const std::vector<tracker_ref<winrt::UIElement>>& anchorCandidates)
{
    winrt::IVector<winrt::UIElement> anchorCandidatesTmp = winrt::make<Vector<winrt::UIElement, MakeVectorParam<VectorFlag::DependencyObjectBase>()>>();
        
    for (tracker_ref<winrt::UIElement> anchorCandidate : anchorCandidates)
    {
        anchorCandidatesTmp.Append(anchorCandidate.get());
    }
    m_anchorCandidates.set(anchorCandidatesTmp);
}

winrt::UIElement ScrollingAnchorRequestedEventArgs::GetAnchorElement() const
{
    return m_anchorElement.get();
}

void ScrollingAnchorRequestedEventArgs::SetAnchorElement(const winrt::UIElement& anchorElement)
{
    m_anchorElement.set(anchorElement);
}
