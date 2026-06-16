project(SodaTinyLib)

add_library(SodaTinyLib STATIC
    src/Soda/FrameBuffer.cpp
    src/Soda/Rasterizer.cpp
    src/Soda/Color.cpp
    src/Soda/MathUtils.cpp
    src/Soda/Vec.cpp
    src/Soda/Line.cpp
    src/Soda/PPM.cpp
)

target_include_directories(SodaTinyLib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)