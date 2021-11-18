//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_VECTOR_HH
#define GOLPHOOK_FUN_VECTOR_HH


struct __Angle {
    float pitch;	// x
    float yaw;		// y
    float roll;		// z

    inline __Angle& operator*= (const float scalar) noexcept {
        this->pitch *= scalar;
        this->yaw *= scalar;
        this->roll *= scalar;

        return *this;
    }
};

struct Vec4 {
    float x, y, z, w;
};


struct Vec3 {
    float x, y, z;

    inline Vec3 operator+ (const Vec3& rhs) const noexcept {
        return Vec3{this->x + rhs.x, this->y + rhs.y, this->z + rhs.z};
    }

    inline Vec3 operator* (const Vec3& rhs) const noexcept {
        return Vec3{this->x * rhs.x, this->y * rhs.y, this->z * rhs.z};
    }

    inline float dot_product(const Vec3& rhs) const noexcept {
        return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
    }
};

template <class T>
struct Vec2 {
    T x, y;
};


#endif //GOLPHOOK_FUN_VECTOR_HH
