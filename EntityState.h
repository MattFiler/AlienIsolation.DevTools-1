#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "DevTools.h"
#include "Datatypes.h"
#include "ShortGuidTable.h"

namespace EntityState
{
    enum class EntityStateID : std::uint32_t {
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
    DEFINE_ENUM_FLAG_OPERATORS(EntityStateID)

    struct Data {
        EntityStateID state;
    };

    std::string entityStateIDToString(EntityStateID state);
    std::string DumpStatesToString(EntityStateID state);

	typedef void(__thiscall* t_state_change)(EntityState::Data* _this, int* param_1, int param_2, EntityStateID state, bool shouldAddState);
	inline auto state_change = reinterpret_cast<t_state_change>(DEVTOOLS_RELATIVE_ADDRESS(0x00937670 - 0x00400000));
    void __fastcall h_state_change(EntityState::Data* _this, void* _EDX, int* param_1, int param_2, EntityStateID state, bool shouldAddState);
}

struct EntityInfo
{
    void** _vfptr;
    EntityState::Data entityState;
    DataTypes::ShortGuid guid;
    EntityInfo* parent;

    DataTypes::ShortGuid unk1;
    DataTypes::ShortGuid unk2;
};
