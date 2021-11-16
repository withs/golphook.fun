//
// Created by fleur on 16/11/2021.
//

#ifndef GOLPHOOK_FUN_IINPUTSYSTEM_H
#define GOLPHOOK_FUN_IINPUTSYSTEM_H

#include "IAppSystem.h"

class IInputSystem : IAppSystem {
    public:
         virtual void AttachToWindow( void* hWnd ) = 0;
         virtual void DetachFromWindow( ) = 0;
         virtual void EnableInput( bool bEnable ) = 0;
         virtual void EnableMessagePump( bool bEnable ) = 0;
         virtual void PollInputState() = 0;
         virtual int GetPollTick() const = 0;
};

#endif //GOLPHOOK_FUN_IINPUTSYSTEM_H
