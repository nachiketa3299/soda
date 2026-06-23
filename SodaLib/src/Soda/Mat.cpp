#include "Soda/Mat.h"

#include <cassert>

namespace Soda {

Mat4f& Mat4f::operator*=(Mat4f oth) {
    Mat4f ret;
    ret[0, 0] = (*this)[0, 0] * oth[0, 0] + (*this)[0, 1] * oth[1, 0] + (*this)[0, 2] * oth[2, 0] + (*this)[0, 3] * oth[3, 0];
    ret[0, 1] = (*this)[0, 0] * oth[0, 1] + (*this)[0, 1] * oth[1, 1] + (*this)[0, 2] * oth[2, 1] + (*this)[0, 3] * oth[3, 1];
    ret[0, 2] = (*this)[0, 0] * oth[0, 2] + (*this)[0, 1] * oth[1, 2] + (*this)[0, 2] * oth[2, 2] + (*this)[0, 3] * oth[3, 2];
    ret[0, 3] = (*this)[0, 0] * oth[0, 3] + (*this)[0, 1] * oth[1, 3] + (*this)[0, 2] * oth[2, 3] + (*this)[0, 3] * oth[3, 3];

    ret[1, 0] = (*this)[1, 0] * oth[0, 0] + (*this)[1, 1] * oth[1, 0] + (*this)[1, 2] * oth[2, 0] + (*this)[1, 3] * oth[3, 0];
    ret[1, 1] = (*this)[1, 0] * oth[0, 1] + (*this)[1, 1] * oth[1, 1] + (*this)[1, 2] * oth[2, 1] + (*this)[1, 3] * oth[3, 1];
    ret[1, 2] = (*this)[1, 0] * oth[0, 2] + (*this)[1, 1] * oth[1, 2] + (*this)[1, 2] * oth[2, 2] + (*this)[1, 3] * oth[3, 2];
    ret[1, 3] = (*this)[1, 0] * oth[0, 3] + (*this)[1, 1] * oth[1, 3] + (*this)[1, 2] * oth[2, 3] + (*this)[1, 3] * oth[3, 3];

    ret[2, 0] = (*this)[2, 0] * oth[0, 0] + (*this)[2, 1] * oth[1, 0] + (*this)[2, 2] * oth[2, 0] + (*this)[2, 3] * oth[3, 0];
    ret[2, 1] = (*this)[2, 0] * oth[0, 1] + (*this)[2, 1] * oth[1, 1] + (*this)[2, 2] * oth[2, 1] + (*this)[2, 3] * oth[3, 1];
    ret[2, 2] = (*this)[2, 0] * oth[0, 2] + (*this)[2, 1] * oth[1, 2] + (*this)[2, 2] * oth[2, 2] + (*this)[2, 3] * oth[3, 2];
    ret[2, 3] = (*this)[2, 0] * oth[0, 3] + (*this)[2, 1] * oth[1, 3] + (*this)[2, 2] * oth[2, 3] + (*this)[2, 3] * oth[3, 3];

    ret[3, 0] = (*this)[3, 0] * oth[0, 0] + (*this)[3, 1] * oth[1, 0] + (*this)[3, 2] * oth[2, 0] + (*this)[3, 3] * oth[3, 0];
    ret[3, 1] = (*this)[3, 0] * oth[0, 1] + (*this)[3, 1] * oth[1, 1] + (*this)[3, 2] * oth[2, 1] + (*this)[3, 3] * oth[3, 1];
    ret[3, 2] = (*this)[3, 0] * oth[0, 2] + (*this)[3, 1] * oth[1, 2] + (*this)[3, 2] * oth[2, 2] + (*this)[3, 3] * oth[3, 2];
    ret[3, 3] = (*this)[3, 0] * oth[0, 3] + (*this)[3, 1] * oth[1, 3] + (*this)[3, 2] * oth[2, 3] + (*this)[3, 3] * oth[3, 3];

    *this = ret;

    return *this;
}

Mat4f& Mat4f::operator*=(float c) {

    for (std::size_t i = 0; i < m.size(); ++i) {
        m[i] *= c;
    }

    return *this;
}

Mat4f& Mat4f::operator/=(float c) {
    assert(c != 0.f);

    for (std::size_t i = 0; i < m.size(); ++i) {
        m[i] /= c;
    }

    return *this;
}

Mat4f Mat4f::Translate(Vec3f t) {
    Mat4f ret = Mat4f::Identity;
    ret[0, 3] = t.x;
    ret[1, 3] = t.y;
    ret[2, 3] = t.z;

    return ret;
}

Mat4f Mat4f::Scale(Vec3f s) {
    Mat4f ret = Mat4f::Identity;
    ret[0, 0] = s.x;
    ret[1, 1] = s.y;
    ret[2, 2] = s.z;

    return ret;
}

Mat4f Mat4f::Rotation(Vec3f axis, float rad) {
    Mat4f ret = Mat4f::Identity;
    auto [nx, ny, nz] = axis.Normalized();

    float c = std::cos(rad);
    float s = std::sin(rad);
    float t = 1.0f - c;

    ret[0, 0] = t * nx * ny + c;
    ret[0, 1] = t * nx * ny - s * nz;
    ret[0, 2] = t * nx * nz + s * ny;
    ret[0, 3] = 0.f;

    ret[1, 0] = t * nx * ny + s * nz;
    ret[1, 1] = t * ny * ny + c;
    ret[1, 2] = t * ny * nz - s * nx;
    ret[1, 3] = 0.f;

    ret[2, 0] = t * nx * nz - s * ny;
    ret[2, 1] = t * ny * nz + s * nx;
    ret[2, 2] = t * nz * nz + c;
    ret[2, 3] = 0.f;

    return ret;
}

}