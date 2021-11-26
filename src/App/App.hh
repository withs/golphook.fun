//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_APP_HH
#define GOLPHOOK_FUN_APP_HH

#include "CommonIncludes.hh"

#include "Utils/Utils.hh"

#include "Sdk/Interfaces.hh"
#include "Hooks/Hooks.hh"
#include "Config/Config.hh"
#include "Render/Menu.hh"
#include "Netvars/Netvars.hh"
#include "Render/DrawQueue.hh"
#include "Features/Features.hh"

struct AppIo {
    int32_t windHeight = 0;
    int32_t windWidth = 0;

    HWND windHandle = nullptr;
};

class App: public SharedObject<App> {
    public:

         bool ready = false;
         std::vector<Entity_t*> entityList = {  };
         Entity_t* localPlayer;
         CUserCmd* cmd;

         static void bootstrap(HMODULE withModuleHandle);
         void run();
         void caca();
         void collectEntities();

         AppIo io { };

};


#endif //GOLPHOOK_FUN_APP_HH
