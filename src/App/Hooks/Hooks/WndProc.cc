//
// Created by fleur on 14/11/2021.
//

#include "WndProc.hh"

bool __stdcall WndProc::hooked(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam) {
    if ( uMsg == WM_KEYUP ) {
        if ( wParam == VK_INSERT ) {
            Menu::Get().isMenuOpened = !(Menu::Get().isMenuOpened);
        }
    }

    if ( Menu::Get().isMenuOpened )
        if (nk_d3d9_handle_event(hWnd, uMsg, wParam, lParam))
            return 0;

    return CallWindowProcW(WndProc::original, hWnd, uMsg, wParam, lParam);
}