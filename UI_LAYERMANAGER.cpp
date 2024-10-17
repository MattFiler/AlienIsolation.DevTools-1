#include "UI_LAYERMANAGER.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <fstream>

using namespace UI_LAYERMANAGER;

__declspec(noinline)
void __fastcall UI_LAYERMANAGER::h_CreateLayer_TRIGGERABLE_DEBUG_TEXT(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2)
{
	std::cout << "h_CreateLayer_TRIGGERABLE_DEBUG_TEXT\n";

	CreateLayer_TRIGGERABLE_DEBUG_TEXT(_this, std::string("DATA/UI/DEBUGTEXT.GFX").c_str(), unk0, unk1, unk2);
	std::cout << "debug_text = " << GetLayer(_this, std::string("debug_text").c_str()) << "\n";
	std::cout << "ThisShouldBeNull = " << GetLayer(_this, std::string("ThisShouldBeNull").c_str()) << "\n";
}

__declspec(noinline)
void __fastcall UI_LAYERMANAGER::h_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2)
{
	std::cout << "h_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK\n";

	CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK(_this, std::string("DATA/UI/DEBUGTEXT.GFX").c_str(), unk0, unk1, unk2);
	std::cout << "debug_text_stack = " << GetLayer(_this, std::string("debug_text_stack").c_str()) << "\n";
}

__declspec(noinline)
void* __fastcall UI_LAYERMANAGER::h_GetLayer(void* _this, void* _EDX, const char* layer_name)
{
	return GetLayer(_this, layer_name);
}