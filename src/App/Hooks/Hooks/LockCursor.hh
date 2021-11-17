//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_LOCKCURSOR_HH
#define GOLPHOOK_FUN_LOCKCURSOR_HH

#include "App.hh"

typedef void(__thiscall* oFnLockCursor)(void*);

class LockCursor {
    public:
         static inline oFnLockCursor original;
         static void __thiscall hooked();
};


#endif //GOLPHOOK_FUN_LOCKCURSOR_HH
