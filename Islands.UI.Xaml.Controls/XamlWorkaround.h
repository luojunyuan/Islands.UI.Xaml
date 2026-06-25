#pragma once

// XamlCompiler-generated .cpp/.h files still include C++/WinRT and STL headers.
// Include the project's native/textual base once before importing modules, then
// make the generated includes no-ops and satisfy the same symbols through modules.
#include "CppBaseIncludes.h"

#ifndef WINRT_IMPORT_MODULE
#define WINRT_IMPORT_MODULE
#endif

#undef _STL_COMPILER_PREPROCESSOR
#define _STL_COMPILER_PREPROCESSOR 0

import std;
import CppWinRTModules;
