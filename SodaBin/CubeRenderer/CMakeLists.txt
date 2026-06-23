add_executable(CubeRenderer
    main.cpp
)

target_link_libraries(CubeRenderer 
    PRIVATE SodaLib SodaWindow SodaApp)