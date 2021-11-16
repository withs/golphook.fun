//
// Created by fleur on 14/11/2021.
//

#include "thread"

#include "App/App.hh"

bool __stdcall DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if ( ul_reason_for_call == DLL_PROCESS_ATTACH ) {
        std::thread appLoop(App::bootstrap, hModule);
        appLoop.detach();
    }

    return TRUE;
}