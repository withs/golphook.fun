//
// Created by fleur on 14/11/2021.
//

#include "DrawTools.hh"

#include "DrawItemsCollection.hh"

bool DrawRectb::draw() {
    float boxHeight = this->_height > this->_pos.y ? (this->_height - this->_pos.y):(this->_pos.y - this->_height);
    float boxWidth = boxHeight / 3.5f;

    /*
     *                 (-)
     *                  ^
     *                  |
     *                  |
     *  x (-) <- ---------------- -> (+)
     *                  |
     *                  |
     *                  v
     *                 (+)
     *                  y
     * */


    // ligne bas
    int32_t x1 = this->_pos.x - boxWidth;
    int32_t y1 = this->_pos.y;
    int32_t x2 = this->_pos.x + boxWidth;
    int32_t y2 = this->_pos.y;
    DrawLineb({x1, y1}, {x2, y2}, 1.3f, this->_color).draw();

    // ligne haut
    x1 = x1;
    y1 = this->_pos.y - boxHeight;
    x2 = x2;
    y2 = this->_pos.y - boxHeight;
    DrawLineb({x1, y1}, {x2, y2}, 1.3f, this->_color).draw();

    // ligne guauche
    x1 = this->_pos.x - boxWidth;
    y1 = this->_pos.y;
    x2 = this->_pos.x - boxWidth;
    y2 = this->_pos.y - boxHeight;
    DrawLineb({x1, y1}, {x2, y2}, 1.3f, this->_color).draw();

    // ligne droite
    x1 = this->_pos.x + boxWidth;
    y1 = this->_pos.y;
    x2 = this->_pos.x + boxWidth;
    y2 = this->_pos.y - boxHeight;
    DrawLineb({x1, y1}, {x2, y2}, 1.3f, this->_color).draw();


    /*
    uint32_t x1 = this->_pos.x - boxWidth;
    uint32_t y1 = this->_pos.y;
    uint32_t x2 = this->_pos.x + boxWidth;
    uint32_t y2 = this->_pos.y;

    DrawLineb({x1, y1}, {x2, y2}, 1.3f, this->_color).draw();

    x1 = x1;
    y1 = this->_pos.y;
    x2 = x1;
    y2 = this->_pos.y - boxHeight;
    DrawLineb({x1, y1}, {x2, y2}, 1.3f, this->_color).draw();

    x1 = this->_pos.x + boxWidth;
    y1 = this->_pos.y;
    x2 = this->_pos.x + boxWidth;
    y2 = this->_pos.y - boxHeight;
    DrawLineb({x1, y1}, {x2, y2}, 1.3f, this->_color).draw();

    x1 = this->_pos.x - boxWidth;
    y1 = this->_pos.y - boxHeight;
    x2 = this->_pos.x + boxWidth;
    y2 = this->_pos.y - boxHeight;
    DrawLineb({x1, y1}, {x2, y2}, 1.3f, this->_color).draw();
    */

    return true;
}

bool DrawTextb::draw() {
    RECT rect;
    SetRect(&rect, this->_pos.x, this->_pos.y, 0, 0);
    DrawItemsCollection::Get().f_lucidaMed->DrawTextA(NULL, this->_content.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, static_cast<D3DCOLOR>(this->_color));
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
