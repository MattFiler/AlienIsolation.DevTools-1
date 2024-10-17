#include "DebugEnvironmentMarker.h"

#include <stdio.h>
#include <iostream>

#include <Windows.h>

using namespace DebugEnvironmentMarker;

__declspec(noinline)
int __fastcall DebugEnvironmentMarker::h_on_update(void* _this, void* _EDX, int* param_1, int* param_2)
{
	std::cout << "DebugEnvironmentMarker h_on_update\n";
	return on_update(_this, param_1, param_2);
}