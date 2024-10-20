#pragma once

#include <iostream>
#include "DevTools.h"
#include "Datatypes.h"
#include "ShortGuidTable.h"

namespace EntityState
{
	typedef int(__thiscall* t_state_change)(void* _this, int* param_1, int param_2, unsigned int param_3, char param_4);
	inline auto state_change = reinterpret_cast<t_state_change>(DEVTOOLS_RELATIVE_ADDRESS(0x00937670 - 0x00400000));
	int  __fastcall h_state_change(void* _this, void* _EDX, int* param_1, int param_2, unsigned int param_3, char param_4)
	{
		int val = state_change(_this, param_1, param_2, param_3, param_4);
		std::cout << "state_change " << val << " " << param_1 << " " << param_2 << " " << param_3 << " " << param_4 << "\n";
		return val;
	}
}
