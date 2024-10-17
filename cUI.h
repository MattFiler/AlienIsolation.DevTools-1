#pragma once

#include "DevTools.h"

namespace cUI
{
	void __fastcall h_OpenScene(void* _this, void* _EDX, const char* param_1, int* param_2);
	typedef void(__thiscall* t_OpenScene)(void* _this, const char* param_1, int* param_2);
	inline auto OpenScene = reinterpret_cast<t_OpenScene>(DEVTOOLS_RELATIVE_ADDRESS(0x009a6120 - 0x00400000));

	//Functions below here are in cUIRenderer

	//void __fastcall h_DrawTextARGB(void* _this, void* _EDX, const char* param_1, int* param_2);
	//typedef void(__thiscall* t_DrawTextARGB)(void* _this, const char* param_1, int* param_2);
	//inline auto DrawTextARGB = reinterpret_cast<t_DrawTextARGB>(DEVTOOLS_RELATIVE_ADDRESS(0x009aad80 - 0x00400000));
}
