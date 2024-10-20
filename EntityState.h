#pragma once

#include <iostream>
#include "DevTools.h"
#include "Datatypes.h"
#include "ShortGuidTable.h"

namespace EntityState
{
    enum EntityStateID {
        NO_STATE = 0x0,
        ACTIVATE = 0x1,
        SPAWN = 0x2,
        START = 0x4,
        PAUSE = 0x8,
        ATTACH = 0x10,
        UNKNOWN_1 = 0x20,
        UNKNOWN_2 = 0x40,
        ENABLE = 0x80,
        SIMULATE = 0x100,
        LOCK = 0x200,
        SHOW = 0x400,
        SUSPEND = 0x800,
        PROXY_ENABLE = 0x1000,
        FLOATING = 0x2000,
        LIGHT_SWITCH_ON = 0x4000,
        INSTALL_PROXY = 0x8000,
        UNKNOWN_3 = 0x10000,
        UNKNOWN_4 = 0x20000,
        UNKNOWN_5 = 0x40000,
        SUSPENDED = 0x80000,
        GHOSTED = 0x100000,
        INVISIBLE = 0x200000,
        FROZEN = 0x400000
    };

    std::string entityStateIDToString(EntityStateID state) {
        switch (state) {
        case NO_STATE: return "NO_STATE";
        case ACTIVATE: return "ACTIVATE";
        case SPAWN: return "SPAWN";
        case START: return "START";
        case PAUSE: return "PAUSE";
        case ATTACH: return "ATTACH";
        case UNKNOWN_1: return "UNKNOWN_1";
        case UNKNOWN_2: return "UNKNOWN_2";
        case ENABLE: return "ENABLE";
        case SIMULATE: return "SIMULATE";
        case LOCK: return "LOCK";
        case SHOW: return "SHOW";
        case SUSPEND: return "SUSPEND";
        case PROXY_ENABLE: return "PROXY_ENABLE";
        case FLOATING: return "FLOATING";
        case LIGHT_SWITCH_ON: return "LIGHT_SWITCH_ON";
        case INSTALL_PROXY: return "INSTALL_PROXY";
        case UNKNOWN_3: return "UNKNOWN_3";
        case UNKNOWN_4: return "UNKNOWN_4";
        case UNKNOWN_5: return "UNKNOWN_5";
        case SUSPENDED: return "SUSPENDED";
        case GHOSTED: return "GHOSTED";
        case INVISIBLE: return "INVISIBLE";
        case FROZEN: return "FROZEN";
        default: return "UNKNOWN_STATE";
        }
    }

	typedef void(__thiscall* t_state_change)(void* _this, int* param_1, int param_2, unsigned int param_3, bool param_4);
	inline auto state_change = reinterpret_cast<t_state_change>(DEVTOOLS_RELATIVE_ADDRESS(0x00937670 - 0x00400000));
	void  __fastcall h_state_change(void* _this, void* _EDX, int* param_1, int param_2, unsigned int param_3, bool param_4)
	{
		state_change(_this, param_1, param_2, param_3, param_4);
		std::cout << "state_change " << param_1 << " " << param_2 << " " << entityStateIDToString((EntityStateID)param_3) << " " << param_4 << "" << "\n";
	}
}
