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

         bool dormant() {
             return Mem::callVirtual< bool, 9 >(networkable());
         }

         bool isAlive() {
             return Mem::callVirtual<bool, 155>(this);
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

         Vec3 origin() {
             return Mem::getValOffset< Vec3 >(NetvarsCollection::m_vecOrigin, this);
         }

};

#endif //GOLPHOOK_FUN_ENTITY_HH
