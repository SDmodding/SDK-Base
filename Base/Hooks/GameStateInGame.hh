//=============================================================================
// 
// Description:		This function is called each frame while in-game (even when in pause menu).
//					You're inside game-thread, do everything here if you want to spawn object,
//                  change object transform, etc...
// 
//=============================================================================
#pragma once

namespace Hook
{
    typedef void(__fastcall* Fn_GameStateInGameUpdate)(void*, float);
    Fn_GameStateInGameUpdate g_GameStateInGameUpdate;

    void __fastcall GameStateInGameUpdate(void* p_GameState, float p_TimeDelta)
    {
        g_GameStateInGameUpdate(p_GameState, p_TimeDelta);

        Global::g_GameStateInGameCounter++;
    }
}