add_subdirectory(core)
add_subdirectory(render)


add_executable(spacesim main.cpp)
target_link_libraries(spacesim PRIVATE core_lib render_lib)