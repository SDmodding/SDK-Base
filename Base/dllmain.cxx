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
    uint8_t m_GameStateInGameCounter = 0;
}

#include "Renderer.hxx"
#include "Hooks.hxx"

DWORD __stdcall MainThread(void* p_Reserved)
{
    while (!(*UFG::Global::DXGISwapChain))
        Sleep(10);

    if (!Render::Initialize(*UFG::Global::Window, reinterpret_cast<ID3D11Device*>(*UFG::Global::D3D11Device), reinterpret_cast<ID3D11DeviceContext*>(*UFG::Global::D3D11DeviceContext)))
    {
        FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(p_Reserved), 0x0);
        return 0;
    }

    Hooks::Initialize();

    while (!GetAsyncKeyState(VK_END))
        Sleep(10);

    Hooks::Uninitialize();

    Sleep(100); // Wait for frame to finish

    UFG::Input::EnableGameInput(true); // Reset input...
    Render::Uninitialize();

    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(p_Reserved), 0x0);
    return 0;
}

int __stdcall DllMain(HMODULE p_Module, DWORD p_Reason, void* p_Reserved)
{
    if (p_Reason == DLL_PROCESS_ATTACH)
    {
        HANDLE m_Thread = CreateThread(0, 0, MainThread, p_Module, 0, 0);
        if (!m_Thread)
            return 0;

        CloseHandle(m_Thread);
    }

    return 1;
}