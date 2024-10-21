#pragma once

#include "ShortGuidTable.h"
#include "DevTools.h"
#include "Datatypes.h"

namespace ShortGuid
{
	int* __fastcall hShortGuid(int* _this, void* _EDX, char* node_name);
	typedef int* (__thiscall* tShortGuid)(int*, char*);
	inline auto ShortGuid = reinterpret_cast<tShortGuid>(DEVTOOLS_RELATIVE_ADDRESS(0x004bf7f0));
}
