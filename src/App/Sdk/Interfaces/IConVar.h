//
// Created by fleur on 16/11/2021.
//

#ifndef GOLPHOOK_FUN_ICONVAR_H
#define GOLPHOOK_FUN_ICONVAR_H

#include "Utils/Memory/Mem.hh"

enum class CvarFlags : int {
    fcvar_none = 0,
    fcvar_unregistered = 1 << 0,
    fcvar_development_only = 1 << 1,
    fcvar_game_dll = 1 << 2,
    fcvar_client_dll = 1 << 3,
    fcvar_hidden = 1 << 4,
    fcvar_protected = 1 << 5,
    fcvar_sp_only = 1 << 6,
    fcvar_archive = 1 << 7,
    fcvar_notify = 1 << 8,
    fcvar_user_info = 1 << 9,
    fcvar_printable_only = 1 << 10,
    fcvar_unlogged = 1 << 11,
    fcvar_never_as_string = 1 << 12,
    fcvar_replicated = 1 << 13,
    fcvar_cheat = 1 << 14,
    fcvar_ss = 1 << 15,
    fcvar_demo = 1 << 16,
    fcvar_no_record = 1 << 17,
    fcvar_ss_added = 1 << 18,
    fcvar_release = 1 << 19,
    fcvar_reload_materials = 1 << 20,
    fcvar_reload_textures = 1 << 21,
    fcvar_not_connected = 1 << 22,
    fcvar_material_system_thread = 1 << 23,
    fcvar_archive_xbox = 1 << 24,
    fcvar_accessible_from_threads = 1 << 25,
    fcvar_server_can_execute = 1 << 28,
    fcvar_server_cannot_query = 1 << 29,
    fcvar_clientcmd_can_execute = 1 << 30,
    fcvar_unused = 1 << 31,
    fcvar_material_thread_mask = fcvar_reload_materials | fcvar_reload_textures | fcvar_material_system_thread
};

struct Convar {
    public:
         float getFloat() {
             return Mem::callVirtual< float, 12 >(this);
         }

         int getInt() {
             return Mem::callVirtual< int, 13 >(this);
         }

         void setValue(const char* value) {
             return Mem::callVirtual< void, 14, const char* >(this, value);
         }

         void setValue(const float value) {
             return Mem::callVirtual< void, 15, float >(this, value);
         }

         void setValue(const int value) {
             return Mem::callVirtual< void, 16, int >(this, value);
         }

         uint8_t pad[24];
         void* change_callback;
         Convar* parent;
         const char* default_value;
         char* get_string;
         uint8_t pad1[28];
         void* on_change_callbacks;
};

#endif //GOLPHOOK_FUN_ICONVAR_H
