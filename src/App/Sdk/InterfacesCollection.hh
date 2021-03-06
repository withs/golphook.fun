//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_INTERFACESCOLLECTION_HH
#define GOLPHOOK_FUN_INTERFACESCOLLECTION_HH

#include "Interfaces/IVDebugOverlay.h"
#include "Interfaces/cdll_int.h"
#include "Interfaces/ICvar.h"
#include "Interfaces/IInputSystem.h"
#include "Interfaces/ISurface.h"
#include "Interfaces/IEntityList.h"
#include "Interfaces/client_class.h"
#include "Interfaces/IEngineTrace.hh"
#include "Interfaces/CInput.hh"
#include "Interfaces/IVModelInfo.h"

class InterfacesCollection {
    public:
         static inline IVDebugOverlay* i_vDebugOverlay;
         static inline EntityList* i_entityList;
         static inline IBaseClientDLL* i_baseClient;
         static inline IVEngineClient* i_engineClient;
         static inline ICvar* i_console;
         static inline IInputSystem* i_inputSystem;
         static inline ISurface* i_surface;
         static inline IEngineTrace* i_engineTrace;
         static inline CInput* i_cinput;
         static inline IVModelInfo* i_modelInfo;
};


#endif //GOLPHOOK_FUN_INTERFACESCOLLECTION_HH
