module;

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <roapi.h>
#include <winstring.h>

export module winrt_smoke;

export using ::DWORD;
export using ::FARPROC;
export using ::HINSTANCE;
export using ::HSTRING;
export using ::IActivationFactory;
export using ::UINT32;

export using DllModuleHandle = HINSTANCE;
export using HResult = HRESULT;
export using DllGetActivationFactoryFn = HResult(__stdcall*)(HSTRING, IActivationFactory**);

export using ::FreeLibrary;
export using ::GetLastError;
export using ::GetProcAddress;
export using ::LoadLibraryW;
export using ::RoInitialize;
export using ::RoUninitialize;
export using ::WindowsCreateString;
export using ::WindowsDeleteString;

export constexpr auto roInitSingleThreaded = RO_INIT_SINGLETHREADED;
export constexpr auto rpcChangedMode = RPC_E_CHANGED_MODE;

export inline bool succeeded(HResult hr) noexcept
{
    return SUCCEEDED(hr);
}

export inline bool failed(HResult hr) noexcept
{
    return FAILED(hr);
}
