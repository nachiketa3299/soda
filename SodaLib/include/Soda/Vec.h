#pragma once

#include <cmath>

namespace Soda {

struct Vec2i {
    int x, y;

    Vec2i& operator+=(Vec2i oth);
    Vec2i& operator-=(Vec2i oth);

    inline Vec2i operator-() const { return { -x, -y }; }
};

inline Vec2i operator+(Vec2i l, Vec2i r) { return l += r; }
inline Vec2i operator-(Vec2i l, Vec2i r) { return l -= r; }

inline int Cross(Vec2i u, Vec2i v) { return u.x * v.y - u.y * v.x; }

struct Vec2f {
    float x, y;

    Vec2f& operator+=(Vec2f oth);
    Vec2f& operator-=(Vec2f oth);
    Vec2f& operator*=(float s);
    Vec2f& operator/=(float s);

    inline Vec2f operator-() const { return { -x, -y }; }

    inline float LengthSquared() const { return x * x + y * y; }
    inline float Length() const { return std::sqrt(LengthSquared()); }
    Vec2f Normalized() const;
};

inline Vec2f operator+(Vec2f l, Vec2f r) { return l += r; }
inline Vec2f operator-(Vec2f l, Vec2f r) { return l -= r; }
inline Vec2f operator*(float l, Vec2f r) { return r *= l; }
inline Vec2f operator*(Vec2f l, float r) { return l *= r; }
inline Vec2f operator/(Vec2f l, float r) { return l /= r; }

inline float Dot(Vec2f u, Vec2f v) { return u.x * v.x + u.y * v.y; }
inline float Cross(Vec2f u, Vec2f v) { return u.x * v.y - u.y * v.x; }

struct Vec3f {
    float x, y, z;

    Vec3f& operator+=(Vec3f oth);
    Vec3f& operator-=(Vec3f oth);
    Vec3f& operator*=(float c);
    Vec3f& operator/=(float c);

    inline Vec3f operator-() const { return { -x, -y, -z }; }

    inline float LengthSquared() const { return x * x + y * y + z * z; }
    inline float Length() const { return std::sqrt(LengthSquared()); }
    Vec3f Normalized() const;
};

inline Vec3f operator+(Vec3f l, Vec3f r) { return l += r; }
inline Vec3f operator-(Vec3f l, Vec3f r) { return l -= r; }
inline Vec3f operator*(Vec3f l, float r) { return l *= r; }
inline Vec3f operator*(float l, Vec3f r) { return r *= l; }
inline Vec3f operator/(Vec3f l, float r) { return l /= r; }

inline float Dot(Vec3f l, Vec3f r) { return l.x * r.x + l.y * r.y + l.z * r.z; }
inline Vec3f Cross(Vec3f l, Vec3f r) {
    return Vec3f {
        l.y * r.z - l.z * r.y,
        l.z * r.x - l.x * r.z,
        l.x * r.y - l.y * r.x
    };
}

struct Vec4f {
    float x, y, z, w;

    Vec4f& operator+=(Vec4f oth);
    Vec4f& operator-=(Vec4f oth);
    Vec4f& operator*=(float c);
    Vec4f& operator/=(float c);

    inline Vec4f operator-() const { return { -x, -y, -z, -w }; }
};

inline Vec4f operator+(Vec4f l, Vec4f r) { return l += r; }
inline Vec4f operator-(Vec4f l, Vec4f r) { return l -= r; }
inline Vec4f operator*(Vec4f l, float r) { return l *= r; }
inline Vec4f operator*(float l, Vec4f r) { return r *= l; }
inline Vec4f operator/(Vec4f l, float r) { return l /= r; }

}