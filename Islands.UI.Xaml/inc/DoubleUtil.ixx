// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

export module inc.DoubleUtil;

import std;

export
{

class DoubleUtil
{
public:
    // Represents a value that is not a number (NaN).
    inline static const double NaN{ std::numeric_limits<double>::quiet_NaN() };
};


}
