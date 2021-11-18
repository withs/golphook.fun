//
// Created by fleur on 14/11/2021.
//

#include "Hooks.hh"

Hooks::Hooks() {

    PLOGD << "Bootstraping hooks";

    if ( MH_Initialize() != MH_OK ) {
        throw FatalError::CoreInitException("Failed to initialize minhook");
    }

    EndScene::getDevice();
    this->_applyHook(static_cast<uintptr_t *>(EndScene::d3d9DeviceTable[42]),
                     reinterpret_cast<uintptr_t *>(&EndScene::hooked),
                     reinterpret_cast<uintptr_t *>(&EndScene::original), "EndScene()");

    uintptr_t* lockCursorAddress = static_cast<uintptr_t *>(Mem::getVirtual(InterfacesCollection::i_surface, 67));
    this->_applyHook(static_cast<uintptr_t *>(lockCursorAddress),
                     reinterpret_cast<uintptr_t *>(&LockCursor::hooked),
                     reinterpret_cast<uintptr_t *>(&LockCursor::original), "LockCursor()");


    if ( (WndProc::original = reinterpret_cast<decltype(WndProc::original)>(SetWindowLongA(
            FindWindowA("Valve001", nullptr),
            GWL_WNDPROC,
            reinterpret_cast<LONG>(WndProc::hooked)
        ))) ) {
        PLOGD << Utils::stringAlign("Hook: WndProc", 45, "|") << "Ok";
    } else {
        throw FatalError::ApplyHookError("Failed to apply hook on WndProc");
    }

    uint8_t* createMooveAddr = Mem::patternScan(GetModuleHandleA("client.dll"), "55 8B EC 8B 4D 04 8B");
    this->_applyHook(reinterpret_cast<uintptr_t *>(createMooveAddr),
                     reinterpret_cast<uintptr_t *>(&CreateMoove::hooked),
                     reinterpret_cast<uintptr_t *>(&CreateMoove::original), "CreateMoove()");



    if (MH_EnableHook(MH_ALL_HOOKS) == MH_OK)
        LOG_INFO << "minhooks success";

}

void Hooks::removeHooks() {

    SetWindowLongA(FindWindowA("Valve001", nullptr), GWL_WNDPROC, reinterpret_cast<LONG>(WndProc::original));

    if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
        throw std::runtime_error("Failed to remove restore hooked functions");
    if (MH_Uninitialize() != MH_OK)
        LOG_ERROR << "Failed to unintialise minhook";
}

void Hooks::_applyHook(uintptr_t* toAddress, uintptr_t* withDetour, uintptr_t* withOriginal, std::string andHookName) {
    if ( MH_CreateHook(toAddress, withDetour, reinterpret_cast<void**>(withOriginal)) != MH_OK ) {
        throw FatalError::ApplyHookError("Failed to apply hook on " + andHookName);
    }
    PLOGD << Utils::stringAlign("Hook: " + andHookName, 45, "|") << "Ok";
}