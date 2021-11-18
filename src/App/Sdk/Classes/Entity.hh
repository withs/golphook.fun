//
// Created by fleur on 18/11/2021.
//

#ifndef GOLPHOOK_FUN_ENTITY_HH
#define GOLPHOOK_FUN_ENTITY_HH

#include "Utils/Structs/Vector.hh"
#include "Utils/Memory/Mem.hh"

#include "Sdk/Interfaces/client_class.h"

#include "Netvars/NetvarsCollection.hh"

class c_econ_item_view;

inline constexpr bool isKnife(const short i) noexcept {
    return i >= 500 && i < 5027 || i == 42 || i == 59;
}

inline constexpr bool isCustomKnife(const short i) noexcept {
    return i >= 500 && i < 5027;
}

enum class FrameStage_t : int32_t {
    // Haven't run any frames yet.
    frame_undefined = -1,
    frame_start,

    // A network packet is being recieved.
    frame_net_update_start,
    // Data has been received and we're going to start calling postdataupdate.
    frame_net_update_postdataupdate_start,
    // Data has been received and we've called postdataupdate on all data recipients.
    frame_net_update_postdataupdate_end,
    // We've received all packets, we can now do interpolation, prediction, etc...
    frame_net_update_end,

    // We're about to start rendering the scene.
    frame_render_start,
    // We've finished rendering the scene.
    frame_render_end
};

class Collideable_t {
    public:
         Vec3 mins() {
             return Mem::callVirtual< Vec3&, 1 >(this);
         }

         Vec3 maxs() {
             return Mem::callVirtual< Vec3&, 2 >(this);
         }
};

class Entity_t {
    public:
         void* animating() {
             return static_cast<void*>(this + 4);
         }

         void* networkable() {
             return static_cast<void*>(this + 8);
         }

         void release() {
             return Mem::callVirtual< void, 1 >(networkable());
         }

         ClientClass* client_class() {
             return Mem::callVirtual< ClientClass*, 2 >(networkable());
         }

         int32_t handle() {
             return Mem::callVirtual< int32_t&, 2 >(this);
         }

         Collideable_t* collideable() {
             return Mem::callVirtual< Collideable_t*, 3 >(this);
         }

         void onDataChanged(const int32_t updateType) {
             return Mem::callVirtual< void, 5, int32_t >(networkable(), updateType);
         }

         void preDataUpdate(const int32_t updateType) {
             return Mem::callVirtual< void, 6, int32_t >(networkable(), updateType);
         }

         void postDataUpdate(const int32_t updateType) {
             return Mem::callVirtual< void, 7, int32_t >(networkable(), updateType);
         }

         const void* getModel() {
             return Mem::callVirtual< const void*, 8 >(animating());
         }

         bool dormant() {
             return Mem::callVirtual< bool, 9 >(networkable());
         }

         int32_t index() {
             return Mem::callVirtual< int32_t, 10 >(networkable());
         }

         void setDestroyedOnRecreateEntity() {
             return Mem::callVirtual< void, 13 >(networkable());
         }

         void setModelIndex(const int32_t index) {
             return Mem::callVirtual< void, 75, int32_t >(this, index);
         }

         bool isAlive() {
             return Mem::callVirtual< bool, 155 >(this);
         }

         void sendViewmodelMatchingSequence(int32_t sequence) {
             return Mem::callVirtual< void, 246, int32_t >(this, sequence);
         }

         Entity_t* activeWeapon() {
             return Mem::callVirtual< Entity_t*, 267 >(this);
         }

         /*
         c_econ_item_view* get_econ_item_view() {
             return signatures::fn_get_econ_item_view(this);
         }

         int32_t equip_wearable(void* const owner)
         {
             return signatures::fn_equip_wearable(this, owner);
         }

         int32_t initialize_attributes()
         {
             return signatures::fn_initialize_attributes(this);
         }
            */
         // NETVARS
         auto body() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_nBody, this);
         }

         auto viewModelIndex() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_nViewModelIndex, this);
         }

         auto weaponHandle() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_hWeapon, this);
         }

         auto ownerHandle() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_hOwner, this);
         }

         auto itemIndex() {
             return Mem::getValOffset< int16_t >(NetvarsCollection::m_iItemDefinitionIndex, this);
         }

         auto originalOwnerXuidLow() {
             return Mem::getValOffset< uint32_t >(NetvarsCollection::m_OriginalOwnerXuidLow, this);
         }

         auto originalOwnerXuidHigh() {
             return Mem::getValOffset< uint32_t >(NetvarsCollection::m_OriginalOwnerXuidHigh, this);
         }

         auto itemIdLow() {
             return Mem::getValOffset< uint64_t >(NetvarsCollection::m_iItemIDLow, this);
         }

         auto itemIdHigh() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_iItemIDHigh, this);
         }

         auto entityQuality() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_iEntityQuality, this);
         }

         auto accountId() {
             return Mem::getValOffset< uint32_t >(NetvarsCollection::m_iAccountID, this);
         }

         auto initialized() {
             return Mem::getValOffset< bool >(NetvarsCollection::m_bInitialized, this);
         }

         auto worldModelHandle() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_hWeaponWorldModel, this);
         }
        /*
         auto wearables() {
             return netvar_manager::get_netvar_pointer< int32_t >("DT_BaseCombatCharacter", "m_hMyWearables", this);
         }

         auto weapons() {
             return Mem::getValOffset< int32_t[64] >("DT_BaseCombatCharacter", "m_hMyWeapons", this);
         }
        */
         auto modelIndex() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_nModelIndex, this);
         }

         auto team() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_iTeamNum, this);
         }

         auto ownerEntity() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_hOwnerEntity, this);
         }

         auto viewModelHandle() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_hViewModelz, this);
         }

         auto tickBase() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_nTickBase, this);
         }

         // Player related NETVARS
         auto health() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_iHealth, this);
         }

         auto isScoped() {
             return Mem::getValOffset< bool >(NetvarsCollection::m_bIsScoped, this);
         }

         auto isControllingBot() {
             return Mem::getValOffset< bool >(NetvarsCollection::m_bIsControllingBot, this);
         }

         auto ragdollHandle() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_hRagdoll, this);
         }

         auto weaponOriginalTeamNumber() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_iOriginalTeamNumber, this);
         }

         auto weaponPreviousOwner() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_hPrevOwner, this);
         }

         // C4 netvars
         auto startedArming() {
             return Mem::getValOffset< bool >(NetvarsCollection::m_bStartedArming, this);
         }

         auto c4Bombsite() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_nBombSite, this);
         }

         auto c4BlowTime() {
             return Mem::getValOffset< float >(NetvarsCollection::m_flC4Blow, this);
         }

         auto c4Defuser() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_hBombDefuser, this);
         }

         auto c4DefuseTime() {
             return Mem::getValOffset< float >(NetvarsCollection::m_flDefuseCountDown, this);
         }
};

#endif //GOLPHOOK_FUN_ENTITY_HH
