//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_CREATEMOOVE_HH
#define GOLPHOOK_FUN_CREATEMOOVE_HH

#include "CommonIncludes.hh"

#include "App.hh"

typedef bool(__stdcall* oFnCreateMoove)(float, void*);

class CreateMoove {
    public:
         static inline oFnCreateMoove original;
         static bool __stdcall hooked(float dum, void* dumm);
};


#endif //GOLPHOOK_FUN_CREATEMOOVE_HH
