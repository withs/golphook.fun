//
// Created by fleur on 14/11/2021.
//

#include "Visuals.hh"

#include "Render/DrawQueue.hh"


void Visuals::onCreateMoove() {
    if ( Config::Get().currentCfg().watermark )
        this->_watermark();

    if ( InterfacesCollection::i_engineClient->IsInGame() && InterfacesCollection::i_engineClient->IsConnected() ) {

        for ( uint16_t pIndex = 0; pIndex <= 32; pIndex++ ) {

            Entity_t* ent;

            if ( (ent = InterfacesCollection::i_entityList->getClientEntity(pIndex)) ) {

                if ( ent != this->localPlayer &&
                     ent->dormant() == 0 &&
                     ent->health() > 0 &&
                     ent->team() != this->localPlayer->team()
                ) {
                    if ( Config::Get().currentCfg().snaplines )
                        this->_snapline(ent);
                }

            }

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

        Color_t bc { Config::Get().currentCfg().snaplinesCol.r,
                     Config::Get().currentCfg().snaplinesCol.g,
                     Config::Get().currentCfg().snaplinesCol.b,
                     Config::Get().currentCfg().snaplinesCol.a
        };
        std::shared_ptr<DrawLineb> aa;
        aa = std::shared_ptr<DrawLineb>{
                new DrawLineb(
                        Vec2<uint32_t>{static_cast<uint32_t>(App::Get().io.windWidth / 2),
                                       static_cast<uint32_t>(App::Get().io.windHeight)},
                        Vec2<uint32_t>{static_cast<uint32_t>(screenOut.x), static_cast<uint32_t>(screenOut.y)},
                        1.3f,
                        bc
                )
        };
        DrawQueue::Get().push(aa);

    }

}

void Visuals::_watermark() {
    Color_t bc { Config::Get().currentCfg().watermarkCol.r,
                 Config::Get().currentCfg().watermarkCol.g,
                 Config::Get().currentCfg().watermarkCol.b,
                 Config::Get().currentCfg().watermarkCol.a
    };
    std::shared_ptr<DrawTextb> aa;
    aa = std::shared_ptr<DrawTextb>{ new DrawTextb(Vec2<uint32_t>{static_cast<uint32_t>(4), static_cast<uint32_t>(4)}, "golphook.fun", bc) };
    DrawQueue::Get().push(aa);

}
