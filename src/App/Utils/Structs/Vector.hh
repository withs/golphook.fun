//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_VECTOR_HH
#define GOLPHOOK_FUN_VECTOR_HH


struct __Angle {
    float pitch;	// x
    float yaw;		// y
    float roll;		// z

    inline __Angle_t& operator*= (const float scalar) noexcept {
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

    inline vec3_t operator+ (const vec3_t& rhs) const noexcept {
        return vec3_t{this->x + rhs.x, this->y + rhs.y, this->z + rhs.z};
    }

    inline vec3_t operator* (const vec3_t& rhs) const noexcept {
        return vec3_t{this->x * rhs.x, this->y * rhs.y, this->z * rhs.z};
    }

    inline float dot_product(const vec3_t& rhs) const noexcept {
        return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
    }
};

struct Vec2 {
    float x, y;
};


#endif //GOLPHOOK_FUN_VECTOR_HH
