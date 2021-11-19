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

bool DrawLineb::draw() {
    D3DXVECTOR2 line[2];
    line[0] = D3DXVECTOR2(this->_pos.x, this->_pos.y);
    line[1] = D3DXVECTOR2(this->_pos2.x, this->_pos2.y);

    DrawItemsCollection::Get().l_line->SetWidth(this->_thickness);
    DrawItemsCollection::Get().l_line->Draw(line, 2, static_cast<D3DCOLOR>(this->_color));
    return true;
}
