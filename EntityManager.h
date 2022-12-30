#pragma once

#include "DevTools.h"
#include "CATHODE.h"

namespace EntityManager
{
	inline void* m_this = nullptr;

	//Jump to Checkpoint entity
	void __fastcall h_jump_to_checkpoint(void* _this, void* _EDX, const char* checkpoint);
	typedef void(__thiscall* t_jump_to_checkpoint)(void*, const char*);
	inline auto jump_to_checkpoint = reinterpret_cast<t_jump_to_checkpoint>(DEVTOOLS_RELATIVE_ADDRESS(0x00522330));

	//There is also jump_to_DEBUG_checkpoint which will take you to DebugCheckpoint entities

	//Get entity name
	char* __fastcall h_object_name(void* _this, void* _EDX, void* obj);
	typedef char*(__thiscall* t_object_name)(void*, void*);
	inline auto object_name = reinterpret_cast<t_object_name>(DEVTOOLS_RELATIVE_ADDRESS(0x00520d70));
}
