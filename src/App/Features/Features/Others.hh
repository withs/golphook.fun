//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_OTHERS_HH
#define GOLPHOOK_FUN_OTHERS_HH

#include "CommonIncludes.hh"

#include "chrono"

#include "Sdk/InterfacesCollection.hh"
#include "Sdk/Functions/Functions.hh"
#include "Sdk/Interfaces/Misc/Enums.hh"
#include "Utils/Structs/Color.hh"
#include "Utils/Math/Math.hh"

class Others {
    private:
         void _bop();

         std::string _currentTag = "";
         void _tag();
         void _fovCircle();
         void _indicators();

    public:
         void onCreateMoove();
         void onFrame();

         void overrideViewmodel();
};


#endif //GOLPHOOK_FUN_OTHERS_HH
