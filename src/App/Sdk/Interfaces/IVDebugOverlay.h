//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_IVDEBUGOVERLAY_H
#define GOLPHOOK_FUN_IVDEBUGOVERLAY_H

#include "Math/Vector.hpp"
#include "Math/QAngle.hpp"

class OverlayText_t;

class IVDebugOverlay {
    public:
         virtual void            __unkn() = 0;
         virtual void            AddEntityTextOverlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
         virtual void            AddBoxOverlay(const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration) = 0;
         virtual void            AddSphereOverlay(const Vector& vOrigin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float flDuration) = 0;
         virtual void            AddTriangleOverlay(const Vector& p1, const Vector& p2, const Vector& p3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
         virtual void            AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration) = 0;
         virtual void            AddTextOverlay(const Vector& origin, float duration, const char *format, ...) = 0;
         virtual void            AddTextOverlay(const Vector& origin, int line_offset, float duration, const char *format, ...) = 0;
         virtual void            AddScreenTextOverlay(float flXPos, float flYPos, float flDuration, int r, int g, int b, int a, const char *text) = 0;
         virtual void            AddSweptBoxOverlay(const Vector& start, const Vector& end, const Vector& mins, const Vector& max, const QAngle & angles, int r, int g, int b, int a, float flDuration) = 0;
         virtual void            AddGridOverlay(const Vector& origin) = 0;
         virtual void            _dummy1() = 0;
         virtual int             ScreenPosition(const Vector& point, Vector& screen) = 0;
         virtual int             ScreenPosition(float flXPos, float flYPos, Vector& screen) = 0;
};

#endif //GOLPHOOK_FUN_IVDEBUGOVERLAY_H
