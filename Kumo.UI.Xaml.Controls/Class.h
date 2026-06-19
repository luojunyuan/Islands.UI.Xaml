#pragma once

#include "Class.g.h"

namespace winrt::Kumo_UI_Xaml_Controls::implementation
{
    struct Class : ClassT<Class>
    {
        Class() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::Kumo_UI_Xaml_Controls::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
