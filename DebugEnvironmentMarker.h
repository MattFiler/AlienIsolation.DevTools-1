#pragma once

#include "DevTools.h"

namespace DebugEnvironmentMarker
{

	//These are methods in DEBUG_ENVIRONMENT_MARKER rather than DebugEnvironmentMarker

	int __fastcall h_on_update(void* _this, void* _EDX, int* param_1, int* param_2);
	typedef int(__thiscall* t_on_update)(void* _this, int* param_1, int* param_2);
	inline auto on_update = reinterpret_cast<t_on_update>(DEVTOOLS_RELATIVE_ADDRESS(0x005a77d0 - 0x00400000));

}
