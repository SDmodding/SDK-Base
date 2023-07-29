#pragma once

/*
* Main game-thread:
* This is called each frame when you're in-game. Here you need to do everything related to transform/calling game-thread safe functions, etc...
*/

namespace Hook
{
    typedef void(__fastcall* m_tGameStateInGameUpdate)(void*, float);
    m_tGameStateInGameUpdate m_oGameStateInGameUpdate;

    void __fastcall GameStateInGameUpdate(void* p_GameState, float p_TimeDelta)
    {
        m_oGameStateInGameUpdate(p_GameState, p_TimeDelta);

        Global::m_GameStateInGameCounter++;
    }
}