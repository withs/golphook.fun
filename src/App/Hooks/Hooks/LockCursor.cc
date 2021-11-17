//
// Created by fleur on 14/11/2021.
//

#include "LockCursor.hh"

void __thiscall LockCursor::hooked() {
    if(Menu::Get().isMenuOpened)
        return InterfacesCollection::i_surface->UnlockCursor();

    LockCursor::original(InterfacesCollection::i_surface);

}