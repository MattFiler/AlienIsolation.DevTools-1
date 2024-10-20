#pragma once

#include "DevTools.h"
#include <iostream>

namespace EntityManager
{
	typedef int(__thiscall* t_call_entity_method)(void* _this, int* param_1, char* param_2, int* param_3, int param_4);
	inline auto call_entity_method = reinterpret_cast<t_call_entity_method>(DEVTOOLS_RELATIVE_ADDRESS(0x0091d9f0 - 0x00400000));
	int  __fastcall h_call_entity_method(void* _this, void* _EDX, int* param_1, char* param_2, int* param_3, int param_4)
	{
		unsigned int method = *param_1; //shortguid

		std::cout << "call_entity_method = " << method << " " << param_2 << " " << param_3 << " " << param_4 << "\n";

		int val = call_entity_method(_this, param_1, param_2, param_3, param_4);
		std::cout << param_2 << "\n";
		std::cout << val << "\n";
		return val;
	}
}
