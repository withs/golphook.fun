//
// Created by fleur on 14/11/2021.
//

#include "Interfaces.hh"

Interfaces::Interfaces() {

    PLOGD << "Bootstraping interfaces";

    InterfacesCollection::i_vDebugOverlay = this->_getInterface<IVDebugOverlay>("client.dll", "VClientEntityList003");
    InterfacesCollection::i_baseClient = this->_getInterface<IBaseClientDLL>("client.dll", "VClient018");
    InterfacesCollection::i_engineClient = this->_getInterface<IVEngineClient>("engine.dll", "VEngineClient014");
    InterfacesCollection::i_console = this->_getInterface<ICvar>("vstdlib.dll", "VEngineCvar007");
    InterfacesCollection::i_inputSystem = this->_getInterface<IInputSystem>("inputsystem.dll", "InputSystemVersion001");
    InterfacesCollection::i_surface = this->_getInterface<ISurface>("vguimatsurface.dll", "VGUI_Surface031");

    // TODO: mettre un try catch pour call CoreInitError si une des interfaces failed

}