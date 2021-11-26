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


}



void App::run() {

    this->localPlayer = InterfacesCollection::i_entityList->getClientEntity(
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

        if ( GetAsyncKeyState(0x42) & 1 ) {





        }

        if ( GetAsyncKeyState(VK_END) & 1 ) {
            break;
        }
    }

}

void App::collectEntities() {

    if ( InterfacesCollection::i_engineClient->IsInGame() && InterfacesCollection::i_engineClient->IsConnected() ) {

        for ( uint16_t pIndex = 0; pIndex <= 32; pIndex++ ) {

            Entity_t* ent;

            if ( (ent = InterfacesCollection::i_entityList->getClientEntity(pIndex)) ) {

                if ( ent != this->localPlayer &&
                     ent->dormant() == 0 &&
                     ent->health() > 0 &&
                     ent->team() != this->localPlayer->team()
                        ) {

                    this->entityList.push_back(ent);

                }

            }

        }

    }

}
