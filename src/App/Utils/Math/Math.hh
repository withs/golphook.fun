//
// Created by fleur on 19/11/2021.
//

#ifndef GOLPHOOK_FUN_MATH_HH
#define GOLPHOOK_FUN_MATH_HH

#include "cmath"

#include "Utils/Structs/Vector.hh"
#include "Sdk/InterfacesCollection.hh"
#include "Utils/Math/Consts.hh"

class Math {

    public:
         static bool screenTransform(const Vec3& in, Vec3& out);
         static bool worldToScreen(const Vec3& in, Vec3& out);
         static void sinCos(float withRadian, float& andSin, float& andCos);
         static void angleToVectors(Vec3& withAngle, Vec3& andYaw, Vec3& andRoll, Vec3& andPitch);

};


#endif //GOLPHOOK_FUN_MATH_HH
