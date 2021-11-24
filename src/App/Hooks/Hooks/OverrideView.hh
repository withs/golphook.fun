//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_OVERRIDEVIEW_HH
#define GOLPHOOK_FUN_OVERRIDEVIEW_HH

#include "App.hh"

typedef void(__stdcall *oFnOverrideView)(void*);

class OverrideView {
    public:
         static inline oFnOverrideView original;
         static void __stdcall hooked(void* pSetup);
};


#endif //GOLPHOOK_FUN_OVERRIDEVIEW_HH
