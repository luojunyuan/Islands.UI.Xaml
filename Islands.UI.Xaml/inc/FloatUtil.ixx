// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

export module inc.FloatUtil;

import std;

export
{

class FloatUtil
{
public:
    // Represents a value that is not a number (NaN).
    inline static const float NaN{ std::numeric_limits<float>::quiet_NaN() };
};
}
