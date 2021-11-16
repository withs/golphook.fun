//
// Created by fleur on 16/11/2021.
//

#ifndef GOLPHOOK_FUN_ICVAR_H
#define GOLPHOOK_FUN_ICVAR_H

#include "Utils/Memory/Mem.hh"

#include "IConVar.h"

class ICvar {
    public:
         Convar* getConvar(const char* name) {
             return Mem::callVirtual< Convar*, 15, const char* >(this, name);
         }
};

#endif //GOLPHOOK_FUN_ICVAR_H
