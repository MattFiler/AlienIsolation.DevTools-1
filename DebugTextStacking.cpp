#include "DebugTextStacking.h"

#include <stdio.h>
#include <iostream>

#include <Windows.h>

using namespace DebugTextStacking;

__declspec(noinline)
int __fastcall DebugTextStacking::h_on_custom_method(void* _this, void* _EDX, int* param_1, int* param_2, int* param_3, int* param_4)
{
	std::cout << "DebugTextStacking OnCustomMethod\n";
	return on_custom_method(_this, param_1, param_2, param_3, param_4);
}

void __cdecl DebugTextStacking::h_create(EntityInfo* param_1, int** param_2)
{
	create(param_1, param_2);
	std::cout << "DebugTextStacking create = " << EntityState::DumpStatesToString(param_1->entityState.state) << " " << param_1->unk1 << " " << param_1->unk2 << "\n";
	
	/*EntityInfo* entity = param_1;
	if (param_1->parent != nullptr) {
		entity = param_1->parent;
		std::cout << "[P]DebugTextStacking create = " << EntityState::entityStateIDToString(entity->entityState.state) << "\n";
	}
	else {
		std::cout << "[C]DebugTextStacking create = " << EntityState::entityStateIDToString(entity->entityState.state) << "\n";
	}*/
}