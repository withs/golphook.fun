//
// Created by fleur on 18/11/2021.
//

#ifndef GOLPHOOK_FUN_ENTITY_HH
#define GOLPHOOK_FUN_ENTITY_HH

#include <Sdk/Interfaces/Misc/Enums.hh>
#include "Utils/Structs/Vector.hh"
#include "Utils/Memory/Mem.hh"

#include "Sdk/Interfaces/client_class.h"
#include "Sdk/Interfaces/Misc/BaseHandle.hh"
#include "Sdk/Interfaces/Misc/Enums.hh"
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

         bool dormant() {
             return Mem::callVirtual< bool, 9 >(networkable());
         }

         bool isAlive() {
             return Mem::callVirtual<bool, 155>(this);
         }

         CBaseHandle handle() {
             return Mem::callVirtual< CBaseHandle   &, 2 >(this);
         }

         Collideable_t* collideable(){
             return Mem::callVirtual< Collideable_t*, 3 >(this);
         }
         ClientClass* GetClientClass() {
             return Mem::callVirtual< ClientClass*, 2 >(networkable());
         }

         Vec3& absOrigin() {
             //return Mem::callVirtual< Vec3,10 >(this);
             using original_fn = Vec3 & (__thiscall*)(void*);
             return (*(original_fn**)this)[10](this);;
         }

         Vec3& absAngle() {
             using original_fn = Vec3 & (__thiscall*)(void*);
             return (*(original_fn**)this)[11](this);;
         }

         void setAbsOrigin(Vec3 withOrigin) {
             using oFnSetAbsOrigin = void(__thiscall*)(void*, const Vec3&);
             static auto oSetAbsOrigin = reinterpret_cast<oFnSetAbsOrigin>(Mem::patternScan(GetModuleHandleA("client.dll"), "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8"));
             oSetAbsOrigin(this, withOrigin);
         }

         void setAbsAngle(Vec3 withAngle) {
             using oFnSetAbsAngle = void(__thiscall*)(void*, const Vec3&);
             static auto oSetAbsAngle = reinterpret_cast<oFnSetAbsAngle>(Mem::patternScan(GetModuleHandleA("client.dll"), "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8"));
             oSetAbsAngle(this, withAngle);
         }

         // Player related NETVARS
         auto health() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_iHealth, this);
         }

         auto isScoped() {
             return Mem::getValOffset< bool >(NetvarsCollection::m_bIsScoped, this);
         }

         auto team() {
             return Mem::getValOffset< bool >(NetvarsCollection::m_iTeamNum, this);
         }

         Vec3 viewOffset() {
             return Mem::getValOffset< Vec3 >(NetvarsCollection::m_vecViewOffset, this);
         }

         Vec3 origin() {
             return Mem::getValOffset< Vec3 >(NetvarsCollection::m_vecOrigin, this);
         }

         Vec3 bone(int16_t boneIndex) {
             Vec3 headPos;

             uintptr_t boneMat = Mem::getValOffset<uintptr_t>(NetvarsCollection::m_dwBoneMatrix, this);

             headPos.x = *reinterpret_cast<float*>(boneMat + 0x30 * boneIndex + 0x0C);
             headPos.y = *reinterpret_cast<float*>(boneMat + 0x30 * boneIndex + 0x1C);
             headPos.z = *reinterpret_cast<float*>(boneMat + 0x30 * boneIndex+ 0x2C);

             return headPos;
         }

         Vec3 getEyePos() {

             return this->origin() + this->viewOffset();
         }

         int32_t viewmodelHandle () {
             return Mem::getValOffset<int32_t>(NetvarsCollection::m_hViewModelz, this);
         }

         int32_t fov() {
             return Mem::getValOffset<int32_t>(NetvarsCollection::m_iDefaultFOV, this);
         }

         void setFov(int32_t withFov) {
             //*((int32_t*)(this + )) = withFov;
             Mem::setValOffset<int32_t>(withFov, NetvarsCollection::m_iDefaultFOV, this);
         }

         EntityFlags flags() {
             return Mem::getValOffset< EntityFlags >(NetvarsCollection::m_fFlags, this);
         }

         MoveType_t moveType() {
             return Mem::getValOffset< MoveType_t >(NetvarsCollection::m_MoveType, this);
         }

         Entity_t* activeWeapon() {
             return Mem::callVirtual< Entity_t*, 267 >(this);
         }

         int32_t modelIndex() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_nModelIndex, this);
         }

         int32_t viewModelIndex() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_nViewModelIndex, this);
         }

         int32_t weaponHandle() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_nViewModelIndex, this);
         }

         int16_t itemIndex() {
             return Mem::getValOffset< int16_t >(NetvarsCollection::m_iItemDefinitionIndex, this);
         }

         uint32_t originalOwnerXuidLow() {
             return Mem::getValOffset< uint32_t >(NetvarsCollection::m_OriginalOwnerXuidLow, this);
         }

         uint32_t originalOwnerXuidHigh() {
             return Mem::getValOffset< uint32_t >(NetvarsCollection::m_OriginalOwnerXuidHigh, this);
         }

         uint64_t itemIdLow() {
             return Mem::getValOffset< uint64_t >(NetvarsCollection::m_iItemIDLow, this);
         }

         int32_t item_id_high() {
             return Mem::getValOffset< int32_t >(NetvarsCollection::m_iItemIDHigh, this);
         }

};

#endif //GOLPHOOK_FUN_ENTITY_HH
