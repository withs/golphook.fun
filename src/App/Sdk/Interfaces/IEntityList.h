//
// Created by fleur on 18/11/2021.
//

#ifndef GOLPHOOK_FUN_IENTITYLIST_H
#define GOLPHOOK_FUN_IENTITYLIST_H

#include "Sdk/Classes/Entity.hh"

class EntityList {
    public:
         Entity_t* getClientEntity(int32_t index) {
             return Mem::callVirtual< Entity_t*, 3, int32_t >(this, index);
         }

         Entity_t* getClientEntityHandle(int32_t handle) {
             return Mem::callVirtual< Entity_t*, 4, int32_t >(this, handle);
         }

         int32_t getHighestIndex() {
             return Mem::callVirtual< int32_t, 6 >(this);
         }
};

#endif //GOLPHOOK_FUN_IENTITYLIST_H
