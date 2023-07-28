#pragma once
#include "3rdParty/MinHook.h"

// Hooks
#include "Hooks/GameStateInGame.hxx"

#include "Hooks/PerformFlip.hxx"
#include "Hooks/WndProc.hxx"

namespace Hooks
{
	void Initialize()
	{
		MH_Initialize();
		auto MH_AddHook = [](uintptr_t p_Function, void* p_Hook, void** p_Original = nullptr)
		{
			MH_CreateHook(reinterpret_cast<void*>(p_Function), p_Hook, p_Original);
			MH_EnableHook(reinterpret_cast<void*>(p_Function));
		};

		MH_AddHook(UFG_RVA(0x412240), Hook::GameStateInGameUpdate, (void**)&Hook::m_oGameStateInGameUpdate);
		MH_AddHook(UFG_RVA(0x6A08A0), Hook::PerformFlip, (void**)&Hook::m_oPerformFlip);

		Hook::m_oWndProc = WNDPROC(SetWindowLongPtrA(*UFG::Global::Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Hook::WndProc)));
	}

	void Uninitialize()
	{
		SetWindowLongPtrA(*UFG::Global::Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hook::m_oWndProc));

		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}
}