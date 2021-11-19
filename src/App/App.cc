//
// Created by fleur on 14/11/2021.
//

#include "App.hh"

void App::bootstrap(HMODULE withModuleHandle) {
    App::makeShared();

#ifdef _DEBUG
    Utils::allocateConsole();
#endif


    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, &consoleAppender);

    Utils::waitForModule({ "client.dll", "engine.dll", "vstdlib.dll", "inputsystem.dll", "vguimatsurface.dll"}, 15);

    App::Get().io.windHandle = FindWindowA(0, "Counter-Strike: Global Offensive");

    Interfaces::makeShared();
    NetvarsDumper::makeShared();
    Config::makeShared();
    Menu::makeShared();
    Hooks::makeShared();
    DrawQueue::makeShared();
    Features::makeShared();

    App::Get().run();

    Hooks::Get().removeHooks();
    Menu::Get().release();

#ifdef _DEBUG
    Utils::freeConsole();
#endif

    FreeLibraryAndExitThread(withModuleHandle, 0);
}

#include "Render/DrawTools.hh"

void App::caca() {
    Color_t bc { };
    bc.r = 255;
    bc.g = 0;
    bc.b = 0;
    bc.a = 255;

    auto aa = std::shared_ptr<DrawTextb>{ new DrawTextb(Vec2<uint32_t>{ 100, 100}, std::string("hello"), bc) };

    DrawQueue::Get().push(aa);
}

void App::run() {

    Features::Get().visuals->localPlayer = InterfacesCollection::i_entityList->getClientEntity(
            InterfacesCollection::i_engineClient->GetLocalPlayer()
    );

    this->ready = true;
    Menu::Get().isMenuOpened = true;

    Beep( 670, 200 );
    Beep( 730, 150 );
    PLOG_INFO << "hello golphook.fun";

    while ( true ) {

        if ( GetAsyncKeyState(VK_INSERT) & 1 ) {
        }


        if ( GetAsyncKeyState(0x41) & 1 ) {
            /*
            for ( uint32_t pIndex = 0; pIndex <= 16; pIndex++ ) {
                Entity_t* player = InterfacesCollection::i_entityList->getClientEntity(pIndex);
                if ( player ) {
                    PLOGD << player->health() << " - " << player->isAlive();
                }
            }*/

            //Entity_t* player = InterfacesCollection::i_entityList->getClientEntity(InterfacesCollection::i_engineClient->GetLocalPlayer());
            //PLOGD << player->health();

            // PLOGD << NetvarsDumper::Get().getNetVarOffset("DT_BaseAnimating", "m_nForceBone"); -> 9868

            uintptr_t ent = reinterpret_cast<uintptr_t>(InterfacesCollection::i_entityList->getClientEntity(
                    InterfacesCollection::i_engineClient->GetLocalPlayer()));
            Entity_t* player = InterfacesCollection::i_entityList->getClientEntity(InterfacesCollection::i_engineClient->GetLocalPlayer());

            Entity_t* abc = (Entity_t*)ent;

        }


        if ( GetAsyncKeyState(VK_END) & 1 ) {
            break;
        }
    }

}