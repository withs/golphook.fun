//
// Created by fleur on 16/11/2021.
//

#ifndef GOLPHOOK_FUN_IAPPSYSTEM_H
#define GOLPHOOK_FUN_IAPPSYSTEM_H

class IAppSystem {
    public:
         virtual void dummy() = 0;                                     // 0
         virtual void                            Disconnect() = 0;                                                           // 1
         virtual void*                           QueryInterface(const char *pInterfaceName) = 0;                             // 2
         virtual int /*InitReturnVal_t*/         Init() = 0;                                                                 // 3
         virtual void                            Shutdown() = 0;                                                             // 4
         virtual const void* /*AppSystemInfo_t*/ GetDependencies() = 0;                                                      // 5
         virtual int /*AppSystemTier_t*/         GetTier() = 0;                                                              // 6
         virtual void dummy2() = 0;
         virtual void                            UnkFunc() = 0;                                                              // 8
};

#endif //GOLPHOOK_FUN_IAPPSYSTEM_H
