#include "EntityInterface.h"

#include <stdio.h>
#include <iostream>

#include <Windows.h>

using namespace EntityInterface;

__declspec(noinline)
bool __fastcall EntityInterface::h_find_parameter(void* _this, void* _EDX, const DataTypes::MemoryPtr& entity_ptr, const DataTypes::ShortGuid& shortguid_ptr, DataTypes::Enum& output_ptr)
{
	return find_parameter(_this, entity_ptr, shortguid_ptr, output_ptr);
}