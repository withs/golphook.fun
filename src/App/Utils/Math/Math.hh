//
// Created by fleur on 19/11/2021.
//

#ifndef GOLPHOOK_FUN_MATH_HH
#define GOLPHOOK_FUN_MATH_HH

#include "Utils/Structs/Vector.hh"
#include "Sdk/InterfacesCollection.hh"

class Math {

    public:
         static bool screenTransform(const Vec3& in, Vec3& out);
         static bool worldToScreen(const Vec3& in, Vec3& out);

};


#endif //GOLPHOOK_FUN_MATH_HH
