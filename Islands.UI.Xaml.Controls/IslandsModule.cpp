#include "pch.h"
#include "winrt/base.h"

void* winrt_make_Islands_UI_Xaml_Automation_Peers_ScrollPresenterAutomationPeer();
void* winrt_make_Islands_UI_Xaml_Controls_ScrollView();
void* winrt_make_Islands_UI_Xaml_Controls_ScrollingScrollOptions();
void* winrt_make_Islands_UI_Xaml_Controls_ScrollingZoomOptions();
void* winrt_make_Islands_UI_Xaml_Controls_XamlMetaDataProvider();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_MUXControlsTestHooks();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_RepeatedScrollSnapPoint();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_RepeatedZoomSnapPoint();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollControllerAddScrollVelocityRequestedEventArgs();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollControllerPanRequestedEventArgs();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollControllerScrollByRequestedEventArgs();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollControllerScrollToRequestedEventArgs();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollPresenter();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollPresenterTestHooks();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollSnapPoint();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollViewTestHooks();
void* winrt_make_Islands_UI_Xaml_Controls_Primitives_ZoomSnapPoint();

bool __stdcall winrt_can_unload_now() noexcept
{
    if (winrt::get_module_lock())
    {
        return false;
    }

    winrt::clear_factory_cache();
    return true;
}

void* __stdcall winrt_get_activation_factory(std::wstring_view const& name)
{
    auto requal = [](std::wstring_view const& left, std::wstring_view const& right) noexcept
    {
        return std::equal(left.rbegin(), left.rend(), right.rbegin(), right.rend());
    };

    if (requal(name, L"Islands.UI.Xaml.Automation.Peers.ScrollPresenterAutomationPeer"))
    {
        return winrt_make_Islands_UI_Xaml_Automation_Peers_ScrollPresenterAutomationPeer();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.ScrollView"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_ScrollView();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.ScrollingScrollOptions"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_ScrollingScrollOptions();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.ScrollingZoomOptions"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_ScrollingZoomOptions();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.XamlMetaDataProvider"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_XamlMetaDataProvider();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.MUXControlsTestHooks"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_MUXControlsTestHooks();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.RepeatedScrollSnapPoint"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_RepeatedScrollSnapPoint();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.RepeatedZoomSnapPoint"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_RepeatedZoomSnapPoint();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.ScrollControllerAddScrollVelocityRequestedEventArgs"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollControllerAddScrollVelocityRequestedEventArgs();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.ScrollControllerPanRequestedEventArgs"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollControllerPanRequestedEventArgs();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.ScrollControllerScrollByRequestedEventArgs"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollControllerScrollByRequestedEventArgs();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.ScrollControllerScrollToRequestedEventArgs"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollControllerScrollToRequestedEventArgs();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.ScrollPresenter"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollPresenter();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.ScrollPresenterTestHooks"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollPresenterTestHooks();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.ScrollSnapPoint"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollSnapPoint();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.ScrollViewTestHooks"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_ScrollViewTestHooks();
    }

    if (requal(name, L"Islands.UI.Xaml.Controls.Primitives.ZoomSnapPoint"))
    {
        return winrt_make_Islands_UI_Xaml_Controls_Primitives_ZoomSnapPoint();
    }

    return nullptr;
}

int32_t __stdcall WINRT_CanUnloadNow() noexcept
{
#ifdef _WRL_MODULE_H_
#ifdef _MSC_VER
#pragma warning(suppress: 4324)
#endif
    if (!::Microsoft::WRL::Module<::Microsoft::WRL::InProc>::GetModule().Terminate())
    {
        return 1;
    }
#endif

    return winrt_can_unload_now() ? 0 : 1;
}

int32_t __stdcall WINRT_GetActivationFactory(void* classId, void** factory) noexcept try
{
    std::wstring_view const name{ *reinterpret_cast<winrt::hstring*>(&classId) };
    *factory = winrt_get_activation_factory(name);

    if (*factory)
    {
        return 0;
    }

#ifdef _WRL_MODULE_H_
#pragma warning(suppress: 4324)
    return ::Microsoft::WRL::Module<::Microsoft::WRL::InProc>::GetModule().GetActivationFactory(
        static_cast<HSTRING>(classId),
        reinterpret_cast<::IActivationFactory**>(factory));
#else
    return winrt::hresult_class_not_available(name).to_abi();
#endif
}
catch (...)
{
    return winrt::to_hresult();
}
