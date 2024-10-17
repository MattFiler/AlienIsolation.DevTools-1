#include "DevTools.h"

#include "GAME_LEVEL_MANAGER.h"
#include "GameFlow.h"
#include "UI_LAYERMANAGER.h"
#include "DebugText.h"
#include "DebugTextStacking.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>
#include <string>
#include <iostream>
#include <fstream>

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

void RedirectIOToConsole()
{
    AllocConsole();

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
    freopen_s(&fp, "CONOUT$", "w", stderr);

    std::ios::sync_with_stdio();
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD  ul_reason_for_call, LPVOID /*lpReserved*/)
{
    if (DetourIsHelperProcess())
    {
        return TRUE;
    }

    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            RedirectIOToConsole();

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

            DEVTOOLS_DETOURS_ATTACH(DebugText::on_custom_method, DebugText::h_on_custom_method);
            DEVTOOLS_DETOURS_ATTACH(DebugText::on_start, DebugText::h_on_start);
            DEVTOOLS_DETOURS_ATTACH(DebugTextStacking::on_custom_method, DebugTextStacking::h_on_custom_method);

            DetourTransactionCommit();
            break;

        case DLL_PROCESS_DETACH:
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());

            DEVTOOLS_DETOURS_DETACH(GAME_LEVEL_MANAGER::get_level_from_name, GAME_LEVEL_MANAGER::h_get_level_from_name);
            DEVTOOLS_DETOURS_DETACH(GAME_LEVEL_MANAGER::queue_level, GAME_LEVEL_MANAGER::h_queue_level);
            DEVTOOLS_DETOURS_DETACH(GAME_LEVEL_MANAGER::request_next_level, GAME_LEVEL_MANAGER::h_request_next_level);

            DEVTOOLS_DETOURS_DETACH(GameFlow::start_gameplay, GameFlow::h_start_gameplay);

            DEVTOOLS_DETOURS_DETACH(UI_LAYERMANAGER::GetLayer, UI_LAYERMANAGER::h_GetLayer);
            DEVTOOLS_DETOURS_DETACH(UI_LAYERMANAGER::CreateLayer_TRIGGERABLE_DEBUG_TEXT, UI_LAYERMANAGER::h_CreateLayer_TRIGGERABLE_DEBUG_TEXT);
            DEVTOOLS_DETOURS_DETACH(UI_LAYERMANAGER::CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK, UI_LAYERMANAGER::h_CreateLayer_TRIGGERABLE_DEBUG_TEXT_STACK);

            DEVTOOLS_DETOURS_DETACH(DebugText::on_custom_method, DebugText::h_on_custom_method);
            DEVTOOLS_DETOURS_DETACH(DebugText::on_start, DebugText::h_on_start);
            DEVTOOLS_DETOURS_DETACH(DebugTextStacking::on_custom_method, DebugTextStacking::h_on_custom_method);
        
            DetourTransactionCommit();
            break;
    }
	
    return TRUE;
}