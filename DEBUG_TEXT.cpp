#include "DEBUG_TEXT.h"
#include "Menu_Log.hpp"

__declspec(noinline)
void __fastcall DEBUG_TEXT::h_on_update(void* _this, void* _EDX, void* _ptr, void* _unk)
{
	m_this = _this;

	void* _debug = &_this + 0x20;

	logger.AddLog("CATHODE::DEBUG_TEXT::on_update: \n");
	on_update(_this, _ptr, _unk);
}