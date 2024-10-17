#pragma once

#include "DevTools.h"

namespace DebugText
{
	int __fastcall h_on_custom_method(void* _this, void* _EDX, int* param_1, int* param_2, int* param_3, int* param_4);
	typedef int(__thiscall* t_on_custom_method)(void*, int* param_1, int* param_2, int* param_3, int* param_4);
	inline auto on_custom_method = reinterpret_cast<t_on_custom_method>(DEVTOOLS_RELATIVE_ADDRESS(0x00913080 - 0x00400000));



	//These are methods in DEBUG_TEXT rather than DebugText

	int __fastcall h_on_start(void* _this, void* _EDX, int* param_1);
	typedef int(__thiscall* t_on_start)(void*, int* param_1);
	inline auto on_start = reinterpret_cast<t_on_start>(DEVTOOLS_RELATIVE_ADDRESS(0x005a7250 - 0x00400000));

}
