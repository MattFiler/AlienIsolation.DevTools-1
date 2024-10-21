#pragma once

#include "DevTools.h"
#include "Datatypes.h"

namespace EntityInterface
{
	bool  __fastcall h_find_parameter(void* _this, void* _EDX, const DataTypes::MemoryPtr& entity_ptr, const DataTypes::ShortGuid& shortguid_ptr, DataTypes::Enum& output_ptr);
	typedef bool(__thiscall* t_find_parameter)(void*, const DataTypes::MemoryPtr& entity_ptr, const DataTypes::ShortGuid& shortguid_ptr, DataTypes::Enum& output_ptr);
	inline auto find_parameter = reinterpret_cast<t_find_parameter>(DEVTOOLS_RELATIVE_ADDRESS(0x008d6620 - 0x00400000));
}
