//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_MENU_HH
#define GOLPHOOK_FUN_MENU_HH

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_STANDARD_BOOL
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
#include "nuklear_d3d9.h"

struct nk_context;

#include "CommonIncludes.hh"

#include "Utils/SharedObject.hh"

#include "Hooks/Hooks/EndScene.hh"

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
         void renderShadow();
         void bootstrap();
         void release();

};


#endif //GOLPHOOK_FUN_MENU_HH

