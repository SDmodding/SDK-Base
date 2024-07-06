#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <algorithm>
#include <string>
#include <map>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <SDK/_Includes.hpp>

namespace Global
{
    uint8_t g_GameStateInGameCounter = 0;
}

#include "Renderer.hh"
#include "Hooks.hh"

DWORD __stdcall MainThread(void* p_Reserved)
{
    auto pD3DGlobals = UFG::D3DGlobals_t::Get();

    while (!pD3DGlobals->m_DXGISwapChain) {
        Sleep(10);
    }

    if (!Render::Initialize(UFG::Global::GetWindowHandle(), pD3DGlobals->m_Device, pD3DGlobals->m_DeviceCtx))
    {
        FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(p_Reserved), 0x0);
        return 0;
    }

    Hooks::Initialize();

    while (!GetAsyncKeyState(VK_END)) {
        Sleep(10);
    }

    Hooks::Uninitialize();

    Sleep(100); // Wait for frame to finish

    Render::Uninitialize();

    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(p_Reserved), 0x0);
    return 0;
}

int __stdcall DllMain(HMODULE p_Module, DWORD p_Reason, void* p_Reserved)
{
    if (p_Reason == DLL_PROCESS_ATTACH)
    {
        HANDLE hThread = CreateThread(0, 0, MainThread, p_Module, 0, 0);
        if (!hThread) {
            return 0;
        }

        CloseHandle(hThread);
    }

    return 1;
}