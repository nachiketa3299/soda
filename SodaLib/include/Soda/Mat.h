#pragma once

#include "Vec.h"

#include <array>
#include <cstddef>

namespace Soda {

// Row-Major
struct Mat4f{
    constexpr inline float& operator[](int r, int c)       { return m[static_cast<std::size_t>(c + 4 * r)]; }
    constexpr inline float  operator[](int r, int c) const { return m[static_cast<std::size_t>(c + 4 * r)]; }

    Mat4f& operator*=(Mat4f oth);
    Mat4f& operator*=(float c);
    Mat4f& operator/=(float c);

    static Mat4f Translate(Vec3f t);
    static Mat4f Scale(Vec3f s);
    static Mat4f Rotation(Vec3f axis, float rad);

    static const Mat4f Identity;
    static const Mat4f Zero;

    std::array<float, 16> m {};
};

inline Mat4f operator*(Mat4f l, Mat4f r) { return l *= r; }
inline Vec4f operator*(Mat4f oth, Vec4f v) {
    return Vec4f {
        .x = oth[0, 0] * v.x + oth[0, 1] * v.y + oth[0, 2] * v.z + oth[0, 3] * v.w,
        .y = oth[1, 0] * v.x + oth[1, 1] * v.y + oth[1, 2] * v.z + oth[1, 3] * v.w,
        .z = oth[2, 0] * v.x + oth[2, 1] * v.y + oth[2, 2] * v.z + oth[2, 3] * v.w,
        .w = oth[3, 0] * v.x + oth[3, 1] * v.y + oth[3, 2] * v.z + oth[3, 3] * v.w,
    };
}

inline constexpr Mat4f Mat4f::Identity {
    .m = {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    }
};

inline constexpr Mat4f Mat4f::Zero {
    .m = {
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f
    }
};

}