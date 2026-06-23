#pragma once

#include "Soda/Vertex.h"
#include "Soda/Face.h"

#include <vector>

namespace Soda {

struct Mesh {
    std::vector<Vertex3f> v;
    std::vector<Face> f;

    static const Mesh TestCube;
};

inline const Mesh Mesh::TestCube {
    .v = {
        Vertex3f { .p = {  0.5f,  0.5f,  0.5f }, .c = Color4f::Red }, // A0
        Vertex3f { .p = {  0.5f,  0.5f, -0.5f }, .c = Color4f::Red }, // B1
        Vertex3f { .p = {  0.5f, -0.5f,  0.5f }, .c = Color4f::Red }, // C2
        Vertex3f { .p = {  0.5f, -0.5f, -0.5f }, .c = Color4f::Red }, // D3
        Vertex3f { .p = { -0.5f,  0.5f,  0.5f }, .c = Color4f::Blue }, // E4
        Vertex3f { .p = { -0.5f,  0.5f, -0.5f }, .c = Color4f::Blue }, // F5
        Vertex3f { .p = { -0.5f, -0.5f,  0.5f }, .c = Color4f::Blue }, // G6
        Vertex3f { .p = { -0.5f, -0.5f, -0.5f }, .c = Color4f::Blue }, // H7
    },
    .f = {
        { 0, 1, 3 }, { 0, 3, 2 }, // 우 x+  ABCD
        { 4, 5, 7 }, { 4, 7, 6 }, // 좌 x-  EFGH
        { 0, 1, 5 }, { 0, 5, 4 }, // 상 y+  ABEF
        { 2, 3, 7 }, { 2, 7, 6 }, // 하 y-  CDGH
        { 0, 2, 6 }, { 0, 6, 4 }, // 앞 z+  ACEG
        { 1, 3, 7 }, { 1, 7, 5 }, // 뒤 z-  BDFH
    },
};

}