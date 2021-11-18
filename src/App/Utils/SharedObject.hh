//
// Created by fleur on 15/11/2021.
//

#ifndef GOLPHOOK_FUN_SHAREDOBJECT_HH
#define GOLPHOOK_FUN_SHAREDOBJECT_HH

#include "memory"

template<class T>
class SharedObject {

    public:
         static inline std::unique_ptr<T> shared;

         static T& Get() noexcept {
             return *T::shared;
         }

         static void makeShared() noexcept {
             if (!T::shared) {
                 T::shared = std::make_unique<T>();
             }
         }
};

#endif //GOLPHOOK_FUN_SHAREDOBJECT_HH
