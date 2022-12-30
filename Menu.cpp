#include "Menu.h"
#include "Menu_Log.hpp"
#include "CATHODE.h"

// Game-specific code classes.
#include "GAME_LEVEL_MANAGER.h"
#include "AI_BEHAVIORAL.h"
#include "EntityManager.h"

// Engine-specific code classes.

#include "ShortGuid.h"

#include <detours.h>
#include <map>
#include <sstream>
#include <iomanip>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

IDXGISwapChain* g_swapChain = nullptr;
ID3D11Device* g_device = nullptr;
ID3D11DeviceContext* g_context = nullptr;
ID3D11RenderTargetView* g_renderTargetView = nullptr;
HWND                    g_hWindow = nullptr;
WNDPROC                 g_originalWndProcHandler = nullptr;

bool g_menuInitialised = false;
bool g_showDemoWindow = false;
bool g_showMenu = false;

const std::string g_modName = "Alien: Isolation DevTools";
const std::string g_modVersion = "0.1.4 (Alpha)";
const std::string g_modFullName = g_modName + " " + g_modVersion;

extern bool shouldLogFloats;
extern bool shouldLogBools;
extern bool shouldLogVectors;
extern bool shouldLogStrings;
extern bool shouldLogEnums;

Menu::Menu()
{
	
}

// Destructor for the Menu class.
Menu::~Menu() {
    g_swapChain = nullptr;
    g_context = nullptr;
    g_renderTargetView = nullptr;
    g_hWindow = nullptr;
    g_originalWndProcHandler = nullptr;
}

// Our custom window handler to override A:I's own handler.
// This lets us detect keyboard inputs and pass mouse + keyboard input control to ImGui.
LRESULT CALLBACK Menu::WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    ImGuiIO& io = ImGui::GetIO();
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    ScreenToClient(g_hWindow, &cursorPos);
    io.MousePos.x = cursorPos.x;
    io.MousePos.y = cursorPos.y;

    if (uMsg == WM_KEYUP) {
        if (wParam == VK_DELETE) {
            g_showMenu = !g_showMenu;
        }
    }

    if (g_showMenu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
        return true;
    }

    return CallWindowProc(g_originalWndProcHandler, hWnd, uMsg, wParam, lParam);
}

void Menu::InitMenu(IDXGISwapChain* pSwapChain)
{
    g_swapChain = pSwapChain;
}

IDXGISwapChain* Menu::GetSwapChain()
{
    return g_swapChain;
}

bool Menu::IsInitialised()
{
    return g_swapChain != nullptr;
}

void Menu::DrawMenu() {
    if (!g_menuInitialised) {
        if (FAILED(GetDeviceAndContextFromSwapChain(g_swapChain, &g_device, &g_context))) {
            DebugBreak();
            return;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
    	// Enable ImGUI support for keyboard and gamepad input.
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        // Get the swapchain description (we use this to get the handle to the game's window).
        DXGI_SWAP_CHAIN_DESC dxgiSwapChainDesc;
        //DX_CHECK(g_swapChain->GetDesc(&dxgiSwapChainDesc));
        if (FAILED(g_swapChain->GetDesc(&dxgiSwapChainDesc)))
        {
	        DebugBreak();
        	return;
        }

        ImGui::StyleColorsDark();
    	
        g_hWindow = dxgiSwapChainDesc.OutputWindow;
        // Replace the game's window handler with our own so we can intercept key press events in the game.
        g_originalWndProcHandler = reinterpret_cast<WNDPROC>(SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProcHandler)));

        ImGui_ImplWin32_Init(g_hWindow);
        ImGui_ImplDX11_Init(g_device, g_context);
        //io.ImeWindowHandle = g_hWindow;

        ID3D11Texture2D* pBackBuffer = nullptr;
        //DX_CHECK(g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer)));
        if (FAILED(g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer))))
        {
            DebugBreak();
            return;
        }

        // Ensure the back buffer is not 0 or null.
        if (pBackBuffer) {
            //DX_CHECK(g_device->CreateRenderTargetView(pBackBuffer, NULL, &g_renderTargetView));
            if (FAILED(g_device->CreateRenderTargetView(pBackBuffer, nullptr, &g_renderTargetView)))
            {
                DebugBreak();
                return;
            }
        }
        else {
            DebugBreak();
        	return;
        }

        pBackBuffer->Release();
    	
        g_menuInitialised = true;
    }

    // Feed inputs to dear imgui, start new frame.
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

	static int alienIsolation_devTools_menu_lastBehaviourAnimTargetValue = 0;
	static int alienIsolation_devTools_menu_behaviourAnimTargetValue = -1;
    static bool alienIsolation_devTools_menu_showEngineLog = true;
	static bool alienIsolation_devTools_enum_hasClearedEnumValueMap = false;
    static bool alienIsolation_devTools_enum_doClearEnumValueMap = false;
    static bool alienIsolation_devTools_enum_doReapplyEnumValueOverride = false;

    // Clear the stored enum value pointers between level loads (avoids null pointer exceptions).
    if ((alienIsolation_devTools_enum_doClearEnumValueMap) && !alienIsolation_devTools_enum_hasClearedEnumValueMap)
    {
        logger.AddLog("[Menu] Cleared behaviour anim enum map!\n");
        alienIsolation_devTools_enum_hasClearedEnumValueMap = true;
        alienIsolation_devTools_enum_doClearEnumValueMap = false;
    }
    else if (!alienIsolation_devTools_enum_doClearEnumValueMap && alienIsolation_devTools_enum_hasClearedEnumValueMap)
    {
        logger.AddLog("[Menu] Reset enum cleared flag!\n");
        alienIsolation_devTools_enum_hasClearedEnumValueMap = false;
        //alienIsolation_devTools_enum_doReapplyEnumValueOverride = true;
    }

	if (alienIsolation_devTools_menu_showEngineLog)
    {
    	// Show our CATHODE log output window.
	    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    	
	    // Actually call in the regular Log helper.
	    logger.Draw((g_modName + " - Engine Log").c_str(), &alienIsolation_devTools_menu_showEngineLog);
    }

	{
    	ImGui::SetNextWindowSize(ImVec2(480, 100), ImGuiCond_FirstUseEver);
        ImGui::Begin((g_modName + " - Monitor").c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);

        static const char* behaviourAnim_enumString = "";

        switch (alienIsolation_devTools_menu_behaviourAnimTargetValue)
        {
        case -1:
            behaviourAnim_enumString = "Not Available";
            break;
        case 0:
            behaviourAnim_enumString = "UNIFORM";
            break;
        case 1:
            behaviourAnim_enumString = "PULSATE";
            break;
        case 2:
            behaviourAnim_enumString = "OSCILLATE";
            break;
        case 3:
            behaviourAnim_enumString = "FLICKER";
            break;
        case 4:
            behaviourAnim_enumString = "FLUCTUATE";
            break;
        case 5:
            behaviourAnim_enumString = "FLICKER_OFF";
            break;
        case 6:
            behaviourAnim_enumString = "SPARKING";
        	break;
        case 7:
            behaviourAnim_enumString = "BLINK";
            break;
        default:
            behaviourAnim_enumString = "Unknown?!";
        }

        ImGui::Text("Lighting Behaviour Animation: %s (%d)", behaviourAnim_enumString, alienIsolation_devTools_menu_behaviourAnimTargetValue);
        ImGui::Text("Has cleared behaviour animation map: %s", alienIsolation_devTools_enum_hasClearedEnumValueMap ? "Yes" : "No");

        ImGui::End();
    }
	
    // If the user wants to display the menu, then render it.
    if (g_showMenu) {
        static bool alienIsolation_devTools_menu_showAboutWindow = false;

        if (alienIsolation_devTools_menu_showAboutWindow) {
            if (ImGui::Begin((g_modName + " - About").c_str(), &alienIsolation_devTools_menu_showAboutWindow, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings)) {
                ImGui::TextColored(ImVec4(255, 170, 0, 1), (g_modFullName + " - Built on %s at %s").c_str(), __DATE__, __TIME__);
                ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
                ImGui::Text("Detours %s", DETOURS_STRINGIFY(DETOURS_VERSION));
                ImGui::Separator();
                ImGui::Text("Build information:");
#ifdef _DEBUG
                ImGui::Text("Target: Debug");
#else
                ImGui::Text("Target: Release");
#endif
#ifdef _WIN32
                ImGui::Text("Architecture: x86");
#elif _WIN64
                ImGui::Text("Architecture: x64");
#endif
#ifdef _MSC_VER
                ImGui::Text("MSVC Compiler Version: %d (%d)", _MSC_VER, _MSC_FULL_VER);
#endif
#ifdef _MSVC_LANG
                ImGui::Text("MSVC C++ Standard: %d", _MSVC_LANG);
#endif
                ImGui::Separator();
                ImGui::Text("Mod credits:");
                ImGui::Text("Developed by RyanJGray with help from the following people, thanks!");
                ImGui::Text("MattFiler - thanks for all your help and support!");
            }

            ImGui::End();
        }

        // Get the center of the screen.
        const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        {
            ImGui::Begin((g_modName + " - Settings").c_str(), nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings);

            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("Help")) {
                    if (ImGui::MenuItem("About")) {
                        alienIsolation_devTools_menu_showAboutWindow = true;
                    }

                    ImGui::EndMenu();
                }
            	if (ImGui::BeginMenu("Tools")) {
	                if (ImGui::MenuItem("Engine Log")) {
		                alienIsolation_devTools_menu_showEngineLog = true;
	                }

            		ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            ImGui::TextColored(ImVec4(255, 170, 0, 1), g_modFullName.c_str());

            ImGui::Separator();

            ImGui::Text("Alien Withdrawl Control");

            if (ImGui::Button("Force Alien withdrawl"))
            {
                AI_BEHAVIORAL::WithdrawalManager::request_withdraw(AI_BEHAVIORAL::WithdrawalManager::m_this, 15.0f, 3.0f, -1.0f, false);
            }

            ImGui::Separator();

            ImGui::Text("Level Loading Control");

        	static char levelName[128] = "";
            static std::string levelPrefix = "Production\\";
            std::string levelToLoad;
            static bool invalidLevelError = false;
            ImGui::InputTextWithHint("Level name", "e.g. TECH_RnD_HzdLab", levelName, IM_ARRAYSIZE(levelName));
        	
            if (ImGui::Button("Load to provided level"))
            {
                levelToLoad = levelPrefix + levelName;

                const int level = GAME_LEVEL_MANAGER::get_level_from_name(GAME_LEVEL_MANAGER::m_instance, const_cast<char*>(levelToLoad.c_str()));

            	// When GAME_LEVEL_MANAGER::get_level_from_name returns int 0, this indicates that the engine does not recognise the level provided.
            	// Callback::GameMenu::LoadLevel has a hard-coded check for GAME_LEVEL_MANAGER::get_level_from_name returning int 0, it will terminate execution early if it detects that this happens.
                if (level == 0)
                {
                    invalidLevelError = true;
                }
            	else
            	{
                    invalidLevelError = false;
                    
                    // Add the level we want to the level queue.
                    GAME_LEVEL_MANAGER::queue_level(GAME_LEVEL_MANAGER::m_instance, level);

                    // Request that the game loads the next level in the queue.
                    GAME_LEVEL_MANAGER::request_next_level(GAME_LEVEL_MANAGER::m_instance, false);
                    
                    // Inform the enum map reset code that the UI wants the map to be cleared.
                    alienIsolation_devTools_enum_doClearEnumValueMap = true;
                }
            }

            ImGui::Separator();

            static char checkpointName[128] = "";
            ImGui::InputTextWithHint("Checkpoint name", "e.g. Entry", checkpointName, IM_ARRAYSIZE(checkpointName));

            if (ImGui::Button("Jump to Checkpoint"))
            {
                EntityManager::jump_to_checkpoint(EntityManager::m_this, "Entry");
            }

            ImGui::Separator();

            static char stringToConvert[128] = "";
            ImGui::InputTextWithHint("String", "e.g. HelloWorld", stringToConvert, IM_ARRAYSIZE(stringToConvert));

            if (ImGui::Button("Convert"))
            {
                EntityManager::jump_to_checkpoint(EntityManager::m_this, "Entry");

                CATHODE::DataTypes::ShortGuid* shortguid = new CATHODE::DataTypes::ShortGuid();
                CATHODE::ShortGuid::ShortGuid(shortguid, stringToConvert);

                std::stringstream s;
                s << std::setfill('0') << std::setw(sizeof(CATHODE::DataTypes::ShortGuid) * 2) << std::hex << *shortguid;
                logger.AddLog(("%s = " + s.str() +"\n").c_str(), stringToConvert);
            }

        	if (invalidLevelError)
        	{
                ImGui::TextColored(ImVec4(255, 170, 0, 1), "WARNING: Request blocked - Level not recognised by the engine!");
        	}

            ImGui::Separator();

            ImGui::Checkbox("Log FLOAT accessors", &shouldLogFloats);
            ImGui::Checkbox("Log BOOL accessors", &shouldLogBools);
            ImGui::Checkbox("Log STRING accessors", &shouldLogStrings);
            ImGui::Checkbox("Log ENUM accessors", &shouldLogEnums);
            ImGui::Checkbox("Log VECTOR accessors", &shouldLogVectors);

            ImGui::End();
        }
    }

    ImGui::EndFrame();

    // Render dear imgui onto the screen.
    ImGui::Render();
    g_context->OMSetRenderTargets(1, &g_renderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // A call to DXGISwapChain->Present is not needed here, as we are hooked into DirectX 11's Present function, so anything we draw here will be presented by the game in its own time.
}

void Menu::ShutdownMenu() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

// Code taken (and changed a little) from Niemand's wonderful article on hooking DX11 and using ImGUI.
// https://niemand.com.ar/2019/01/01/how-to-hook-directx-11-imgui/
HRESULT Menu::GetDeviceAndContextFromSwapChain(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext) {
    const HRESULT ret = pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<PVOID*>(ppDevice));

    if (SUCCEEDED(ret)) {
        (*ppDevice)->GetImmediateContext(ppContext);
    }

    return ret;
}