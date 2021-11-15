//
// Created by fleur on 14/11/2021.
//

#include "App.hh"

void App::init(HMODULE withModuleHandle) {
    App::makeShared();

    Utils::allocateConsole();

    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, &consoleAppender);

    if ( MH_Initialize() != MH_OK ) {
        throw FatalError::CoreInitException("Failed to initialize minhook");
        return;
    }

    Utils::waitForModule({ "client.dll", "engine.dll", "vstdlib.dll"}, 5);

    App::Get().run();

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