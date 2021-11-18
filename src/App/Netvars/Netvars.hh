//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_NETVARSDUMPER_HH
#define GOLPHOOK_FUN_NETVARSDUMPER_HH

#include "CommonIncludes.hh"

#include "Utils/Utils.hh"
#include "Utils/SharedObject.hh"
#include "Utils/Errors/Fatal.hh"

#include "NetvarsCollection.hh"

#include "Sdk/InterfacesCollection.hh"
#include "Sdk/Interfaces/client_class.h"


class NetvarsDumper: public SharedObject<NetvarsDumper> {

    private:
         intptr_t _getOffset(RecvTable* inTable, std::string withTableName, std::string forNetvarName) noexcept;
         ClientClass* _clientClass = nullptr;

    public:
         NetvarsDumper();

         intptr_t getNetVarOffset(std::string withTableName,std::string forNetvarName);
};


#endif //GOLPHOOK_FUN_NETVARSDUMPER_HH
