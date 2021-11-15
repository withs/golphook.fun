//
// Created by fleur on 15/11/2021.
//

#ifndef GOLPHOOK_FUN_UTILS_HH
#define GOLPHOOK_FUN_UTILS_HH

#include "CommonIncludes.hh"

class Utils {
    public:
         static void allocateConsole();
         static void freeConsole();

         static void waitForModule(std::vector<std::string> inModulesList, uint16_t withTimeout);
};


#endif //GOLPHOOK_FUN_UTILS_HH