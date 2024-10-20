#include "DebugText.h"

#include <stdio.h>
#include <iostream>

#include <Windows.h>

using namespace DebugText;

__declspec(noinline)
int __fastcall DebugText::h_on_custom_method(void* _this, void* _EDX, int* param_1, int* param_2, int* param_3, int* param_4)
{
	std::cout << "DebugText OnCustomMethod\n";
	return on_custom_method(_this, param_1, param_2, param_3, param_4);
}

__declspec(noinline)
int __fastcall DebugText::h_get_alignment(void* _this, void* _EDX, int* param_1, int* param_2)
{
	std::cout << "DebugText get_alignment\n";
	return get_alignment(_this, param_1, param_2);
}

void __cdecl DebugText::h_create(DataTypes::EntityInfo* param_1, int** param_2)
{
	create(param_1, param_2);
	std::cout << "DebugText create = " << param_1->val1 << " " << param_1->composite_instance_id << " " << param_2 << "\n";
	
	//int v;
	//std::cin >> v;
}

int __fastcall DebugText::h_update(void* _this, void* _EDX, void* param_2, int param_3)
{
	int val = update(_this, param_2, param_3);
	std::cout << "DebugText update = " + val;
	return val;
}

__declspec(noinline)
int __fastcall DebugText::h_on_start(void* _this, void* _EDX, int* param_1)
{
	std::cout << "DebugText on_start\n";
	return on_start(_this, param_1);
}