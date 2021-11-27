//
// Created by fleur on 19/11/2021.
//

#include "Math.hh"


bool Math::screenTransform( const Vec3& in, Vec3& out ) {
    static auto& w2sMatrix = InterfacesCollection::i_engineClient->WorldToScreenMatrix();;

    out.x = w2sMatrix.m[0][0] * in.x + w2sMatrix.m[0][1] * in.y + w2sMatrix.m[0][2] * in.z + w2sMatrix.m[0][3];
    out.y = w2sMatrix.m[1][0] * in.x + w2sMatrix.m[1][1] * in.y + w2sMatrix.m[1][2] * in.z + w2sMatrix.m[1][3];
    out.z = 0.0f;

    float w = w2sMatrix.m[3][0] * in.x + w2sMatrix.m[3][1] * in.y + w2sMatrix.m[3][2] * in.z + w2sMatrix.m[3][3];

    if( w < 0.001f ) {
        out.x *= 100000;
        out.y *= 100000;
        return false;
    }

    out.x /= w;
    out.y /= w;

    return true;
}

bool Math::worldToScreen( const Vec3& in, Vec3& out ) {
    if ( screenTransform(in, out) ) {
        int w, h;
        InterfacesCollection::i_engineClient->GetScreenSize(w,h);

        out.x = (w / 2.0f) + (out.x * w) / 2.0f;
        out.y = (h / 2.0f) - (out.y * h) / 2.0f;

        return true;
    }
    return false;
}

void Math::sinCos(float withRadian, float& andSin, float& andCos) {
    andSin = std::sin(withRadian);
    andCos = std::cos(withRadian);
}


void Math::angleToVectors(Vec3 &withAngle, Vec3 &andFor, Vec3 &andRight, Vec3 &andUp) {

    float sp, sy, sr, cp, cy, cr;

    Math::sinCos(Consts::radian * withAngle.x, sp, cp);
    Math::sinCos(Consts::radian * withAngle.y, sy, cy);
    Math::sinCos(Consts::radian * withAngle.z, sr, cr);

    andFor.x = cp * cy;
    andFor.y = cp * sy;
    andFor.z = -sp;

    andRight.x = -1.0f * sr * sp * cy + -1.0f * cr * -sy;
    andRight.y = -1.0f * sr * sp * sy + -1.0f * cr * cy;
    andRight.z = -1.0f * sr * cp;

    andUp.x = cr * sp * cy + -sr * -sy;
    andUp.y = cr * sp * sy + -sr * cy;
    andUp.z = cr * cp;
}

float Math::distanceToEntity(const Vec3 &fromLocalPlayer, const Vec3 &toEnemy) {
    return sqrt(pow(fromLocalPlayer.x - toEnemy.x, 2) + pow(fromLocalPlayer.y - toEnemy.y, 2) + pow(fromLocalPlayer.z - toEnemy.z, 2));
}
