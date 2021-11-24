//
// Created by fleur on 14/11/2021.
//

#include "GetViewmodelFov.hh"
#include "App.hh"

float __stdcall GetViewmodelFov::hooked() {

    float currentViewmodFov = GetViewmodelFov::original();

    if ( App::Get().ready ) {
        if ( Config::Get().currentCfg().viewmodel )
            return Config::Get().currentCfg().viewmodelFov;
    }

    return currentViewmodFov;
}