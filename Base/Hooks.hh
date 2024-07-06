#pragma once
#include <SDK/Libs/MinHook.h>
#pragma comment(lib, "SDK/Libs/MinHook.lib")

// Hooks
#include "Hooks/GameStateInGame.hh"
#include "Hooks/PerformFlip.hh"
#include "Hooks/WndProc.hh"

namespace Hooks
{
	void Initialize()
	{
		MH_Initialize();

		MH_CreateHook(UFG_RVA_PTR(0x412240), Hook::GameStateInGameUpdate, (void**)&Hook::g_GameStateInGameUpdate);
		MH_CreateHook(UFG_RVA_PTR(0x6A08A0), Hook::PerformFlip, (void**)&Hook::g_PerformFlip);

		Hook::g_WndProc = WNDPROC(SetWindowLongPtrA(UFG::Global::GetWindowHandle(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Hook::WndProc)));
	}

	void Uninitialize()
	{
		SetWindowLongPtrA(UFG::Global::GetWindowHandle(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hook::g_WndProc));

		MH_Uninitialize();
	}
}