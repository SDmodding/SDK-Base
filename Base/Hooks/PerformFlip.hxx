#pragma once

/*
* Main DX11 Render Thread:
* This is called each frame before calling IDXGISwapChain::Present.
* More info: https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiswapchain-present
* Calling original will call the present.
*/

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