export module ixx.ZoomFactorChange;

import inc.common;
import ixx.ViewChange;
import std;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.



class ZoomFactorChange : public ViewChange
{
public:
    ZoomFactorChange(
        float zoomFactor,
        winrt::IReference<winrt::float2> centerPoint,
        ScrollPresenterViewKind zoomFactorKind,
        winrt::IInspectable const& options);
    ~ZoomFactorChange();

    float ZoomFactor() const
    {
        return m_zoomFactor;
    }

    winrt::IReference<winrt::float2> CenterPoint() const
    {
        return m_centerPoint;
    }

private:
    float m_zoomFactor{};
    winrt::IReference<winrt::float2> m_centerPoint{};
};


}
