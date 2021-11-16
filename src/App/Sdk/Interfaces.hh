//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_INTERFACES_HH
#define GOLPHOOK_FUN_INTERFACES_HH

#include "CommonIncludes.hh"

#include "Utils/Errors/Fatal.hh"
#include "Utils/SharedObject.hh"
#include "Utils/Utils.hh"
#include "InterfacesCollection.hh"

typedef void*(*oCreateInterface)(char*, int);

class Interfaces: public SharedObject<Interfaces> {

    public:
        Interfaces();
    private:

        template<typename T>
        T* _getInterface(std::string fromModuleName, std::string withName) {
            // TODO: regarder sir c_str retourne un const et voir si avec un const cast ca fix le pb
            HMODULE moduleHandle;
            oCreateInterface pCreateInterface;

            if ( moduleHandle = GetModuleHandleA(fromModuleName.c_str()) ) {
                if ( pCreateInterface = (oCreateInterface)GetProcAddress(moduleHandle, "CreateInterface") ) {
                    T* interfaceAddr;
                    if ( !( interfaceAddr = (T*)(pCreateInterface(const_cast<char*>(withName.c_str()), 0)) ) ) {
                        throw FatalError::CreateInterfaceError("Null address returned for interface: " + withName + " from module: " + fromModuleName);
                    }
                    PLOGD << Utils::stringAlign("Interface: " + withName, 45, "|") << std::hex << interfaceAddr << std::dec;
                    return interfaceAddr;
                } else {
                    throw FatalError::CreateInterfaceError("Failed get CreateInterface function from module" + fromModuleName);
                }
            } else {
                throw FatalError::GetModuleProcAddrError("Failed get handle from module" + fromModuleName);
            }
        }
};


#endif //GOLPHOOK_FUN_INTERFACES_HH
