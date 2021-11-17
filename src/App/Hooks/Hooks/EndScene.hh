//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_ENDSCENE_HH
#define GOLPHOOK_FUN_ENDSCENE_HH

#include "CommonIncludes.hh"
#include "../../App.hh"

#include "d3d9.h"
#include "d3dx9.h"

typedef bool(__stdcall* oFnEndScene)(LPDIRECT3DDEVICE9 withDevice);

class EndScene {
    public:
         static inline void* d3d9DeviceTable[119];
         static inline LPDIRECT3DDEVICE9 d3dDevice = nullptr;

         static inline oFnEndScene original;
         static bool __stdcall hooked(LPDIRECT3DDEVICE9 withDevice);

         static void getDevice();
};


#endif //GOLPHOOK_FUN_ENDSCENE_HH
