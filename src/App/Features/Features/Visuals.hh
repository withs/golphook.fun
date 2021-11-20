//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_VISUALS_HH
#define GOLPHOOK_FUN_VISUALS_HH

#include "Sdk/Interfaces/Math/VMatrix.hpp"

#include "Sdk/InterfacesCollection.hh"
#include "Utils/Structs/Color.hh"
#include "Utils/Math/Math.hh"

class Visuals {

    private:
         void _snapline(Entity_t* ent);
         void _boxe(Entity_t* ent);
         void _watermark();

         bool _canSeePlayer(int32_t hitbox, Entity_t* fromPlayer, Entity_t* ToPlayer);

    public:

         Entity_t* localPlayer;

         void onCreateMoove();
};


#endif //GOLPHOOK_FUN_VISUALS_HH
