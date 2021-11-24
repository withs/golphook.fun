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

    //uint8_t* createMooveAddr = Mem::patternScan(GetModuleHandleA("client.dll"), "55 8B EC 8B 4D 04 8B");
    uintptr_t* createMooveAddr = static_cast<uintptr_t *>(Mem::getVirtual(InterfacesCollection::i_baseClient, 22));
    this->_applyHook(reinterpret_cast<uintptr_t *>(createMooveAddr),
                     reinterpret_cast<uintptr_t *>(&CreateMoove::proxy),
                     reinterpret_cast<uintptr_t *>(&CreateMoove::original), "CreateMoove()");


    uintptr_t* frameStageAddress = static_cast<uintptr_t *>(Mem::getVirtual(InterfacesCollection::i_baseClient, 37));
    this->_applyHook(static_cast<uintptr_t *>(frameStageAddress),
                     reinterpret_cast<uintptr_t *>(&FrameStageNotify::hooked),
                     reinterpret_cast<uintptr_t *>(&FrameStageNotify::original), "FrameStageNotify()");

    uint8_t* overideViewAddr = Mem::patternScan(GetModuleHandleA("client.dll"), "55 8B EC 83 E4 F8 83 EC 58 56 57 8B 3D ? ? ? ? 85 FF");
    this->_applyHook(reinterpret_cast<uintptr_t *>(overideViewAddr),
                     reinterpret_cast<uintptr_t *>(&OverrideView::hooked),
                     reinterpret_cast<uintptr_t *>(&OverrideView::original), "OverrideView()");

    uint8_t* getViewmodelFovAddr = Mem::patternScan(GetModuleHandleA("client.dll"), "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57");
    this->_applyHook(reinterpret_cast<uintptr_t *>(getViewmodelFovAddr),
                     reinterpret_cast<uintptr_t *>(&GetViewmodelFov::hooked),
                     reinterpret_cast<uintptr_t *>(&GetViewmodelFov::original), "GetViewmodelFov()");

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