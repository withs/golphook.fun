//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_APP_HH
#define GOLPHOOK_FUN_APP_HH

#include "CommonIncludes.hh"

#include "Utils/SharedObject.hh"
#include "Utils/Utils.hh"

#include "Sdk/Interfaces.hh"
#include "Hooks/Hooks.hh"
#include "Render/Menu.hh"

struct AppIo {
    int32_t windHeight = 0;
    int32_t windWidth = 0;

    HWND windHandle = nullptr;
};

class App: public SharedObject<App> {
    public:

         static void bootstrap(HMODULE withModuleHandle);
         void run();

         AppIo io { };

};


#endif //GOLPHOOK_FUN_APP_HH
