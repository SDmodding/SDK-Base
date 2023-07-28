#pragma once

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