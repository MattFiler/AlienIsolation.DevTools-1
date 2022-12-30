#include "ShortGuid.h"

#include "Menu_Log.hpp"

#include <iostream>

using namespace CATHODE;
using namespace CATHODE::DataTypes;

__declspec(noinline)
uintptr_t __fastcall CATHODE::ShortGuid::hShortGuid(DataTypes::ShortGuid* _this, void* /*_EDX*/, char* node_name)
{
    return ShortGuid(_this, node_name);
}

template< typename T >
std::string ToHex(T i)
{
}
