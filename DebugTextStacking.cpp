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