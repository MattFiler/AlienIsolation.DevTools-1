#pragma once

#include "DevTools.h"

namespace UI_LAYERMANAGER
{
	void __fastcall h_CreateLayer_TRIGGERABLE_DEBUG_TEXT(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2);
	typedef void (__thiscall* t_CreateLayer_TRIGGERABLE_DEBUG_TEXT)(void* _this, const char* filepath, void* unk0, bool unk1, int unk2);
	inline auto CreateLayer_TRIGGERABLE_DEBUG_TEXT = reinterpret_cast<t_CreateLayer_TRIGGERABLE_DEBUG_TEXT>(DEVTOOLS_RELATIVE_ADDRESS(0x0040e060));

	void __fastcall h_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2);
	typedef void (__thiscall* t_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK)(void* _this, const char* filepath, void* unk0, bool unk1, int unk2);
	inline auto CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK = reinterpret_cast<t_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK>(DEVTOOLS_RELATIVE_ADDRESS(0x0040e100));

	void* __fastcall h_GetLayer(void* _this, void* _EDX, const char* layer_name);
	typedef void*(__thiscall* t_GetLayer)(void* _this, const char* layer_name);
	inline auto GetLayer = reinterpret_cast<t_GetLayer>(DEVTOOLS_RELATIVE_ADDRESS(0x00410420));
}
