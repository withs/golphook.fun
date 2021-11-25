//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_ENGINE_HH
#define GOLPHOOK_FUN_ENGINE_HH

#include "CommonIncludes.hh"

#include <cmath>

#include "Sdk/InterfacesCollection.hh"
#include "Utils/Math/Math.hh"

class Engine {

    private:

         struct Bone {
             Vec3 pos;
             int32_t id;
         };

         struct TargetedEntity {
             Entity_t* ent;
             std::vector<Bone> bonesOnscreen = {  };
             Bone closestBone = { { 0,0,999 }, 999 };
         };

         std::vector<TargetedEntity> _targetedEntities = {  };

         bool _isInFov(Vec3& entPosOnScren);
         void _aimAt(TargetedEntity ent);
         bool _canSeePlayer(int32_t hitbox, Entity_t* ToPlayer);
         void _collectTargetedEnts();

    public:
        bool aShoot = false;
        bool forceBone = false;
        void onFrame();

};


#endif //GOLPHOOK_FUN_ENGINE_HH
