//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_COLOR_HH
#define GOLPHOOK_FUN_COLOR_HH

#include "CommonIncludes.hh"

#include "d3d9.h"
#include "d3dx9.h"

struct Color_t {
    public:

         uint32_t r, g, b, a;

         Color_t(): r(0), g(0), b(0), a(0) {}

        Color_t(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
            : r(r), g(g), b(b), a(a) {}

        Color_t(float r, float g, float b, float a) {
            this->r = r * 255;
            this->g = g * 255;
            this->b = b * 255;
            this->a = a * 255;
        }

         Color_t(nk_color withNkColor) {
             this->r = withNkColor.r;
             this->g = withNkColor.g;
             this->b = withNkColor.b;
             this->a = withNkColor.a;
         };

         Color_t(nk_colorf withNkColorf) {
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

             if ( (_r = this->r * 255.f) == 255 ) _r = 1.f;
             if ( (_g = this->g * 255.f) == 255 ) _g = 1.f;
             if ( (_b = this->b * 255.f) == 255 ) _b = 1.f;
             if ( (_a = this->a * 255.f) == 255 ) _a = 1.f;

             return nk_colorf(_r, _g, _b, _a);
         }
};


#endif //GOLPHOOK_FUN_COLOR_HH
