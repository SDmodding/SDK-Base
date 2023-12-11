//=============================================================================
// 
// Description:		This function is called each frame when game will render D3D11 Scene ie. Present call...
//					You can do any D3D11 stuff here.
// 
//=============================================================================
#pragma once

namespace Hook
{
    typedef bool(__fastcall* Fn_PerformFlip)(uint32_t);
    Fn_PerformFlip m_oPerformFlip;

    bool __fastcall PerformFlip(uint32_t p_SyncInterval)
    {
        Render::OnFrame();

        return m_oPerformFlip(p_SyncInterval);
    }
}