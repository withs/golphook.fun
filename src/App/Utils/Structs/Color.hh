//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_COLOR_HH
#define GOLPHOOK_FUN_COLOR_HH

#include "CommonIncludes.hh"

#include "d3d9.h"
#include "d3dx9.h"
#include "nuklear.h"

struct Color_t {
    public:
         int32_t r, g, b, a;

         Color_t(): r(255), g(255), b(255), a(255) {}

        Color_t(int32_t r, int32_t g, int32_t b, int32_t a) {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
         }

         Color_t(float _r, float _g, float _b, float _a)
                 : Color_t(
                     static_cast<int>(_r * 255.0f),
                     static_cast<int>(_g * 255.0f),
                     static_cast<int>(_b * 255.0f),
                     static_cast<int>(_a * 255.0f)) {}

         explicit Color_t(nk_color withNkColor) {
             this->r = withNkColor.r;
             this->g = withNkColor.g;
             this->b = withNkColor.b;
             this->a = withNkColor.a;
         };

         explicit Color_t(nk_colorf withNkColorf) {
             this->r = withNkColorf.r * 255;
             this->g = withNkColorf.g * 255;
             this->b = withNkColorf.b * 255;
             this->a = withNkColorf.a * 255;
         };

         operator D3DCOLOR() {
            return D3DCOLOR_RGBA(this->r, this->g, this->b, this->a);
         }

         operator nk_color() {
            return nk_color(this->r, this->g, this->b, this->a);
         }

         operator nk_colorf() {

             float _r, _g, _b, _a;

             if ( (_r = this->r / 255.f) == 255 ) _r = 1.f;
             if ( (_g = this->g / 255.f) == 255 ) _g = 1.f;
             if ( (_b = this->b / 255.f) == 255 ) _b = 1.f;
             if ( (_a = this->a / 255.f) == 255 ) _a = 1.f;

             return nk_colorf(_r, _g, _b, _a);
         }
};


#endif //GOLPHOOK_FUN_COLOR_HH


/*
 * 255 145
 * 1.0 0.56
 */