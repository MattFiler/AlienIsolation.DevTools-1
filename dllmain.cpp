#include "DevTools.h"

#include "GAME_LEVEL_MANAGER.h"
#include "GameFlow.h"
#include "UI_LAYERMANAGER.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>
#include <string>

bool LoadLevel(int id) {
    if (id == 0) return false;
    GAME_LEVEL_MANAGER::queue_level(GAME_LEVEL_MANAGER::m_instance, id);
    GAME_LEVEL_MANAGER::request_next_level(GAME_LEVEL_MANAGER::m_instance, false);
    return true;
}
bool LoadLevel(std::string name) {
    std::string levelToLoad = "Production\\" + name;
    const int level = GAME_LEVEL_MANAGER::get_level_from_name(GAME_LEVEL_MANAGER::m_instance, const_cast<char*>(levelToLoad.c_str()));
    return LoadLevel(level);
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD  ul_reason_for_call, LPVOID /*lpReserved*/)
{
    if (DetourIsHelperProcess())
    {
        return TRUE;
    }

    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DetourRestoreAfterWith();
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        DEVTOOLS_DETOURS_ATTACH(GAME_LEVEL_MANAGER::get_level_from_name, GAME_LEVEL_MANAGER::h_get_level_from_name);
        DEVTOOLS_DETOURS_ATTACH(GAME_LEVEL_MANAGER::queue_level, GAME_LEVEL_MANAGER::h_queue_level);
        DEVTOOLS_DETOURS_ATTACH(GAME_LEVEL_MANAGER::request_next_level, GAME_LEVEL_MANAGER::h_request_next_level);

        DEVTOOLS_DETOURS_ATTACH(GameFlow::start_gameplay, GameFlow::h_start_gameplay);

        DEVTOOLS_DETOURS_ATTACH(UI_LAYERMANAGER::GetLayer, UI_LAYERMANAGER::h_GetLayer);
        DEVTOOLS_DETOURS_ATTACH(UI_LAYERMANAGER::CreateLayer_TRIGGERABLE_DEBUG_TEXT, UI_LAYERMANAGER::h_CreateLayer_TRIGGERABLE_DEBUG_TEXT);
        DEVTOOLS_DETOURS_ATTACH(UI_LAYERMANAGER::CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK, UI_LAYERMANAGER::h_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK);

        const long result = DetourTransactionCommit();
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        DEVTOOLS_DETOURS_DETACH(GAME_LEVEL_MANAGER::get_level_from_name, GAME_LEVEL_MANAGER::h_get_level_from_name);
        DEVTOOLS_DETOURS_DETACH(GAME_LEVEL_MANAGER::queue_level, GAME_LEVEL_MANAGER::h_queue_level);
        DEVTOOLS_DETOURS_DETACH(GAME_LEVEL_MANAGER::request_next_level, GAME_LEVEL_MANAGER::h_request_next_level);

        DEVTOOLS_DETOURS_DETACH(GameFlow::start_gameplay, GameFlow::h_start_gameplay);

        DEVTOOLS_DETOURS_DETACH(UI_LAYERMANAGER::GetLayer, UI_LAYERMANAGER::h_GetLayer);
        DEVTOOLS_DETOURS_DETACH(UI_LAYERMANAGER::CreateLayer_TRIGGERABLE_DEBUG_TEXT, UI_LAYERMANAGER::h_CreateLayer_TRIGGERABLE_DEBUG_TEXT);
        DEVTOOLS_DETOURS_DETACH(UI_LAYERMANAGER::CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK, UI_LAYERMANAGER::h_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK);
        
        DetourTransactionCommit();
    }
	
    return TRUE;
}