#include "Soda/Vec.h"

#include <cassert>

namespace Soda {

Vec2i& Vec2i::operator+=(Vec2i oth) {
    x += oth.x;
    y += oth.y;

    return *this;
}

Vec2i& Vec2i::operator-=(Vec2i oth){
    x -= oth.x;
    y -= oth.y;

    return *this;
}

Vec2f Vec2f::Normalized() const {
    float len = Length();
    assert(len != 0.f);

    return *this / len;
}

Vec2f& Vec2f::operator+=(Vec2f oth) {
    x += oth.x;
    y += oth.y;

    return *this;
}

Vec2f& Vec2f::operator-=(Vec2f oth) {
    x -= oth.x;
    y -= oth.y;

    return *this;
}

Vec2f& Vec2f::operator*=(float oth) {
    x *= oth;
    y *= oth;

    return *this;
}

Vec2f& Vec2f::operator/=(float oth) {
    assert(oth != 0.f);

    x /= oth;
    y /= oth;

    return *this;
}

Vec3f& Vec3f::operator+=(Vec3f oth) {
    x += oth.x;
    y += oth.y;
    z += oth.z;

    return *this;
}

Vec3f& Vec3f::operator-=(Vec3f oth) {
    x -= oth.x;
    y -= oth.y;
    z -= oth.z;

    return *this;
}

Vec3f& Vec3f::operator*=(float c) {
    x *= c;
    y *= c;
    z *= c;

    return *this;
}

Vec3f& Vec3f::operator/=(float c) {
    assert(c != 0.f);
    x /= c;
    y /= c;
    z /= c;

    return *this;
}

Vec3f Vec3f::Normalized() const {
    float len = Length();
    assert(len != 0.f);

    return *this / len;
}

Vec4f& Vec4f::operator+=(Vec4f oth) {
    x += oth.x;
    y += oth.y;
    z += oth.z;
    w += oth.w;

    return *this;
}

Vec4f& Vec4f::operator-=(Vec4f oth) {
    x -= oth.x;
    y -= oth.y;
    z -= oth.z;
    w -= oth.w;

    return *this;
}

Vec4f& Vec4f::operator*=(float c) {
    x *= c;
    y *= c;
    z *= c;
    w *= c;

    return *this;
}

Vec4f& Vec4f::operator/=(float c) {
    x /= c;
    y /= c;
    z /= c;
    w /= c;

    return *this;
}

}