//
// Created by fleur on 14/11/2021.
//

#include "FrameStageNotify.hh"


void __stdcall FrameStageNotify::hooked(int32_t dum) {
    int32_t w, h;
    InterfacesCollection::i_engineClient->GetScreenSize(w, h);
    App::Get().io.windHeight= h;
    App::Get().io.windWidth = w;
    FrameStageNotify::original(dum);
}