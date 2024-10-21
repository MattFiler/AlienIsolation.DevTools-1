#pragma once

#include "DevTools.h"
#include "EntityState.h"

namespace DebugText
{
	int __fastcall h_on_custom_method(void* _this, void* _EDX, int* param_1, int* param_2, int* param_3, int* param_4);
	typedef int(__thiscall* t_on_custom_method)(void* _this, int* param_1, int* param_2, int* param_3, int* param_4);
	inline auto on_custom_method = reinterpret_cast<t_on_custom_method>(DEVTOOLS_RELATIVE_ADDRESS(0x00913080 - 0x00400000));

	int __fastcall h_get_alignment(void* _this, void* _EDX, int* param_1, int* param_2);
	typedef int(__thiscall* t_get_alignment)(void* _this, int* param_1, int* param_2);
	inline auto get_alignment = reinterpret_cast<t_get_alignment>(DEVTOOLS_RELATIVE_ADDRESS(0x008eae70 - 0x00400000));

	void __cdecl h_create(EntityInfo* param_1, int** param_2);
	typedef void(__cdecl* t_create)(EntityInfo* param_1, int** param_2);
	inline auto create = reinterpret_cast<t_create>(DEVTOOLS_RELATIVE_ADDRESS(0x005c18b0 - 0x00400000));

	int __fastcall h_update(void* _this, void* _EDX, void* param_2, int param_3);
	typedef int (__thiscall* t_update)(void* _this, void* param_2, int param_3);
	inline auto update = reinterpret_cast<t_update>(DEVTOOLS_RELATIVE_ADDRESS(0x005a7150 - 0x00400000));



	//These are methods in DEBUG_TEXT rather than DebugText

	int __fastcall h_on_start(void* _this, void* _EDX, int* param_1);
	typedef int(__thiscall* t_on_start)(void* _this, int* param_1);
	inline auto on_start = reinterpret_cast<t_on_start>(DEVTOOLS_RELATIVE_ADDRESS(0x005a7250 - 0x00400000));

}
