include(FetchContent)

set(SDL_SHARED       ON  CACHE BOOL "" FORCE)
set(SDL_STATIC       OFF CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.10
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(SDL3)

add_library(SodaWindow STATIC
    src/Window.cpp
)

target_include_directories(SodaWindow PUBLIC include)

target_link_libraries(SodaWindow
    PUBLIC  SodaLib
    PRIVATE SDL3::SDL3
)