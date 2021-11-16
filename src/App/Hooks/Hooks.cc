//
// Created by fleur on 14/11/2021.
//

#include "Hooks.hh"

Hooks::Hooks() {

    PLOGD << "Bootstraping hooks";

    if ( MH_Initialize() != MH_OK ) {
        //throw FatalError::CoreInitException("Failed to initialize minhook");
        PLOGD << "Failed to initialize minhook";
    }

    EndScene::getDevice();
    this->_applyHook(static_cast<uintptr_t *>(EndScene::d3d9DeviceTable[42]),
                     reinterpret_cast<uintptr_t *>(&EndScene::hooked),
                     reinterpret_cast<uintptr_t *>(&EndScene::original), "EndScene()");
    if (MH_EnableHook(MH_ALL_HOOKS) == MH_OK)
        LOG_INFO << "minhooks success";

}

void Hooks::removeHooks() {
    if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
        //throw std::runtime_error("Failed to remove restore hooked functions");
        PLOGD << "Failed to remove restore hooked functions";
    if (MH_Uninitialize() != MH_OK)
        LOG_ERROR << "Failed to unintialise minhook";
}

void Hooks::_applyHook(uintptr_t* toAddress, uintptr_t* withDetour, uintptr_t* withOriginal, std::string andHookName) {
    if ( MH_CreateHook(toAddress, withDetour, reinterpret_cast<void**>(withOriginal)) != MH_OK ) {
        //throw FatalError::ApplyHookError("Failed to apply hook on " + andHookName);
        PLOGD << "Failed to apply hook on " + andHookName;
    }
    PLOGD << Utils::stringAlign("Hook: " + andHookName, 45, "|") << "Ok";
}