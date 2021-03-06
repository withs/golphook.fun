//
// Created by fleur on 14/11/2021.
//

#include "CreateMoove.hh"

bool __stdcall CreateMoove::hooked(int sequence_number, float input_sample_frametime, bool active, bool bSendPacket) {

    CreateMoove::original(InterfacesCollection::i_baseClient, sequence_number, input_sample_frametime, active);

    App::Get().cmd = InterfacesCollection::i_cinput->GetUserCmd(sequence_number);
    CVerifiedUserCmd    * verified = InterfacesCollection::i_cinput->GetVerifiedCmd(sequence_number);

    if ( App::Get().ready ) {
        Features::Get().others->onCreateMoove();
    }
    verified->m_cmd = *App::Get().cmd;
    verified->m_crc = App::Get().cmd->GetChecksum();
    return false;
}

__declspec(naked) void __stdcall CreateMoove::proxy(int sequence_number, float input_sample_frametime, bool active) {
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esp
        push dword ptr[active]
        push dword ptr[input_sample_frametime]
        push dword ptr[sequence_number]
        call hooked
        pop ebx
        pop ebp
        retn 0Ch
    }
}
