//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_HOOKSCONTROLLER_HH
#define GOLPHOOK_FUN_HOOKSCONTROLLER_HH

#include "CommonIncludes.hh"
#include "../Utils/Utils.hh"
#include "../Utils/SharedObject.hh"

#include "Hooks/EndScene.hh"
#include "Hooks/WndProc.hh"

#include "MinHook.h"

class Hooks: public SharedObject<Hooks> {
    public:
         Hooks();
         void removeHooks();
    private:
         void _applyHook(uintptr_t* toAddress, uintptr_t* withDetour, uintptr_t* withOriginal, std::string andHookName);
};


#endif //GOLPHOOK_FUN_HOOKSCONTROLLER_HH
