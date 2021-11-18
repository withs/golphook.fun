//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_WNDPROC_HH
#define GOLPHOOK_FUN_WNDPROC_HH

#include "CommonIncludes.hh"

#include "App.hh"

#include "nuklear.h"
#include "nuklear_d3d9.h"

class WndProc {
    public:
         static inline WNDPROC original;
         static bool __stdcall hooked(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam);
};


#endif //GOLPHOOK_FUN_WNDPROC_HH
