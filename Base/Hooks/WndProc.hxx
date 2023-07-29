#pragma once

// More Info: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Hook
{
    typedef LRESULT(__stdcall* m_tWndProc)(HWND, UINT, WPARAM, LPARAM);
    m_tWndProc m_oWndProc;

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
                    m_SpecialKeyPressed = true;
                }
            }
            else
                m_SpecialKeyPressed = false;

        }

        UFG::Input::EnableGameInput(!Render::m_Visible);

        return CallWindowProcA(m_oWndProc, p_Window, p_Msg, p_WParam, p_LParam);
    }
}