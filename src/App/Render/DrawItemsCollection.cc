//
// Created by fleur on 14/11/2021.
//

#include "DrawItemsCollection.hh"

DrawItemsCollection::DrawItemsCollection() {
    D3DXCreateFont(EndScene::d3dDevice, 9, 0, 500, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Lucida Console", &this->f_lucida);
    D3DXCreateLine(EndScene::d3dDevice, &this->l_line);
}

DrawItemsCollection::~DrawItemsCollection() {
    this->f_lucida->Release();
}