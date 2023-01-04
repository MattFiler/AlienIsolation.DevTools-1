#include "Menu.h"

// Game-specific code classes.
#include "GAME_LEVEL_MANAGER.h"

// Engine-specific code classes.

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
            //g_showMenu = !g_showMenu;
        }
        if (wParam == VK_INSERT) {
            LoadLevel(GAME_LEVEL_MANAGER::get_current_level(GAME_LEVEL_MANAGER::m_instance));
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

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    if (g_showMenu) 
    {
        const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings);

        static char levelName[128] = "";
        ImGui::InputTextWithHint("Level name", "e.g. TECH_RnD_HzdLab", levelName, IM_ARRAYSIZE(levelName));
        if (ImGui::Button("Load to provided level")) LoadLevel(levelName);

        ImGui::End();
    }
    ImGui::EndFrame();

    ImGui::Render();
    g_context->OMSetRenderTargets(1, &g_renderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

bool Menu::LoadLevel(std::string name) {
    std::string levelToLoad = "Production\\" + name;
    const int level = GAME_LEVEL_MANAGER::get_level_from_name(GAME_LEVEL_MANAGER::m_instance, const_cast<char*>(levelToLoad.c_str()));
    return LoadLevel(level);
}
bool Menu::LoadLevel(int id) {
    if (id == 0) return false;
    GAME_LEVEL_MANAGER::queue_level(GAME_LEVEL_MANAGER::m_instance, id);
    GAME_LEVEL_MANAGER::request_next_level(GAME_LEVEL_MANAGER::m_instance, false);
    return true;
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