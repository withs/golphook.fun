//
// Created by fleur on 14/11/2021.
//

#include "Menu.hh"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_D3D9_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_d3d9.h"


void Menu::bootstrap() {

    this->_ctx = nk_d3d9_init(EndScene::d3dDevice, App::Get().io.windWidth, App::Get().io.windHeight);
    struct nk_font_atlas* atlas;
    nk_d3d9_font_stash_begin(&atlas);
    nk_d3d9_font_stash_end();
}

void Menu::release() {

    this->isMenuOpened = false;

    SetWindowLongA(FindWindowA("Valve001", nullptr), GWL_WNDPROC, reinterpret_cast<LONG>(WndProc::original));

    nk_d3d9_shutdown();

}

nk_bool check = 0;

void Menu::render() {

    if( nk_begin(this->_ctx, "Golphook v0.4.3-alpha", nk_rect(100, 100, 670, 274), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_NO_SCROLLBAR) ) {

        nk_layout_row_dynamic(this->_ctx, 20, 5);
        if ( nk_selectable_label(this->_ctx, "Visuals", NK_TEXT_CENTERED, &this->_tabsHighlight[0]) ) {
            this->_currentTab = MenuTabs::VISUALS;
            for ( auto& bo: this->_tabsHighlight ) bo = 0;
            this->_tabsHighlight[0] = 1;
        }
        if ( nk_selectable_label(this->_ctx, "Engine", NK_TEXT_CENTERED, &this->_tabsHighlight[1]) ) {
            this->_currentTab = MenuTabs::ENGINE;
            for ( auto& bo: this->_tabsHighlight ) bo = 0;
            this->_tabsHighlight[1] = 1;
        }
        if ( nk_selectable_label(this->_ctx, "VHV", NK_TEXT_CENTERED, &this->_tabsHighlight[2]) ) {
            this->_currentTab = MenuTabs::VHV;
            for ( auto& bo: this->_tabsHighlight ) bo = 0;
            this->_tabsHighlight[2] = 1;
        }

        if ( nk_selectable_label(this->_ctx, "Skins", NK_TEXT_CENTERED, &this->_tabsHighlight[3]) ) {
            this->_currentTab = MenuTabs::SKINS;
            for ( auto& bo: this->_tabsHighlight ) bo = 0;
            this->_tabsHighlight[3] = 1;
        }

        if ( nk_selectable_label(this->_ctx, "Others", NK_TEXT_CENTERED, &this->_tabsHighlight[4]) ) {
            this->_currentTab = MenuTabs::OTHERS;
            for ( auto& bo: this->_tabsHighlight ) bo = 0;
            this->_tabsHighlight[4] = 1;
        }

        switch ( this->_currentTab ) {
            case ::VISUALS:

                nk_layout_row_dynamic(this->_ctx, 270, 2);

                if ( nk_group_begin(this->_ctx, "Visuals1", NK_WINDOW_BORDER) ) {

                    nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);

                    nk_layout_row_push(this->_ctx, 0.75f);
                    nk_checkbox_label(this->_ctx, "Boxes", &check);

                    if ( check ) {
                        nk_layout_row_push(this->_ctx, 0.25f);
                        nk_button_label(this->_ctx, "#FFBB");
                    }
                    nk_layout_row_end(this->_ctx);

                    if ( check ) {
                        nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);

                        nk_layout_row_push(this->_ctx, 1.f);
                        nk_checkbox_label(this->_ctx, "Names", &check);

                        nk_layout_row_end(this->_ctx);

                        nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);

                        nk_layout_row_push(this->_ctx, 1.f);
                        nk_checkbox_label(this->_ctx, "Health bar", &check);

                        nk_layout_row_end(this->_ctx);

                        nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);

                        nk_layout_row_push(this->_ctx, 1.f);
                        nk_checkbox_label(this->_ctx, "Flags", &check);

                        nk_layout_row_end(this->_ctx);

                        nk_layout_row_push(this->_ctx, 1.f);
                        nk_checkbox_label(this->_ctx, "Weapon", &check);

                        nk_layout_row_end(this->_ctx);
                    }

                    nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);

                    nk_layout_row_push(this->_ctx, 0.75f);
                    nk_checkbox_label(this->_ctx, "Snapline", &check);

                    if ( check ) {
                        nk_layout_row_push(this->_ctx, 0.25f);
                        nk_button_label(this->_ctx, "#FFBB");
                    }
                    nk_layout_row_end(this->_ctx);


                    nk_group_end(this->_ctx);
                }

                if ( nk_group_begin(this->_ctx, "Visuals2", NK_WINDOW_BORDER) ) {

                    nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);

                    nk_layout_row_push(this->_ctx, 0.75f);
                    nk_checkbox_label(this->_ctx, "check", &check);

                    nk_layout_row_push(this->_ctx, 0.25f);
                    nk_button_label(this->_ctx, "#FFBB");

                    nk_layout_row_end(this->_ctx);


                    nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);

                    nk_layout_row_push(this->_ctx, 0.75f);
                    nk_checkbox_label(this->_ctx, "check", &check);

                    nk_layout_row_push(this->_ctx, 0.25f);
                    nk_button_label(this->_ctx, "#FFBB");

                    nk_layout_row_end(this->_ctx);

                    nk_group_end(this->_ctx);
                }

                break;
            case ::ENGINE:
                break;
            case ::VHV:
                break;
            case ::SKINS:
                break;
            case ::OTHERS:

                nk_layout_row_dynamic(this->_ctx, 270, 2);

                if (nk_group_begin(this->_ctx, "Group_top", NK_WINDOW_BORDER)) {
                    nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);
                    nk_layout_row_push(this->_ctx, 0.75f);
                    nk_checkbox_label(this->_ctx, "check", &check);
                    nk_layout_row_push(this->_ctx, 0.25f);
                    nk_button_label(this->_ctx, "#FFBB");
                    nk_layout_row_end(this->_ctx);

                    nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);
                    nk_layout_row_push(this->_ctx, 0.75f);
                    nk_checkbox_label(this->_ctx, "check", &check);
                    nk_layout_row_push(this->_ctx, 0.25f);
                    nk_button_label(this->_ctx, "#FFBB");
                    nk_layout_row_end(this->_ctx);

                    nk_group_end(this->_ctx);
                }

                if (nk_group_begin(this->_ctx, "Group_top", NK_WINDOW_BORDER)) {
                    nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);
                    nk_layout_row_push(this->_ctx, 0.75f);
                    nk_checkbox_label(this->_ctx, "check", &check);
                    nk_layout_row_push(this->_ctx, 0.25f);
                    nk_button_label(this->_ctx, "#FFBB");
                    nk_layout_row_end(this->_ctx);

                    nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);
                    nk_layout_row_push(this->_ctx, 0.75f);
                    nk_checkbox_label(this->_ctx, "check", &check);
                    nk_layout_row_push(this->_ctx, 0.25f);
                    nk_button_label(this->_ctx, "#FFBB");
                    nk_layout_row_end(this->_ctx);

                    nk_group_end(this->_ctx);
                }

                break;
        }

        nk_end(this->_ctx);
        nk_d3d9_render(NK_ANTI_ALIASING_ON);

        nk_input_begin(this->_ctx);
        nk_input_end(this->_ctx);

    }
}
