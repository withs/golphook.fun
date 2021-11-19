//
// Created by fleur on 14/11/2021.
//

#include "Visuals.hh"

void Visuals::onCreateMoove() {

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
                    this->_snapline(ent);
                }

            }

        }

    }

}

#include "Render/DrawQueue.hh"



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

        Color_t bc {  };
        bc.r = 255;
        bc.g = 0;
        bc.b = 0;
        bc.a = 255;
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
    Color_t bc {  };
    bc.r = 128;
    bc.g = 0;
    bc.b = 128;
    bc.a = 255;
    std::shared_ptr<DrawTextb> aa;
    aa = std::shared_ptr<DrawTextb>{ new DrawTextb(Vec2<uint32_t>{static_cast<uint32_t>(4), static_cast<uint32_t>(4)}, "golphook.fun", bc) };
    DrawQueue::Get().push(aa);

}
