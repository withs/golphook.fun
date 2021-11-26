//
// Created by fleur on 26/11/2021.
//

#include "Skins.hh"
#include "App.hh"

void Skins::_knifeChanger() {
    static uintptr_t g_pClient = (uintptr_t)GetModuleHandleA("client.dll");

    uintptr_t Local = (uintptr_t)App::Get().localPlayer;

    if ( !App::Get().localPlayer->isAlive() )
        return;

    for (int i = 0; i < 8; i++)
    {
        int Weapon = *(int*)(Local + NetvarsCollection::m_hMyWeapons + i * 0x4) & 0xFFF;
        Weapon = *(int*)(g_pClient + 0x4DC178C + (Weapon - 1) * 0x10);
        if (Weapon == 0) { continue; }
        short WeaponID = *(int16_t*)(Weapon + NetvarsCollection::m_iItemDefinitionIndex);
        if (WeaponID == 0) { continue; }
        ItemDefinitionIndex CSGOWeaponID = (ItemDefinitionIndex)WeaponID;

        if ( CSGOWeaponID == WEAPON_KNIFE || CSGOWeaponID == WEAPON_KNIFE_T || CSGOWeaponID == 507) {
            *(int16_t*)(Weapon + NetvarsCollection::m_iItemDefinitionIndex) = 507;
            *(uint32_t*)(Weapon + NetvarsCollection::m_nModelIndex) = InterfacesCollection::i_modelInfo->getModelIndex("models/weapons/v_knife_karam.mdl");
            *(uint32_t*)(Weapon + NetvarsCollection::m_iViewModelIndex) = InterfacesCollection::i_modelInfo->getModelIndex("models/weapons/v_knife_karam.mdl");
            *(int32_t*)(Weapon + NetvarsCollection::m_iEntityQuality) = i;

            *(int32_t*)(Weapon + NetvarsCollection::m_iItemIDHigh) = -1;
            *(uint32_t*)(Weapon + NetvarsCollection::m_nFallbackPaintKit) = 0;
            *(float*)(Weapon + NetvarsCollection::m_flFallbackWear) = 0.001f;


            DWORD activeWeapon = *(DWORD*)(Local + NetvarsCollection::m_hActiveWeapon) & 0xfff;
            activeWeapon = *(DWORD*)(g_pClient +0x4DC178C + (activeWeapon - 1) * 0x10);
            if (!activeWeapon) { continue; }

            short weaponIndex = *(short*)(activeWeapon + NetvarsCollection::m_iItemDefinitionIndex);
            if (weaponIndex != 507) { continue; } // skip if current weapon is not already set to chosen knife

            // get viewmodel entity
            DWORD activeViewModel = *(DWORD*)(Local + NetvarsCollection::m_hViewModelz) & 0xfff;
            activeViewModel = *(DWORD*)(g_pClient +0x4DC178C + (activeViewModel - 1) * 0x10);
            if (!activeViewModel) { continue; }
            *(uint32_t*)(activeViewModel + NetvarsCollection::m_nModelIndex) = InterfacesCollection::i_modelInfo->getModelIndex("models/weapons/v_knife_karam.mdl");

        }

    }

}

void Skins::onFrame() {
    if ( InterfacesCollection::i_engineClient->IsInGame() && InterfacesCollection::i_engineClient->IsConnected() ) {
        if ( Config::Get().currentCfg().knifeChanger )
            this->_knifeChanger();
    }
}