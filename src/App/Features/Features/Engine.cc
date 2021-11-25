//
// Created by fleur on 14/11/2021.
//

#include "Engine.hh"
#include "App.hh"
#include "cmath"

int prefHitBox = 8;
std::vector<int> boneList = { 8, 9, 42, 12, 79, 72, 71, 78 };

void Engine::onFrame() {

    if ( InterfacesCollection::i_engineClient->IsInGame() && InterfacesCollection::i_engineClient->IsConnected() ) {
        if ( Config::Get().currentCfg().engine ) {

            // TODO: test avec asyncKeyState ou avec wndProc
            if ( GetAsyncKeyState(0x05) ) {

                /*
                Indicators::Get().push(
                        "Automatic fire",
                        { 255, 255, 255, 255 }
                );
                
                if ( this->forceBone ) {
                    Indicators::Get().push(
                            "Force bone",
                            { 255, 255, 255, 255 }
                    );
                }*/

                this->_targetedEntities.clear();
                this->_collectTargetedEnts();

                if ( this->_targetedEntities.size() != 0 ) {
                    TargetedEntity closestToCrosshair = this->_targetedEntities.at(0);

                    for ( auto& ent: this->_targetedEntities ) {

                        if ( ent.closestBone.pos.z < closestToCrosshair.closestBone.pos.z ) {
                            closestToCrosshair = ent;
                        }
                    }


                    this->_aimAt(closestToCrosshair);
                    // TODO: fix ca ^^ c'est vraiment pas bo)
                    *(int32_t*)((uintptr_t)GetModuleHandleA("client.dll") + 0x31F1D14) = 6;
                }
            }
        }
    }
}


bool Engine::_isInFov(Vec3& bonePosOnScren) {

    float a = std::abs(bonePosOnScren.x - (App::Get().io.windWidth / 2));
    float b = std::abs(bonePosOnScren.y - (App::Get().io.windHeight / 2));

    if ( (bonePosOnScren.z = sqrt((a*a) + (b*b))) < Config::Get().currentCfg().engineFov )
        return true;
    return false;

}

void Engine::_aimAt(TargetedEntity ent) {
    Vec3 myPos = App::Get().localPlayer->getEyePos();
    Vec3 target = ent.ent->bone(ent.closestBone.id);
    Vec3 out = { 0, 0 ,0};

    Vec3 deltaVec = { target.x - myPos.x, target.y - myPos.y, target.z - myPos.z };
    float deltaVecLength = sqrt(deltaVec.x * deltaVec.x + deltaVec.y * deltaVec.y + deltaVec.z * deltaVec.z);

    float pitch = -asin(deltaVec.z / deltaVecLength) * (180 / Consts::pi);
    float yaw = atan2(deltaVec.y, deltaVec.x) * (180 / Consts::pi);

    if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180)
    {
        out.x = pitch;
        out.y = yaw;
    }

    InterfacesCollection::i_engineClient->SetViewAngles(&out);
}

bool Engine::_canSeePlayer(int32_t hitbox, Entity_t *ToPlayer) {
    CGameTrace tr;
    Ray_t ray;
    CTraceFilter filter;
    filter.pSkip = App::Get().localPlayer;

    Vec3 endpos = ToPlayer->bone(hitbox);
    Vector vEndPos { endpos.x, endpos.y, endpos.z };

    Vec3 eyePos = App::Get().localPlayer->getEyePos();
    Vector vEyePos { eyePos.x, eyePos.y, eyePos.z };

    ray.Init(vEyePos, vEndPos);
    InterfacesCollection::i_engineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);

    return tr.fraction > 0.97f;
}


void Engine::_collectTargetedEnts() {

    for ( auto& ent: App::Get().entityList ) {

        Vec3 bonePos;
        Vec3 screenOut;
        TargetedEntity tEnt{ ent };

        for ( int& boneIndex: boneList ) {
            bonePos = ent->bone(boneIndex);

            if( Math::worldToScreen(bonePos, screenOut) ) {

                if ( this->_isInFov(screenOut) ) {

                    if ( this->_canSeePlayer(boneIndex, ent) ) {

                        tEnt.bonesOnscreen.push_back({ screenOut, boneIndex });

                        if ( screenOut.z < tEnt.closestBone.pos.z || boneIndex == prefHitBox ) {
                            if ( tEnt.closestBone.id != prefHitBox )
                                tEnt.closestBone = tEnt.bonesOnscreen.at(tEnt.bonesOnscreen.size() - 1);
                        }
                    }
                }
            }
        }

        if ( tEnt.bonesOnscreen.size() != 0 )
            this->_targetedEntities.push_back(tEnt);

    }
}
