#pragma once
// XamlCompiler-generated .cpp files always include pch.h even though this
// project sets PrecompiledHeader=NotUsing. Use it as the generated-code module
// bridge: make the generated STL/C++WinRT includes empty, import the modules,
// then include the local control implementation headers that XamlTypeInfo needs.

#ifndef WINRT_IMPORT_MODULE
#define WINRT_IMPORT_MODULE
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <SDKDDKVer.h>
#include <unknwn.h>
#include <inspectable.h>
#include <Windows.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include <assert.h>

#ifndef __unknwn_h__
#define __unknwn_h__
#endif
#ifndef __RPC_H__
#define __RPC_H__
#endif
#ifndef __RPCNDR_H__
#define __RPCNDR_H__
#endif
#ifndef _INC_WINAPIFAMILY
#define _INC_WINAPIFAMILY
#endif
#ifndef _INC_WINPACKAGEFAMILY
#define _INC_WINPACKAGEFAMILY
#endif
#ifndef _OLE2_H_
#define _OLE2_H_
#endif
#ifndef _INC_WINDOWS
#define _INC_WINDOWS
#endif
#ifndef _INC_SDKDDKVER
#define _INC_SDKDDKVER
#endif

#undef _STL_COMPILER_PREPROCESSOR
#define _STL_COMPILER_PREPROCESSOR 0

import std;
import winrt_base;
import winrt.Windows.Foundation;
import winrt.Windows.Foundation.Collections;
import winrt.Windows.Foundation.Numerics;
import winrt.Windows.ApplicationModel.Core;
import winrt.Windows.Graphics;
import winrt.Windows.Storage.Streams;
import winrt.Windows.System;
import winrt.Windows.UI;
import winrt.Windows.UI.Composition;
import winrt.Windows.UI.Text;
import winrt.Windows.UI.Xaml;
import winrt.Windows.UI.Xaml.Automation;
import winrt.Windows.UI.Xaml.Automation.Peers;
import winrt.Windows.UI.Xaml.Controls;
import winrt.Windows.UI.Xaml.Controls.Primitives;
import winrt.Windows.UI.Xaml.Data;
import winrt.Windows.UI.Xaml.Input;
import winrt.Windows.UI.Xaml.Interop;
import winrt.Windows.UI.Xaml.Markup;
import winrt.Windows.UI.Xaml.Media;
import winrt.Microsoft.UI.Xaml.Controls;
import winrt.Microsoft.UI.Xaml.Controls.AnimatedVisuals;
import winrt.Microsoft.UI.Xaml.XamlTypeInfo;
import winrt.Islands.UI.Xaml.Controls;
import winrt.Islands.UI.Xaml.Controls.Primitives;
import winrt.Islands.UI.Xaml.Automation.Peers;
import inc.win32;

#undef GetCurrentTime

#ifndef MUX_ASSERT
#define MUX_ASSERT(condition) assert(condition)
#endif

namespace winrt::Islands::UI::Xaml::Controls
{
    namespace implementation {}
    namespace factory_implementation {}
}

namespace winrt::Islands::UI::Xaml::Controls::Primitives
{
    namespace implementation {}
    namespace factory_implementation {}
}

namespace winrt::Islands::UI::Xaml::Automation::Peers
{
    namespace implementation {}
    namespace factory_implementation {}
}

namespace winrt
{
    namespace implementation = ::winrt::Islands::UI::Xaml::Controls::implementation;
    namespace factory_implementation = ::winrt::Islands::UI::Xaml::Controls::factory_implementation;

    using namespace ::winrt::Windows::Foundation;
    using namespace ::winrt::Windows::Foundation::Collections;
    using namespace ::winrt::Windows::Foundation::Numerics;
    using namespace ::winrt::Windows::ApplicationModel::Core;
    using namespace ::winrt::Windows::Graphics;
    using namespace ::winrt::Windows::Storage::Streams;
    using namespace ::winrt::Windows::System;
    using namespace ::winrt::Windows::UI;
    using namespace ::winrt::Windows::UI::Composition;
    using namespace ::winrt::Windows::UI::Text;
    using namespace ::winrt::Windows::UI::Xaml;
    using namespace ::winrt::Windows::UI::Xaml::Automation;
    using namespace ::winrt::Windows::UI::Xaml::Automation::Peers;
    using namespace ::winrt::Windows::UI::Xaml::Controls;
    using namespace ::winrt::Windows::UI::Xaml::Controls::Primitives;
    using namespace ::winrt::Windows::UI::Xaml::Data;
    using namespace ::winrt::Windows::UI::Xaml::Input;
    using namespace ::winrt::Windows::UI::Xaml::Interop;
    using namespace ::winrt::Windows::UI::Xaml::Markup;
    using namespace ::winrt::Windows::UI::Xaml::Media;
    using IconSource = ::winrt::Microsoft::UI::Xaml::Controls::IconSource;
    using AppWindowTitleBar = ::winrt::Islands::UI::Xaml::Controls::AppWindowTitleBar;
    using InputNonClientPointerSource = ::winrt::Islands::UI::Xaml::Controls::InputNonClientPointerSource;
    using MUXControlsTestHooks = ::winrt::Islands::UI::Xaml::Controls::MUXControlsTestHooks;
    using MUXControlsTestHooksLoggingMessageEventArgs = ::winrt::Islands::UI::Xaml::Controls::MUXControlsTestHooksLoggingMessageEventArgs;
    using NonClientRegionKind = ::winrt::Islands::UI::Xaml::Controls::NonClientRegionKind;
    using TitleBar = ::winrt::Islands::UI::Xaml::Controls::TitleBar;
    using TitleBarAutomationPeer = ::winrt::Islands::UI::Xaml::Controls::TitleBarAutomationPeer;
    using TitleBarTemplateSettings = ::winrt::Islands::UI::Xaml::Controls::TitleBarTemplateSettings;
    using TitleBarWindowAdapter = ::winrt::Islands::UI::Xaml::Controls::TitleBarWindowAdapter;
    using ScrollPresenterAutomationPeer = ::winrt::Islands::UI::Xaml::Automation::Peers::ScrollPresenterAutomationPeer;
    using ScrollPresenter = ::winrt::Islands::UI::Xaml::Controls::Primitives::ScrollPresenter;
    using ScrollView = ::winrt::Islands::UI::Xaml::Controls::ScrollView;
}

using namespace std::literals;
using std::wstring_view;
using winrt::com_ptr;

import inc.RuntimeClassHelpers;
import inc.event;
import inc.GlobalDependencyProperty;
import ixx.MUXControlsTestHooksLoggingMessageEventArgs;
import ixx.MUXControlsTestHooks;
import ixx.TitleBar;
import ixx.TitleBarTemplateSettings;
import ixx.TitleBarAutomationPeer;
import ixx.ScrollPresenter;
import ixx.ScrollPresenterAutomationPeer;
import ixx.ScrollView;
