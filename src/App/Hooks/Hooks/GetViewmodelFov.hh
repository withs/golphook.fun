//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_GETVIEWMODELFOV_HH
#define GOLPHOOK_FUN_GETVIEWMODELFOV_HH

#include "App.hh"

typedef float(__stdcall *oFnGetViewmodelFov)();

class GetViewmodelFov {
    public:
         static inline oFnGetViewmodelFov original;
         static float __stdcall hooked();
};


#endif //GOLPHOOK_FUN_GETVIEWMODELFOV_HH
