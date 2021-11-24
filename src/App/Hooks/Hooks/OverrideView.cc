//
// Created by fleur on 14/11/2021.
//

#include "OverrideView.hh"

void __stdcall OverrideView::hooked(void* pSetup) {

    if ( App::Get().ready ) {
        if ( InterfacesCollection::i_engineClient->IsInGame() && InterfacesCollection::i_engineClient->IsConnected() ) {
            if ( Config::Get().currentCfg().viewmodel )
                Features::Get().others->overrideViewmodel();
        }
    }

    OverrideView::original(pSetup);
}