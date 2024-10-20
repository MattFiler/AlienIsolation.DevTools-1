#pragma once

#include <iostream>
#include "DevTools.h"
#include "Datatypes.h"
#include "ShortGuidTable.h"

namespace EntityManager
{
	typedef int(__thiscall* t_call_entity_method)(void* _this, DataTypes::ShortGuid* param_1, int* param_2, int* param_3, int param_4);
	inline auto call_entity_method = reinterpret_cast<t_call_entity_method>(DEVTOOLS_RELATIVE_ADDRESS(0x0091d9f0 - 0x00400000));
	int  __fastcall h_call_entity_method(void* _this, void* _EDX, DataTypes::ShortGuid* param_1, int* param_2, int* param_3, int param_4)
	{
		std::string str = ShortGuidTable::Get(*param_1);
		int val = call_entity_method(_this, param_1, param_2, param_3, param_4);

		//param_2 gets set in call_entity_method

		std::cout << "call_entity_method " << val << " " << str << " " << *param_2 << " " << *param_3 << " " << param_4 << "\n";

		return val;
	}
}
