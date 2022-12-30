#include "ShortGuid.h"

#include "Menu_Log.hpp"

#include <iostream>
#include <vector>

using namespace CATHODE;
using namespace CATHODE::DataTypes;

std::vector<ShortGuidWithString> ShortGuidTable::table = std::vector<ShortGuidWithString>();

__declspec(noinline)
uintptr_t __fastcall CATHODE::ShortGuid::hShortGuid(DataTypes::ShortGuid* _this, void* /*_EDX*/, char* node_name)
{
    uintptr_t result = ShortGuid(_this, node_name);
    ShortGuidTable::Add(node_name, (CATHODE::DataTypes::ShortGuid*)result); //store the strings locally
    return result;
}

template< typename T >
std::string ToHex(T i)
{
}
