project(SodaLib)

add_library(SodaLib STATIC
    src/Soda/FrameBuffer.cpp
    src/Soda/Rasterizer.cpp
    src/Soda/Color.cpp
    src/Soda/MathUtils.cpp
    src/Soda/Vec.cpp
    src/Soda/Line.cpp
    src/Soda/IO.cpp
    src/Soda/Fragment.cpp
    src/Soda/Mat.cpp
    src/Soda/Mesh.cpp
    src/Soda/Face.cpp
)

target_include_directories(SodaLib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)