#include "EntityInterface.h"

#include "Menu.h"
#include "StringTable.h"

#include "Menu_Log.hpp"

#include <map>

using namespace CATHODE;
using namespace CATHODE::DataTypes;

std::map<ShortGuid, const char*> nodeNameTable;
//std::map<ShortGuid, bool> permittedEnumGuids;
//std::map<ShortGuid, std::pair<Enum, bool>> enumOverrides;
//std::map<ShortGuid, std::pair<Enum, std::string>> entityStates;
//std::map<MemoryPtr, Enum*> enums;
std::map<ShortGuid, bool> boolOverrides;
bool g_shouldOverrideBehaviourAnim = false;
Vector g_lightingColourOverride;

bool shouldLogFloats = false;
bool shouldLogBools = false;
bool shouldLogEnums = false;
bool shouldLogStrings = false;
bool shouldLogVectors = false;

//todo: log these using entity_ptr to get entity info

bool __fastcall EntityInterface::hFindParameterString(void* _this, void* /*_EDX*/, MemoryPtr* entity_ptr, ShortGuid* shortguid_ptr, String* output_ptr)
{
	const bool ret = FindParameterString(_this, entity_ptr, shortguid_ptr, output_ptr);
	std::string paramName = ShortGuidTable::Get(shortguid_ptr);
	if (shouldLogStrings) logger.AddLog(("param '" + paramName + "' using STRING val\n").c_str());
	return ret;
}

__declspec(noinline)
bool __fastcall EntityInterface::hFindParameterBool(void* _this, void* /*_EDX*/, MemoryPtr* entity_ptr, ShortGuid* shortguid_ptr, bool* bool_val)
{
	const bool ret = FindParameterBool(_this, entity_ptr, shortguid_ptr, bool_val);
	std::string paramName = ShortGuidTable::Get(shortguid_ptr);
	if (shouldLogBools) logger.AddLog(("param '" + paramName + "' using BOOL val '" + std::to_string(*bool_val) + "'\n").c_str());
	return ret;
}

bool __fastcall EntityInterface::hFindParameterVector(void* _this, void* /*_EDX*/, MemoryPtr* entity_ptr, ShortGuid* shortguid_ptr, Vector* output_ptr)
{
	const bool ret = FindParameterVector(_this, entity_ptr, shortguid_ptr, output_ptr);
	std::string paramName = ShortGuidTable::Get(shortguid_ptr);
	if (shouldLogVectors) logger.AddLog(("param '" + paramName + "' using VECTOR val\n").c_str());
	return ret;
}

__declspec(noinline)
bool __fastcall EntityInterface::hFindParameterFloat(void* _this, void* /*_EDX*/, MemoryPtr* entity_ptr, ShortGuid* shortguid_ptr, float* float_val)
{
	const bool ret = FindParameterFloat(_this, entity_ptr, shortguid_ptr, float_val);
	std::string paramName = ShortGuidTable::Get(shortguid_ptr);
	if (shouldLogFloats) logger.AddLog(("param '" + paramName + "' using FLOAT val '"+std::to_string(*float_val)+"'\n").c_str());
	return ret;
}

bool __fastcall EntityInterface::hFindParameterEnum(void* _this, void* /*_EDX*/, MemoryPtr* entity_ptr, ShortGuid* shortguid_ptr, Enum* output_ptr)
{
	std::string paramName = ShortGuidTable::Get(shortguid_ptr);
	std::string enumName = ShortGuidTable::Get(output_ptr->enum_short_guid); //TODO: this is wrong
	int enumIndex = output_ptr->enum_value_index;

	if (shouldLogEnums) logger.AddLog(("param '" + paramName + "' using ENUM val '" + enumName + "' with index '%i'\n").c_str(), enumIndex);

	const bool ret = FindParameterEnum(_this, entity_ptr, shortguid_ptr, output_ptr);
	return ret;
}
