#pragma once

namespace Soda {

struct Vec2i {
    int x;
    int y;

    static int Cross(const Vec2i& u, const Vec2i& v);

    Vec2i operator+(const Vec2i& oth) const;
    Vec2i operator-(const Vec2i& oth) const;
};

}