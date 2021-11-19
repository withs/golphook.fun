//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_DRAWTOOLS_HH
#define GOLPHOOK_FUN_DRAWTOOLS_HH


#include "Utils/Structs/Color.hh"
#include "Utils/Structs/Vector.hh"


struct DrawToolBase {

    constexpr DrawToolBase() = default;
    inline ~DrawToolBase() = default;;

    Color_t _color { };
    Vec2<uint32_t> _pos { };

    uint32_t a = 0;

    virtual bool draw() = 0;
};

struct DrawRect final: public DrawToolBase {
    Color_t _color { };
    Vec2<uint32_t> _pos { };

    DrawRect(Vec2<uint32_t> toPos, Color_t andColor) {
        this->_pos = toPos;
        this->_color = andColor;
    };
    bool draw() override;

    constexpr DrawRect() = default;
    inline ~DrawRect() = default;;
};

struct DrawLineb final: public DrawToolBase {

    Color_t _color { };
    Vec2<uint32_t> _pos { };
    Vec2<uint32_t> _pos2 { };
    float _thickness;

    DrawLineb(Vec2<uint32_t> fromPos, Vec2<uint32_t> toPos, float andThickness, Color_t andColor) {
        this->_pos = fromPos;
        this->_pos2 = toPos;
        this->_color = andColor;
        this->_thickness = andThickness;
    };
    bool draw() override;

    constexpr DrawLineb() = default;
    inline ~DrawLineb() = default;;
};

struct DrawTextb final: public DrawToolBase {

    std::string _content;
    Color_t _color { };
    Vec2<uint32_t> _pos { };


    DrawTextb(Vec2<uint32_t> toPos, std::string withText, Color_t andColor) {
        this->_pos = toPos;
        this->_color = andColor;
        this->_content = withText;
    };
    bool draw() override;

    constexpr DrawTextb() = default;
    inline ~DrawTextb() = default;;
};


#endif //GOLPHOOK_FUN_DRAWTOOLS_HH
