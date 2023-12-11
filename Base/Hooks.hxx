#pragma once
#include <SDK/Libs/MinHook.h>
#pragma comment(lib, "SDK/Libs/MinHook.lib")

// Hooks
#include "Hooks/GameStateInGame.hxx"

#include "Hooks/PerformFlip.hxx"
#include "Hooks/WndProc.hxx"

namespace Hooks
{
	void Initialize()
	{
		MH_Initialize();

		MH_CreateHook(UFG_RVA_PTR(0x412240), Hook::GameStateInGameUpdate, (void**)&Hook::m_oGameStateInGameUpdate);
		MH_CreateHook(UFG_RVA_PTR(0x6A08A0), Hook::PerformFlip, (void**)&Hook::m_oPerformFlip);

		Hook::m_oWndProc = WNDPROC(SetWindowLongPtrA(UFG::Global::GetWindowHandle(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Hook::WndProc)));
	}

	void Uninitialize()
	{
		SetWindowLongPtrA(UFG::Global::GetWindowHandle(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hook::m_oWndProc));

		MH_Uninitialize();
	}
}