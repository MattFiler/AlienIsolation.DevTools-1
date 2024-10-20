#pragma once

#include <iostream>
#include "DevTools.h"
#include "Datatypes.h"
#include "ShortGuidTable.h"

namespace MemoryPool
{
	typedef int** (__thiscall* t_allocate_item)(void*, int**, int**);
	inline auto allocate_item = reinterpret_cast<t_allocate_item>(DEVTOOLS_RELATIVE_ADDRESS(0x005b1e50 - 0x00400000));
	int** __fastcall h_allocate_item(void* _this, int** param_1, int** param_2)
	{
		std::cout << "allocate_item\n";
		return allocate_item(_this, param_1, param_2);
	}
}
