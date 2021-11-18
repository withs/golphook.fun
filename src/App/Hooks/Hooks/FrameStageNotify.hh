//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_FRAMESTAGENOTIFY_HH
#define GOLPHOOK_FUN_FRAMESTAGENOTIFY_HH

#include "CommonIncludes.hh"

#include "App.hh"

typedef void(__stdcall* oFnFrameStageNotify)(int32_t);

class FrameStageNotify {
    public:
         static inline oFnFrameStageNotify original;
         static void __stdcall hooked(int32_t dum);
};


#endif //GOLPHOOK_FUN_FRAMESTAGENOTIFY_HH
