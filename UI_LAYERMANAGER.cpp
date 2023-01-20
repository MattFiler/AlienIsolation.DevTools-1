#include "UI_LAYERMANAGER.h"

#include <stdio.h>
#include <string>
#include <fstream>

using namespace UI_LAYERMANAGER;

__declspec(noinline)
void __fastcall UI_LAYERMANAGER::h_CreateLayer_SPLASH_SCREEN(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2)
{
	std::string fixed = "DATA/UI/DEBUGTEXT.GFX";
	CreateLayer_SPLASH_SCREEN(_this, filepath, unk0, unk1, unk2);
}

__declspec(noinline)
void __fastcall UI_LAYERMANAGER::h_CreateLayer_TRIGGERABLE_DEBUG_TEXT(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2)
{
	std::string fixed = "DATA/UI/DEBUGTEXT.GFX";
	CreateLayer_TRIGGERABLE_DEBUG_TEXT(_this, fixed.c_str(), unk0, unk1, unk2);
}

__declspec(noinline)
void __fastcall UI_LAYERMANAGER::h_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK(void* _this, void* _EDX, const char* filepath, void* unk0, bool unk1, int unk2)
{
	std::string fixed = "DATA/UI/DEBUGTEXT.GFX";
	CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK(_this, fixed.c_str(), unk0, unk1, unk2);
}