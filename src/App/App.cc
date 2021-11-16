//
// Created by fleur on 14/11/2021.
//

#include "App.hh"

void App::bootstrap(HMODULE withModuleHandle) {
    App::makeShared();

    Utils::allocateConsole();

    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, &consoleAppender);

    Utils::waitForModule({ "client.dll", "engine.dll", "vstdlib.dll", "inputsystem.dll", "vguimatsurface.dll"}, 15);

    App::Get().io.windHandle = FindWindowA(0, "Counter-Strike: Global Offensive");

    Interfaces::makeShared();
    Hooks::makeShared();

    App::Get().run();

    Hooks::Get().removeHooks();

    Utils::freeConsole();
    FreeLibraryAndExitThread(withModuleHandle, 0);
}

void App::run() {

    PLOG_INFO << "hello golphook.fun";

    while ( true ) {

        if ( GetAsyncKeyState(VK_INSERT) & 1 ) {

        }

        if ( GetAsyncKeyState(VK_END) & 1 ) {
            break;
        }
    }

}