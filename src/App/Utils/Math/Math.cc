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