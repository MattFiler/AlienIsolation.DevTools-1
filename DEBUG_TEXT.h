#pragma once

#include "DevTools.h"
#include "CATHODE.h"

namespace DEBUG_TEXT
{
	inline void* m_this = nullptr;

	//Jump to Checkpoint entity
	void __fastcall h_on_update(void* _this, void* _EDX, void* _entity, void* _unk);
	typedef void(__thiscall* t_on_update)(void*, void*, void*);
	inline auto on_update = reinterpret_cast<t_on_update>(DEVTOOLS_RELATIVE_ADDRESS(0x001a7250));
}
