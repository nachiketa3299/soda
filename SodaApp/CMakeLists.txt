project(SodaApp)

add_library(SodaApp STATIC
    src/App.cpp
    src/Clock.cpp
)
target_include_directories(SodaApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(SodaApp
    PUBLIC SodaLib
    PUBLIC SodaWindow
)