//
// Created by fleur on 14/11/2021.
//

#include "CreateMoove.hh"

bool __stdcall CreateMoove::hooked(float dum, void* dumm) {

    CreateMoove::original(dum, dumm);
    App::Get().caca();
    if ( App::Get().ready )
        Features::Get().visuals->onCreateMoove();

    return false;
}