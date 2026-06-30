module;
#include "TitleBarTemplateSettings.g.h"

export module ixx.TitleBarTemplateSettings;

import inc.common;
import ixx.TitleBarTemplateSettings.properties;

export
{
class TitleBarTemplateSettings :
    public winrt::implementation::TitleBarTemplateSettingsT<TitleBarTemplateSettings>,
    public TitleBarTemplateSettingsProperties
{
public:
    TitleBarTemplateSettings();
};

namespace winrt::Islands::UI::Xaml::Controls::implementation
{
    using TitleBarTemplateSettings = ::TitleBarTemplateSettings;
}
}
