//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_FEATURES_HH
#define GOLPHOOK_FUN_FEATURES_HH

#include "CommonIncludes.hh"

#include "Sdk/Interfaces/Math/VMatrix.hpp"

#include "Utils/SharedObject.hh"

#include "App.hh"

#include "Features/Visuals.hh"
#include "Features/Movements.hh"
#include "Features/Others.hh"
#include "Features/Engine.hh"
#include "Features/Skins.hh"


class Features: public SharedObject<Features> {
    public:
         std::unique_ptr<Visuals> visuals;
         std::unique_ptr<Others> others;
         std::unique_ptr<Engine> engine;
         std::unique_ptr<Skins> skins;

         Features();
};


#endif //GOLPHOOK_FUN_FEATURES_HH
