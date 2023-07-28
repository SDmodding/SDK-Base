#pragma once

namespace Hook
{
    typedef bool(__fastcall* m_tPerformFlip)(uint32_t);
    m_tPerformFlip m_oPerformFlip;

    bool __fastcall PerformFlip(uint32_t p_SyncInterval)
    {
        Render::OnFrame();

        return m_oPerformFlip(p_SyncInterval);
    }
}