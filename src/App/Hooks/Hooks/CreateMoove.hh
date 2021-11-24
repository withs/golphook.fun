//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_CREATEMOOVE_HH
#define GOLPHOOK_FUN_CREATEMOOVE_HH

#include "CommonIncludes.hh"

#include "App.hh"

typedef bool(__thiscall* oFnCreateMoove)(IBaseClientDLL*, int, float, bool);

class CreateMoove {
    public:
         static inline oFnCreateMoove original;
         static bool __stdcall hooked(int sequence_number, float input_sample_frametime, bool active, bool bSendPacket);
         static void __stdcall proxy(int sequence_number, float input_sample_frametime, bool active);
};

#endif //GOLPHOOK_FUN_CREATEMOOVE_HH
