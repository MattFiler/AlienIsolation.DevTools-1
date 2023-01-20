#pragma once

#include "DevTools.h"

namespace UI_LAYERMANAGER
{
	void __fastcall h_CreateLayer_SPLASH_SCREEN(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2);
	typedef void(__thiscall* t_CreateLayer_SPLASH_SCREEN)(void* _this, const char* filepath, void* unk0, bool unk1, int unk2);
	inline auto CreateLayer_SPLASH_SCREEN = reinterpret_cast<t_CreateLayer_SPLASH_SCREEN>(DEVTOOLS_RELATIVE_ADDRESS(0x0040dfc0));

	void __fastcall h_CreateLayer_TRIGGERABLE_DEBUG_TEXT(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2);
	typedef void (__thiscall* t_CreateLayer_TRIGGERABLE_DEBUG_TEXT)(void* _this, const char* filepath, void* unk0, bool unk1, int unk2);
	inline auto CreateLayer_TRIGGERABLE_DEBUG_TEXT = reinterpret_cast<t_CreateLayer_TRIGGERABLE_DEBUG_TEXT>(DEVTOOLS_RELATIVE_ADDRESS(0x0040e060));

	void __fastcall h_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2);
	typedef void (__thiscall* t_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK)(void* _this, const char* filepath, void* unk0, bool unk1, int unk2);
	inline auto CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK = reinterpret_cast<t_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK>(DEVTOOLS_RELATIVE_ADDRESS(0x0040e100));
}
