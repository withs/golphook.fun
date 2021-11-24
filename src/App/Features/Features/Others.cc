//
// Created by fleur on 14/11/2021.
//

#include "Others.hh"
#include "App.hh"

void Others::onCreateMoove(CUserCmd* cmd) {

    if ( InterfacesCollection::i_engineClient->IsInGame() && InterfacesCollection::i_engineClient->IsConnected() ) {

        if ( Config::Get().currentCfg().indicators ) {
            /*
            int32_t queueSize = Indicators::Get().len();
            for ( int32_t i = 0; i < queueSize ; i++ ) {
                Indicators::Get().at(i).draw();
            }

            Indicators::Get().clear();*/
        }

        if ( Config::Get().currentCfg().bop )
            this->_bop(cmd);

        if ( Config::Get().currentCfg().tag )
            this->_tag();

        if ( Config::Get().currentCfg().fovCircle ) {
            std::shared_ptr<DrawCirlceb> aa;
            aa = std::shared_ptr<DrawCirlceb>{
                    new DrawCirlceb(
                            Vec2<int32_t>{App::Get().io.windHeight/2, App::Get().io.windWidth/2},
                            Config::Get().currentCfg().engineFov,
                            { 255, 255, 255, 255 })
            };
            DrawQueue::Get().push(aa);
        }
    }
}

void Others::overrideViewmodel() {
    Entity_t* viewmodelEnt = InterfacesCollection::i_entityList->getClientEntityHandle(
            App::Get().localPlayer->viewmodelHandle());

    Vec3 angles{  } ,forward{  }, right{  }, up{  };

    angles = viewmodelEnt->absAngle();

    Math::angleToVectors(angles, forward, right, up);

    float offX = Config::Get().currentCfg().viewmodelOff.x;
    float offY = Config::Get().currentCfg().viewmodelOff.y;
    float offZ = Config::Get().currentCfg().viewmodelOff.z;

    //App::Get().localPlayer->setFov(Config::Get().currentCfg().fov);

    viewmodelEnt->setAbsOrigin(viewmodelEnt->absOrigin() + forward * offY + up * offZ + right * offX);

    angles.x -= Config::Get().currentCfg().viewmodelAngOff.x;
    angles.y -= Config::Get().currentCfg().viewmodelAngOff.y;
    angles.z -= Config::Get().currentCfg().viewmodelAngOff.z;

    viewmodelEnt->setAbsAngle(angles);
}

void Others::_bop(CUserCmd *cmd) {
    static bool jumped_last_tick = false;
    static bool should_fake_jump = false;

    if ( !App::Get().localPlayer )
        return;

    if ( !App::Get().localPlayer->isAlive() )
        return;

    if ( App::Get().localPlayer->moveType() == MOVETYPE_LADDER || App::Get().localPlayer->moveType() == MOVETYPE_NOCLIP )
        return;

    if ( App::Get().localPlayer->flags() & FL_INWATER )
        return;

    if( !jumped_last_tick && should_fake_jump ) {
        should_fake_jump = false;
        cmd->buttons |= IN_JUMP;
    } else if( cmd->buttons & IN_JUMP ) {
        if( App::Get().localPlayer->flags() & FL_ONGROUND ) {
            jumped_last_tick = true;
            should_fake_jump = true;
        } else {
            cmd->buttons &= ~IN_JUMP;
            jumped_last_tick = false;
        }
    } else {
        jumped_last_tick = false;
        should_fake_jump = false;
    }
}

/*
 * static uint8_t* aa = Mem::patternScan(GetModuleHandleA("client.dll"), "8B 0D ? ? ? ? 8B D6 8B C1 83 CA 02") + 2;
    uintptr_t baseAddrClient = (uintptr_t)GetModuleHandle("client.dll");

    if ( !App::Get().localPlayer )
        return;

    if ( !App::Get().localPlayer->isAlive() )
        return;

    if ( App::Get().localPlayer->moveType() == MOVETYPE_LADDER || App::Get().localPlayer->moveType() == MOVETYPE_NOCLIP )
        return;

    if ( App::Get().localPlayer->flags() & FL_INWATER )
        return;

    int aaaa = App::Get().localPlayer->flags();
    int vvv = App::Get().localPlayer->flags() & FL_ONGROUND;

    if ( GetAsyncKeyState(VK_SPACE) )
        if ( App::Get().localPlayer->flags() & FL_ONGROUND )
            //*(int32_t*)(baseAddrClient + aa) = 6;
 * */

void Others::_tag() {

    int secondsSincEpoch =
            std::chrono::duration_cast<std::chrono::seconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();


    if(std::to_string(secondsSincEpoch).back() == '6') {
        if(this->_currentTag != std::string("^")) {
            this->_currentTag = "^";
            Functions::SetClantag(this->_currentTag);
        }
    }

    if(std::to_string(secondsSincEpoch).back() == '7') {
        if(this->_currentTag != std::string("^^")) {
            this->_currentTag = "^^";
            Functions::SetClantag(this->_currentTag);
        }
    }

    if(std::to_string(secondsSincEpoch).back() == '0') {
        if(this->_currentTag != std::string("^")) {
            this->_currentTag = "^";
            Functions::SetClantag(this->_currentTag);
        }
    }

    if(std::to_string(secondsSincEpoch).back() == '4') {
        if(this->_currentTag != std::string("golphook.fun")) {
            this->_currentTag = "golphook.fun";
            Functions::SetClantag(this->_currentTag);
        }
    }
}