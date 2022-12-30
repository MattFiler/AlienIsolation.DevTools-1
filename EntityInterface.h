#pragma once

#include "DevTools.h"
#include "CATHODE.h"
#include "ShortGuidTable.h"

namespace CATHODE::EntityInterface
{
	typedef void(__cdecl* t_call_triggers)(DataTypes::MemoryPtr* entity, DataTypes::ShortGuid* shortguid, DataTypes::MemoryRefPtr* trigger_info, double unk);
	inline auto call_triggers = reinterpret_cast<t_call_triggers>(DEVTOOLS_RELATIVE_ADDRESS(0x004bd920));

	bool __fastcall hFindParameterString(void* _this, void* _EDX, DataTypes::MemoryPtr* entity_ptr, DataTypes::ShortGuid* shortguid_ptr, DataTypes::String* output_ptr);
	typedef bool(__thiscall* tFindParameterString)(void* , DataTypes::MemoryPtr* , DataTypes::ShortGuid* , DataTypes::String*);
	inline auto FindParameterString = reinterpret_cast<tFindParameterString>(DEVTOOLS_RELATIVE_ADDRESS(0x001991a0));

	bool __fastcall hFindParameterBool(void* _this, void* _EDX, DataTypes::MemoryPtr* entity_ptr, DataTypes::ShortGuid* shortguid_ptr, bool output_ptr);
	typedef bool(__thiscall* tFindParameterBool)(void* , DataTypes::MemoryPtr* , DataTypes::ShortGuid* , bool );
	inline auto FindParameterBool = reinterpret_cast<tFindParameterBool>(DEVTOOLS_RELATIVE_ADDRESS(0x00230590));

	bool __fastcall hFindParameterVector(void* _this, void* _EDX, DataTypes::MemoryPtr* entity_ptr, DataTypes::ShortGuid* shortguid_ptr, DataTypes::Vector* output_ptr);
	typedef bool(__thiscall* tFindParameterVector)(void* , DataTypes::MemoryPtr* , DataTypes::ShortGuid* , DataTypes::Vector* );
	inline auto FindParameterVector = reinterpret_cast<tFindParameterVector>(DEVTOOLS_RELATIVE_ADDRESS(0x004d63c0));

	bool __fastcall hFindParameterFloat(void* _this, void* _EDX, DataTypes::MemoryPtr* entity_ptr, DataTypes::ShortGuid* shortguid_ptr, float output_ptr);
	typedef bool(__thiscall* tFindParameterFloat)(void* , DataTypes::MemoryPtr* , DataTypes::ShortGuid* , float );
	inline auto FindParameterFloat = reinterpret_cast<tFindParameterFloat>(DEVTOOLS_RELATIVE_ADDRESS(0x004d6510));

	bool __fastcall hFindParameterEnum(void* _this, void* _EDX, DataTypes::MemoryPtr* entity_ptr, DataTypes::ShortGuid* shortguid_ptr, DataTypes::Enum* output_ptr);
	typedef bool(__thiscall* tFindParameterEnum)(void* , DataTypes::MemoryPtr* , DataTypes::ShortGuid* , DataTypes::Enum* );
	inline auto FindParameterEnum = reinterpret_cast<tFindParameterEnum>(DEVTOOLS_RELATIVE_ADDRESS(0x004d6620));
}
