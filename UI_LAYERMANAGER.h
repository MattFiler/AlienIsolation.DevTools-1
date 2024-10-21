#pragma once

#include "DevTools.h"
#include <string>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <fstream>

namespace UI_LAYERMANAGER
{
	inline void* _thisRef = nullptr;

	typedef int(__thiscall* t_GetLayer)(void* _this, const char* param_1);
	inline auto GetLayer = reinterpret_cast<t_GetLayer>(DEVTOOLS_RELATIVE_ADDRESS(0x00410420));
	int __fastcall h_GetLayer(void* _this, void* _EDX, const char* layer_name) {
		if (_this == nullptr)
			_this = _thisRef;
		_thisRef = _this;
		if (layer_name == "debug_text" || layer_name == "debug_text_stack") {
			std::cout << "GetLayer requested '" << layer_name << "'\n";
		}
		return GetLayer(_this, layer_name);
	}


	typedef void(__thiscall* t_CreateLayer_TRIGGERABLE_DEBUG_TEXT)(void* _this, const char* filepath, void* unk0, bool unk1, int unk2);
	inline auto CreateLayer_TRIGGERABLE_DEBUG_TEXT = reinterpret_cast<t_CreateLayer_TRIGGERABLE_DEBUG_TEXT>(DEVTOOLS_RELATIVE_ADDRESS(0x0040e060));
	void __fastcall h_CreateLayer_TRIGGERABLE_DEBUG_TEXT(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2)
	{
		CreateLayer_TRIGGERABLE_DEBUG_TEXT(_this, std::string("DATA/UI/DEBUGTEXT.GFX").c_str(), unk0, unk1, unk2);

		std::cout << "debug_text layer = " << GetLayer(_thisRef, std::string("debug_text").c_str()) << "\n";
		std::cout << "splash_screen layer = " << GetLayer(_thisRef, std::string("splash_screen").c_str()) << "\n";
		std::cout << "game_over_menu layer = " << GetLayer(_thisRef, std::string("game_over_menu").c_str()) << "\n";
	}


	typedef void(__thiscall* t_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK)(void* _this, const char* filepath, void* unk0, bool unk1, int unk2);
	inline auto CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK = reinterpret_cast<t_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK>(DEVTOOLS_RELATIVE_ADDRESS(0x0040e100));
	void __fastcall h_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2)
	{
		CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK(_this, std::string("DATA/UI/DEBUGTEXT.GFX").c_str(), unk0, unk1, unk2);

		std::cout << "debug_text_stack layer = " << GetLayer(_thisRef, std::string("debug_text_stack").c_str()) << "\n";
	}
}
