//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_DRAWITEMSCOLLECTION_HH
#define GOLPHOOK_FUN_DRAWITEMSCOLLECTION_HH

#include "Utils/SharedObject.hh"

#include "Hooks/Hooks/EndScene.hh"

#include "d3d9.h"
#include "d3dx9.h"

class DrawItemsCollection: public SharedObject<DrawItemsCollection> {

    public:
         DrawItemsCollection();
         ~DrawItemsCollection();

         ID3DXFont* f_lucida;
         ID3DXLine* l_line;
};


#endif //GOLPHOOK_FUN_DRAWITEMSCOLLECTION_HH
