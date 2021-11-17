//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_MENU_HH
#define GOLPHOOK_FUN_MENU_HH

#include "CommonIncludes.hh"

#include "Utils/SharedObject.hh"
#include "Hooks/Hooks.hh"

enum MenuTabs {
    VISUALS,
    ENGINE,
    VHV,
    SKINS,
    OTHERS
};

class Menu: public SharedObject<Menu> {
    private:
         struct nk_context* _ctx;
         MenuTabs _currentTab = MenuTabs::OTHERS;
         nk_bool _tabsHighlight[5] = { 0, 0 ,0 ,0, 1};

    public:
         bool isMenuOpened = false;

         void render();
         void bootstrap();
         void release();

};


#endif //GOLPHOOK_FUN_MENU_HH

