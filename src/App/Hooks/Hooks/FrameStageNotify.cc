//
// Created by fleur on 14/11/2021.
//

#include "FrameStageNotify.hh"


void __stdcall FrameStageNotify::hooked(int32_t dum) {

    if ( App::Get().ready ) {
        int32_t w, h;
        InterfacesCollection::i_engineClient->GetScreenSize(w, h);
        App::Get().io.windHeight= h;
        App::Get().io.windWidth = w;
        FrameStageNotify::original(dum);

        App::Get().localPlayer = InterfacesCollection::i_entityList->getClientEntity(
                InterfacesCollection::i_engineClient->GetLocalPlayer()
        );

        App::Get().collectEntities();
        Features::Get().engine->onFrame();
        Features::Get().visuals->onFrame();
        Features::Get().others->onFrame();
        Features::Get().skins->onFrame();
        App::Get().entityList.clear();
    }
}