module;

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <SDKDDKVer.h>
#include <unknwn.h>
#include <inspectable.h>
#include <Windows.h>
#include <windows.ui.xaml.hosting.referencetracker.h>
#include <winerror.h>
#include <strsafe.h>
#include <UIAutomationCore.h>
#include <UIAutomationCoreApi.h>

export module inc.win32;

export import inc.WinEventLogLevels;

export using ::BOOL;
export using ::DWORD;
export using ::FILETIME;
export using ::GUID;
export using ::HANDLE;
export using ::HRGN;
export using ::HRESULT;
export using ::HWND;
export using ::IInspectable;
export using ::IReferenceTrackerExtension;
export using ::ITrackerOwner;
export using ::IUnknown;
export using ::LONG;
export using ::LPVOID;
export using ::PCSTR;
export using ::PCWSTR;
export using ::PVOID;
export using ::PWSTR;
export using ::RECT;
export using ::PTP_CALLBACK_INSTANCE;
export using ::PTP_TIMER;
export using ::PTP_WAIT;
export using ::TP_WAIT_RESULT;
export using ::UCHAR;
export using ::UINT;
export using ::UINT16;
export using ::UINT32;
export using ::ULONG;
export using ::ULONGLONG;
export using ::WCHAR;
export using ::TrackerHandle;
export using ::LARGE_INTEGER;
export using ::LONGLONG;

export inline constexpr BOOL win32True{ 1 };
export inline constexpr BOOL win32False{ 0 };
export inline constexpr DWORD infiniteTimeout{ INFINITE };
export inline constexpr HRESULT eFail{ E_FAIL };
export inline constexpr HRESULT eAccessDenied{ E_ACCESSDENIED };
export inline constexpr HRESULT eInvalidArg{ E_INVALIDARG };
export inline constexpr HRESULT eInvalidOperation{ HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION) };
export inline constexpr HRESULT sOk{ S_OK };
export inline constexpr UINT cpUtf8{ CP_UTF8 };
export inline constexpr DWORD formatMessageAllocateBuffer{ FORMAT_MESSAGE_ALLOCATE_BUFFER };
export inline constexpr DWORD formatMessageFromString{ FORMAT_MESSAGE_FROM_STRING };
export inline constexpr int hitTestNowhere{ HTNOWHERE };
export inline constexpr int hitTestClient{ HTCLIENT };
export inline constexpr int hitTestCaption{ HTCAPTION };
export inline constexpr int hitTestSysMenu{ HTSYSMENU };
export inline constexpr int regionDiff{ RGN_DIFF };
export inline constexpr HRESULT strsafeInsufficientBuffer{ STRSAFE_E_INSUFFICIENT_BUFFER };
export inline constexpr HRESULT strsafeInvalidParameter{ STRSAFE_E_INVALID_PARAMETER };
export inline constexpr DWORD strsafeNullOnFailure{ STRSAFE_NULL_ON_FAILURE };

export using ::DeleteObject;
export using ::FormatMessageW;
export using ::FreeLibrary;
export using ::GetClassNameW;
export using ::GetLastError;
export using ::GetModuleHandleW;
export using ::GetProcAddress;
export using ::GetWindowLongPtrW;
export using ::GetWindowRgn;
export using ::GetWindowTextLengthW;
export using ::GetWindowTextW;
export using ::LoadLibraryW;
export using ::LocalFree;
export using ::MultiByteToWideChar;
export using ::OutputDebugStringW;
export using ::SetWindowRgn;
export using ::StringCchPrintfExW;
export using ::StringCchVPrintfW;
export using ::WideCharToMultiByte;

export inline bool failed(HRESULT hr) noexcept
{
    return FAILED(hr);
}

export inline bool succeeded(HRESULT hr) noexcept
{
    return SUCCEEDED(hr);
}

export inline HANDLE invalidHandleValue() noexcept
{
    return INVALID_HANDLE_VALUE;
}

export inline void closeHandle(HANDLE handle) noexcept
{
    CloseHandle(handle);
}

export inline void closeThreadpoolWait(PTP_WAIT wait) noexcept
{
    CloseThreadpoolWait(wait);
}

export inline void closeThreadpoolTimer(PTP_TIMER timer) noexcept
{
    CloseThreadpoolTimer(timer);
}

export inline HANDLE createEvent(void* attributes, BOOL manualReset, BOOL initialState, PCWSTR name) noexcept
{
    return CreateEventW(static_cast<LPSECURITY_ATTRIBUTES>(attributes), manualReset, initialState, name);
}

export inline PTP_TIMER createThreadpoolTimer(PTP_TIMER_CALLBACK callback, void* context, PTP_CALLBACK_ENVIRON environment) noexcept
{
    return CreateThreadpoolTimer(callback, context, environment);
}

export inline PTP_WAIT createThreadpoolWait(PTP_WAIT_CALLBACK callback, void* context, PTP_CALLBACK_ENVIRON environment) noexcept
{
    return CreateThreadpoolWait(callback, context, environment);
}

export inline LONG interlockedIncrement(LONG volatile* value) noexcept
{
    return InterlockedIncrement(value);
}

export inline LONGLONG interlockedIncrement64(LONGLONG volatile* value) noexcept
{
    return InterlockedIncrement64(value);
}

export inline bool inlineIsEqualGUID(GUID const& left, GUID const& right) noexcept
{
    return !!InlineIsEqualGUID(left, right);
}

export inline DWORD getCurrentThreadId() noexcept
{
    return GetCurrentThreadId();
}

export inline BOOL getWindowRect(HWND hwnd, RECT* rect) noexcept
{
    return GetWindowRect(hwnd, rect);
}

export inline HRGN createRectRgn(int left, int top, int right, int bottom) noexcept
{
    return CreateRectRgn(left, top, right, bottom);
}

export inline int combineRgn(HRGN destination, HRGN source1, HRGN source2, int mode) noexcept
{
    return CombineRgn(destination, source1, source2, mode);
}

export inline void setEvent(HANDLE handle) noexcept
{
    SetEvent(handle);
}

export inline void setThreadpoolTimer(PTP_TIMER timer, FILETIME* dueTime, DWORD period, DWORD windowLength) noexcept
{
    SetThreadpoolTimer(timer, dueTime, period, windowLength);
}

export inline void setThreadpoolWait(PTP_WAIT wait, HANDLE handle, FILETIME* timeout) noexcept
{
    SetThreadpoolWait(wait, handle, timeout);
}

export inline BOOL setWindowText(HWND hwnd, PCWSTR value) noexcept
{
    return SetWindowTextW(hwnd, value);
}

export inline DWORD waitForSingleObject(HANDLE handle, DWORD milliseconds) noexcept
{
    return WaitForSingleObject(handle, milliseconds);
}

export inline DWORD formatMessage(DWORD flags, PCWSTR source, DWORD messageId, DWORD languageId, PWSTR buffer, DWORD size, va_list* arguments) noexcept
{
    return FormatMessageW(flags, source, messageId, languageId, buffer, size, arguments);
}

export inline void* localFree(void* memory) noexcept
{
    return LocalFree(memory);
}

export inline int multiByteToWideChar(UINT codePage, DWORD flags, char const* source, int sourceLength, wchar_t* destination, int destinationLength) noexcept
{
    return MultiByteToWideChar(codePage, flags, source, sourceLength, destination, destinationLength);
}

export inline int wideCharToMultiByte(UINT codePage, DWORD flags, wchar_t const* source, int sourceLength, char* destination, int destinationLength, char const* defaultChar, BOOL* usedDefaultChar) noexcept
{
    return WideCharToMultiByte(codePage, flags, source, sourceLength, destination, destinationLength, defaultChar, usedDefaultChar);
}

export template <typename T, size_t Size>
constexpr size_t array_size(T const (&)[Size]) noexcept
{
    return Size;
}
