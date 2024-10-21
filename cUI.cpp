#include "cUI.h"

#include <stdio.h>
#include <iostream>

#include <Windows.h>

using namespace cUI;

__declspec(noinline)
void __fastcall cUI::h_OpenScene(void* _this, void* _EDX, const char* param_1, int* param_2)
{
	if (param_1 == "BENCHMARK" || param_1 == "DEBUG MARKER" || param_1 == "UI_MEMORY") {
		std::cout << "cUI OpenScene: " << param_1 << "\n";
	}

	return OpenScene(_this, param_1, param_2);
}