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
#define NK_INCLUDE_STANDARD_BOOL
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
                    nk_checkbox_label(this->_ctx, "Boxes", &Config::Get().currentCfg().boxe);

                    if ( Config::Get().currentCfg().boxe ) {
                        nk_layout_row_push(this->_ctx, 0.25f);
                        if ( nk_combo_begin_color(this->_ctx, nk_rgb_cf(static_cast<nk_colorf>(Config::Get().currentCfg().boxeCol)), nk_vec2(300,400)) ) {
                            nk_layout_row_dynamic(this->_ctx, 120, 1);

                            nk_colorf bg = static_cast<nk_colorf>(Config::Get().currentCfg().boxeCol);

                            bg = nk_color_picker(this->_ctx, bg, NK_RGBA);
                            nk_layout_row_dynamic(this->_ctx, 25, 1);
                            bg.r = nk_propertyf(this->_ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
                            bg.g = nk_propertyf(this->_ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
                            bg.b = nk_propertyf(this->_ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
                            bg.a = nk_propertyf(this->_ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);

                            Config::Get().currentCfg().boxeCol = Color_t(bg);
                            nk_combo_end(this->_ctx);
                        }
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
                    nk_checkbox_label(this->_ctx, "Snapline", &(Config::Get().currentCfg().snaplines));

                    if ( Config::Get().currentCfg().snaplines ) {
                        nk_layout_row_push(this->_ctx, 0.25f);

                        if ( nk_combo_begin_color(this->_ctx, nk_rgb_cf(static_cast<nk_colorf>(Config::Get().currentCfg().snaplinesCol)), nk_vec2(300,400)) ) {
                            nk_layout_row_dynamic(this->_ctx, 120, 1);

                            nk_colorf bg = static_cast<nk_colorf>(Config::Get().currentCfg().snaplinesCol);

                            bg = nk_color_picker(this->_ctx, bg, NK_RGBA);
                            nk_layout_row_dynamic(this->_ctx, 25, 1);
                            bg.r = nk_propertyf(this->_ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
                            bg.g = nk_propertyf(this->_ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
                            bg.b = nk_propertyf(this->_ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
                            bg.a = nk_propertyf(this->_ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);

                            Config::Get().currentCfg().snaplinesCol = Color_t(bg);
                            nk_combo_end(this->_ctx);
                        }

                    }
                    nk_layout_row_end(this->_ctx);

                    nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);

                    nk_layout_row_push(this->_ctx, 0.75f);
                    nk_checkbox_label(this->_ctx, "Watermark", &Config::Get().currentCfg().watermark);

                    if ( Config::Get().currentCfg().watermark ) {
                        nk_layout_row_push(this->_ctx, 0.25f);

                        if ( nk_combo_begin_color(this->_ctx, nk_rgb_cf(static_cast<nk_colorf>(Config::Get().currentCfg().watermarkCol)), nk_vec2(300,400)) ) {
                            nk_layout_row_dynamic(this->_ctx, 120, 1);

                            nk_colorf bg = static_cast<nk_colorf>(Config::Get().currentCfg().watermarkCol);

                            bg = nk_color_picker(this->_ctx, bg, NK_RGBA);
                            nk_layout_row_dynamic(this->_ctx, 25, 1);
                            bg.r = nk_propertyf(this->_ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
                            bg.g = nk_propertyf(this->_ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
                            bg.b = nk_propertyf(this->_ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
                            bg.a = nk_propertyf(this->_ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);

                            Config::Get().currentCfg().watermarkCol = Color_t(bg);
                            nk_combo_end(this->_ctx);
                        }

                    }
                    nk_layout_row_end(this->_ctx);


                    nk_group_end(this->_ctx);
                }

                if ( nk_group_begin(this->_ctx, "Visuals2", NK_WINDOW_BORDER) ) {


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

                    nk_group_end(this->_ctx);
                }

                if (nk_group_begin(this->_ctx, "Group_top", NK_WINDOW_BORDER)) {
                    nk_layout_row_begin(this->_ctx, NK_DYNAMIC, 25, 2);

                    nk_layout_row_push(this->_ctx, 0.50f);
                    if ( nk_button_label(this->_ctx, "load") )
                        Config::Get().loadConfigFromName("b");

                    nk_layout_row_push(this->_ctx, 0.50f);
                    if ( nk_button_label(this->_ctx, "save") )
                        Config::Get().saveConfigToFile("b");

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

void Menu::renderShadow() {
    D3DXVECTOR2 line[2];
    line[0] = D3DXVECTOR2(1.f, 1.f);
    line[1] = D3DXVECTOR2(App::Get().io.windWidth * 1.f, 1.f);
    DrawItemsCollection::Get().l_line->SetWidth((App::Get().io.windHeight * 2.f));
    DrawItemsCollection::Get().l_line->Draw(line, 2, D3DCOLOR_ARGB(40, 0, 0, 0));
}
