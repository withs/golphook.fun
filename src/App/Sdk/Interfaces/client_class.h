//
// Created by fleur on 16/11/2021.
//

#ifndef GOLPHOOK_FUN_CLIENT_CLASS_H
#define GOLPHOOK_FUN_CLIENT_CLASS_H

#include "dt_recv.h"

class ClientClass;

class ClientClass {
    public:
         void*             m_pCreateFn;
         void*             m_pCreateEventFn;
         char*             m_pNetworkName;
         RecvTable*        m_pRecvTable;
         ClientClass*      m_pNext;
         int               m_ClassID;
};

#endif //GOLPHOOK_FUN_CLIENT_CLASS_H
