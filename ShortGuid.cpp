#include "ShortGuid.h"

#include <iostream>
#include <vector>

std::vector<ShortGuidWithString> ShortGuidTable::table = std::vector<ShortGuidWithString>();

__declspec(noinline)
int* __fastcall ShortGuid::hShortGuid(int* _this, void* /*_EDX*/, char* str)
{
    //std::cout << str << "\n";

    int* result = ShortGuid(_this, str);
    ShortGuidTable::Add(str, (DataTypes::ShortGuid)*result); //store the strings locally
    return result;
}
