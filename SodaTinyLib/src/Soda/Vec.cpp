#include "Soda/Vec.h"

namespace Soda {

int Vec2i::Cross(const Vec2i& u, const Vec2i& v) {
    return u.x * v.y - u.y * v.x;
}

Vec2i Vec2i::operator+(const Vec2i& oth) const {
    return Vec2i { x + oth.x, y + oth.y };
}

Vec2i Vec2i::operator-(const Vec2i& oth) const {
    return Vec2i { x - oth.x, y - oth.y };
}

}