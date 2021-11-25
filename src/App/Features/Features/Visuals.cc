//
// Created by fleur on 14/11/2021.
//

#include "Visuals.hh"

#include "Render/DrawQueue.hh"

void Visuals::onFrame() {
    if ( Config::Get().currentCfg().watermark )
        this->_watermark();

    if ( InterfacesCollection::i_engineClient->IsInGame() && InterfacesCollection::i_engineClient->IsConnected() ) {

        for ( auto& ent: App::Get().entityList ) {
            if ( Config::Get().currentCfg().snaplines )
                this->_snapline(ent);

            if ( Config::Get().currentCfg().boxe )
                this->_boxe(ent);

            // indics
        }

    }
}

void Visuals::_snapline(Entity_t* ent) {

    Vec3 entPos = ent->origin();
    Vec3 screenOut { };

    if ( Math::worldToScreen(entPos, screenOut) ) {

        if ( screenOut.x <= 0 ||
                screenOut.y <= 0 ||
                screenOut.x >= App::Get().io.windWidth ||
                screenOut.y >= App::Get().io.windHeight
                ) {
            return;
        }

        Color_t bc = Config::Get().currentCfg().snaplinesCol;


        std::vector<int32_t> boneToBeVisible = { 8, 42, 12, 79, 72, 71, 78 };

        for ( auto& bone: boneToBeVisible) {
            if ( this->_canSeePlayer(bone, App::Get().localPlayer, ent) ) {
                bc = Config::Get().currentCfg().snaplinesColOcl;
                break;
            }
        }

        std::shared_ptr<DrawLineb> aa;
        aa = std::shared_ptr<DrawLineb>{
                new DrawLineb(
                        Vec2<int32_t>{static_cast<int32_t>(App::Get().io.windWidth / 2), static_cast<int32_t>(App::Get().io.windHeight)},
                        Vec2<int32_t>{static_cast<int32_t>(screenOut.x), static_cast<int32_t>(screenOut.y)},
                        1.3f,
                        bc
                )
        };
        DrawQueue::Get().push(aa);

    }

}

void Visuals::_boxe(Entity_t *ent) {
    Vec3 entPos = ent->origin();
    Vec3 screenOut { };

    if ( Math::worldToScreen(entPos, screenOut) ) {

        if ( screenOut.x <= 0 ||
             screenOut.y <= 0 ||
             screenOut.x >= App::Get().io.windWidth
                ) {
            return;
        }

        Vec3 screenHeadOut { };
        Vec3 headPos = ent->bone(8);
        headPos.z += 13;

        if ( Math::worldToScreen(headPos, screenHeadOut) ) {

            Color_t bc = Config::Get().currentCfg().boxeColOcl;

            std::vector<int32_t> boneToBeVisible = { 8, 42, 12, 79, 72, 71, 78 };

            for ( auto& bone: boneToBeVisible) {
                if ( this->_canSeePlayer(bone, App::Get().localPlayer, ent) ) {
                    bc = Config::Get().currentCfg().boxeCol;
                    break;
                }
            }

            std::shared_ptr<DrawRectb> aa;
            aa = std::shared_ptr<DrawRectb>{
                    new DrawRectb(
                                {static_cast<int32_t>(screenOut.x), static_cast<int32_t>(screenOut.y)},
                                screenHeadOut.y,
                                bc
                            )
            };
            DrawQueue::Get().push(aa);

        }
    }
}

void Visuals::_watermark() {
    Color_t bc = Config::Get().currentCfg().watermarkCol;
    std::shared_ptr<DrawTextb> aa;
    aa = std::shared_ptr<DrawTextb>{ new DrawTextb(Vec2<uint32_t>{static_cast<uint32_t>(4), static_cast<uint32_t>(4)}, "golphook.fun", bc) };
    DrawQueue::Get().push(aa);

}

bool Visuals::_canSeePlayer(int32_t hitbox, Entity_t *fromPlayer, Entity_t *ToPlayer) {
    CGameTrace tr;
    Ray_t ray;
    CTraceFilter filter;
    filter.pSkip = fromPlayer;

    Vec3 endpos = ToPlayer->bone(hitbox);
    Vector vEndPos { endpos.x, endpos.y, endpos.z };

    Vec3 eyePos = fromPlayer->bone(8);
    Vector vEyePos { eyePos.x, eyePos.y, eyePos.z };

    ray.Init(vEyePos, vEndPos);
    InterfacesCollection::i_engineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);

    return tr.fraction > 0.97f;
}
