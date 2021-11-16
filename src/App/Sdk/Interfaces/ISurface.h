//
// Created by fleur on 16/11/2021.
//

#ifndef GOLPHOOK_FUN_ISURFACE_H
#define GOLPHOOK_FUN_ISURFACE_H

#include "Utils/Memory/Mem.hh"

class ISurface {
    public:
         void UnlockCursor() {
             return Mem::callVirtual<void, 66>(this);
         }
         void LockCursor() {
             return Mem::callVirtual<void, 67>(this);
         }
};

#endif //GOLPHOOK_FUN_ISURFACE_H
