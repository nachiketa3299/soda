PROJECT(SodaTiny)

ADD_EXECUTABLE(SodaTiny
    src/main.cpp

    src/PPM/FrameBuffer3.cpp
    src/PPM/Renderer3.cpp
)

TARGET_INCLUDE_DIRECTORIES(SodaTiny
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)