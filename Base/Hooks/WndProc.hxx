//=============================================================================
// 
// Description:		Basically WndProc more info here:
//					https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc
// 
//=============================================================================
#pragma once

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Hook
{
    WNDPROC m_oWndProc;

    LRESULT __stdcall WndProc(HWND p_Window, UINT p_Msg, WPARAM p_WParam, LPARAM p_LParam)
    {
        ImGui_ImplWin32_WndProcHandler(p_Window, p_Msg, p_WParam, p_LParam);

        static constexpr WPARAM m_SpecialKey = VK_INSERT;
        static bool m_SpecialKeyPressed = false;
        if (p_WParam == m_SpecialKey)
        {
            if (p_Msg == WM_KEYDOWN || p_Msg == WM_SYSKEYDOWN)
            {
                if (!m_SpecialKeyPressed)
                {
                    Render::m_Visible = !Render::m_Visible;
                    if (!Render::m_Visible) {
                        UFG::Input::EnableGameInput(true);
                    }
                    m_SpecialKeyPressed = true;
                }
            }
            else
                m_SpecialKeyPressed = false;

        }

        if (Render::m_Visible) {
            UFG::Input::EnableGameInput(false);
        }

        return CallWindowProcA(m_oWndProc, p_Window, p_Msg, p_WParam, p_LParam);
    }
}