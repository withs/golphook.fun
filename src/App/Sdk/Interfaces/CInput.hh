//
// Created by fleur on 24/11/2021.
//

#ifndef GOLPHOOK_FUN_CINPUT_HH
#define GOLPHOOK_FUN_CINPUT_HH

#include "CommonIncludes.hh"

#include "Utils/Memory/Mem.hh"

#include "Sdk/Interfaces/Misc/CUserCmd.h"

#define MULTIPLAYER_BACKUP 150

class bf_write;
class bf_read;

class CInput
{
    public:
         char                pad_0x00[0x0C];
         bool                m_trackir_available;
         bool                m_mouse_initiated;
         bool                m_mouse_active;
         bool                m_fJoystickAdvancedInit;
         char                pad_0x08[0x2C];
         void*               m_pKeys;
         char                pad_0x38[0x6C];
         bool                m_fCameraInterceptingMouse;
         bool                m_fCameraInThirdPerson;
         bool                m_fCameraMovingWithMouse;
         Vector		    m_vecCameraOffset;
         bool                m_fCameraDistanceMove;
         int                 m_nCameraOldX;
         int                 m_nCameraOldY;
         int                 m_nCameraX;
         int                 m_nCameraY;
         bool                m_CameraIsOrthographic;
         Vector              m_angPreviousViewAngles;
         Vector              m_angPreviousViewAnglesTilt;
         float               m_flLastForwardMove;
         int                 m_nClearInputState;
         char                pad_0xE4[0x8];
         CUserCmd*           m_pCommands;
         CVerifiedUserCmd*   m_pVerifiedCommands;

         inline CUserCmd* GetUserCmd(int sequence_number);
         inline CUserCmd * GetUserCmd(int nSlot, int sequence_number);
         inline CVerifiedUserCmd* GetVerifiedCmd(int sequence_number);
};

CUserCmd* CInput::GetUserCmd(int withSeq) {
    return Mem::callVirtual<CUserCmd*, 8>(this, 0, withSeq);
}

CUserCmd *CInput::GetUserCmd(int nSlot, int withSeq) {
    return Mem::callVirtual<CUserCmd*, 8>(this, nSlot, withSeq);
}

CVerifiedUserCmd* CInput::GetVerifiedCmd(int withSeq) {
    auto verifiedCommands = *(CVerifiedUserCmd **)(reinterpret_cast<int32_t>(this) + 0xF8);
    return &verifiedCommands[withSeq % MULTIPLAYER_BACKUP];
}

#endif //GOLPHOOK_FUN_CINPUT_HH
