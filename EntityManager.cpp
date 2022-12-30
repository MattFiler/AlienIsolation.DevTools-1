#include "EntityManager.h"
#include "Menu_Log.hpp"

__declspec(noinline)
void __fastcall EntityManager::h_jump_to_checkpoint(void* _this, void* _EDX, const char* checkpoint)
{
	m_this = _this;

	logger.AddLog("CATHODE::EntityManager::jump_to_checkpoint(%s);\n", checkpoint);
	jump_to_checkpoint(_this, checkpoint);
}

__declspec(noinline)
char* __fastcall EntityManager::h_object_name(void* _this, void* _EDX, void* obj)
{
	m_this = _this;

	char* name = object_name(_this, obj);
	//logger.AddLog("CATHODE::EntityManager::object_name: %s;\n", name);
	return name;
}
