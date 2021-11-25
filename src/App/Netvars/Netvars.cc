//
// Created by fleur on 14/11/2021.
//

#include "Netvars.hh"

NetvarsDumper::NetvarsDumper() {

    this->_clientClass =  InterfacesCollection::i_baseClient->GetAllClasses();
    
    NetvarsCollection::n_localPlayer = this->getNetVarOffset("DT_BasePlayer", "m_vecOrigin");

    NetvarsCollection::m_nBody = this->getNetVarOffset("DT_BaseAnimating", "m_nBody");
    NetvarsCollection::m_nViewModelIndex = this->getNetVarOffset("DT_BaseViewModel", "m_nViewModelIndex");
    NetvarsCollection::m_hWeapon = this->getNetVarOffset("DT_BaseViewModel", "m_hWeapon");
    NetvarsCollection::m_hOwner = this->getNetVarOffset("DT_BaseViewModel", "m_hOwner");
    NetvarsCollection::m_iItemDefinitionIndex = this->getNetVarOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex");
    NetvarsCollection::m_OriginalOwnerXuidLow = this->getNetVarOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
    NetvarsCollection::m_OriginalOwnerXuidHigh = this->getNetVarOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
    NetvarsCollection::m_iItemIDLow = this->getNetVarOffset("DT_BaseAttributableItem", "m_iItemIDLow");
    NetvarsCollection::m_iItemIDHigh = this->getNetVarOffset("DT_BaseAttributableItem", "m_iItemIDHigh");
    NetvarsCollection::m_iEntityQuality = this->getNetVarOffset("DT_BaseAttributableItem", "m_iEntityQuality");
    NetvarsCollection::m_iAccountID = this->getNetVarOffset("DT_BaseAttributableItem", "m_iAccountID");
    NetvarsCollection::m_bInitialized = this->getNetVarOffset("DT_BaseAttributableItem", "m_bInitialized");
    NetvarsCollection::m_hWeaponWorldModel = this->getNetVarOffset("DT_BaseCombatWeapon", "m_hWeaponWorldModel");
    NetvarsCollection::m_nModelIndex = this->getNetVarOffset("DT_BaseEntity", "m_nModelIndex");
    NetvarsCollection::m_hOwnerEntity = this->getNetVarOffset("DT_BaseEntity", "m_hOwnerEntity");
    NetvarsCollection::m_hViewModelz = this->getNetVarOffset("DT_BasePlayer", "m_hViewModel[0]");
    NetvarsCollection::m_nTickBase = this->getNetVarOffset("DT_BasePlayer", "m_nTickBase");

    NetvarsCollection::m_bIsScoped = this->getNetVarOffset("DT_CSPlayer", "m_bIsScoped");
    NetvarsCollection::m_bIsControllingBot = this->getNetVarOffset("DT_CSPlayer", "m_bIsControllingBot");
    NetvarsCollection::m_hRagdoll = this->getNetVarOffset("DT_CSPlayer", "m_hRagdoll");
    NetvarsCollection::m_iOriginalTeamNumber = this->getNetVarOffset("DT_WeaponCSBase", "m_iOriginalTeamNumber");
    NetvarsCollection::m_hPrevOwner = this->getNetVarOffset("DT_WeaponCSBase", "m_hPrevOwner");
    NetvarsCollection::m_bStartedArming = this->getNetVarOffset("DT_WeaponC4", "m_bStartedArming");
    NetvarsCollection::m_nBombSite = this->getNetVarOffset("DT_PlantedC4", "m_nBombSite");
    NetvarsCollection::m_flC4Blow = this->getNetVarOffset("DT_PlantedC4", "m_flC4Blow");
    NetvarsCollection::m_hBombDefuser = this->getNetVarOffset("DT_PlantedC4", "m_hBombDefuser");
    NetvarsCollection::m_flDefuseCountDown = this->getNetVarOffset("DT_PlantedC4", "m_flDefuseCountDown");

    NetvarsCollection::m_iHealth = this->getNetVarOffset("DT_CSPlayer", "m_iHealth");
    NetvarsCollection::m_iTeamNum = this->getNetVarOffset("DT_BaseEntity", "m_iTeamNum");
    NetvarsCollection::m_vecOrigin = this->getNetVarOffset("DT_BasePlayer", "m_vecOrigin");
    NetvarsCollection::m_dwBoneMatrix = this->getNetVarOffset("DT_BaseAnimating", "m_nForceBone") + 28;
    NetvarsCollection::m_vecViewOffset = this->getNetVarOffset("DT_BasePlayer", "m_vecViewOffset[0]");
    NetvarsCollection::m_iDefaultFOV = this->getNetVarOffset("DT_BasePlayer", "m_iDefaultFOV");
    NetvarsCollection::m_fFlags = this->getNetVarOffset("DT_BasePlayer", "m_fFlags");
    NetvarsCollection::m_MoveType = this->getNetVarOffset("DT_BasePlayer", "m_nRenderMode") + 1;
};


// both _getOffset and getNetVarOffset are from GH but i modified them to use strings
// TODO: peut etre call un throw si pas trouver et handle ce throw dans getNetVarOffset
intptr_t NetvarsDumper::_getOffset(RecvTable *inTable, std::string withTableName, std::string forNetvarName) noexcept {
    for ( uint32_t i = 0; i < inTable->m_nProps; i++ ) {
        RecvProp prop = inTable->m_pProps[i];

        if ( (std::string(prop.m_pVarName) == forNetvarName) )
            return prop.m_Offset;

        if ( prop.m_pDataTable ) {
            intptr_t offset = this->_getOffset(prop.m_pDataTable, withTableName, forNetvarName);

            if ( offset ) {
                return offset + prop.m_Offset;
            }
        }
    }
    return 0;
}

intptr_t NetvarsDumper::getNetVarOffset(std::string withTableName,std::string forNetvarName) {
    for ( auto currNode = this->_clientClass; currNode; currNode = currNode->m_pNext ) {
        if ( (withTableName == std::string(currNode->m_pRecvTable->m_pNetTableName)) )
            return this->_getOffset(currNode->m_pRecvTable, withTableName, forNetvarName);
    }
    throw FatalError::NetvarNullError("Failed to get netvar: " + forNetvarName + " in table: " + withTableName);
}