#pragma once

#include "DevTools.h"

namespace DebugTextStacking
{
	int __fastcall h_on_custom_method(void* _this, void* _EDX, int* param_1, int* param_2, int* param_3, int* param_4);
	typedef int(__thiscall* t_on_custom_method)(void*, int* param_1, int* param_2, int* param_3, int* param_4);
	inline auto on_custom_method = reinterpret_cast<t_on_custom_method>(DEVTOOLS_RELATIVE_ADDRESS(0x00912e70 - 0x00400000));

	int** __cdecl h_create(int** param_1, int** param_2);
	typedef int** (__cdecl* t_create)(int** param_1, int** param_2);
	inline auto create = reinterpret_cast<t_create>(DEVTOOLS_RELATIVE_ADDRESS(0x005c1730 - 0x00400000));
}
