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

void __cdecl DebugTextStacking::h_create(DataTypes::EntityInfo* param_1, int** param_2)
{
	create(param_1, param_2);
	std::cout << "DebugTextStacking create = " << param_1->val1 << " " << param_1->val2 << "\n";
}