//
// Created by fleur on 14/11/2021.
//

#include "DrawTools.hh"

#include "DrawItemsCollection.hh"

bool DrawRect::draw() {
    return true;
}

bool DrawTextb::draw() {
    RECT rect;
    SetRect(&rect, this->_pos.x, this->_pos.y, 0, 0);
    DrawItemsCollection::Get().f_lucida->DrawTextA(NULL, this->_content.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, static_cast<D3DCOLOR>(this->_color));
    return true;
}
