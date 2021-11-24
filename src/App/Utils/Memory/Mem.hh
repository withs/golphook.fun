//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_MEM_HH
#define GOLPHOOK_FUN_MEM_HH

#include "CommonIncludes.hh"

class Mem {
    public:

        // from https://github.com/withs/golphook/blob/8c984421b200d56a5d76c4717766aecb3ad06d45/golphook/src/App/Mem/Mem.cc#L70
        static uint8_t* patternScan(void* module, const char* signature);

         // from https://github.com/bruhmoment21/csgo-imgui-sdk/blob/c35ab6965c36e696fc6a4fd5b204967d82508306/jet-sdk-csgo/src/utilities.hpp#L27
        template <typename T, uint32_t atIndex, typename ...Arguments>
        static auto callVirtual(void* const thisClass, Arguments... args) noexcept {
            using fn = T(__thiscall***)(void*, Arguments...);
            return ((*static_cast<fn>(thisClass))[atIndex])(thisClass, args...);
        }

        static auto getVirtual(void* const thisClass, const uint32_t atIndex) noexcept {
            return reinterpret_cast<void*>((*static_cast<int**>(thisClass))[atIndex]);
        }

         template <class T>
         static T getValOffset(uintptr_t withOffset, void* inObject) {
             return *(reinterpret_cast< T* >((uintptr_t)inObject + withOffset));
         }

         template <class T>
         static void setValOffset(T forValue, uintptr_t withOffset, void* inObject) {
             *(reinterpret_cast< T* >((uintptr_t)inObject + withOffset)) = forValue;
         }
};


#endif //GOLPHOOK_FUN_MEM_HH
