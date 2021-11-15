//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_APP_HH
#define GOLPHOOK_FUN_APP_HH

#include "CommonIncludes.hh"

#include "Utils/SharedObject.hh"
#include "Utils/Utils.hh"

#include "MinHook.h"

class App: public SharedObject<App> {
    public:

         static void init(HMODULE withModuleHandle);
         void run();

};


#endif //GOLPHOOK_FUN_APP_HH
