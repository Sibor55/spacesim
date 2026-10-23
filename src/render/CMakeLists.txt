find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_library(render_lib STATIC Renderer.cpp)

target_include_directories(render_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(render_lib PRIVATE core_lib)
target_link_libraries(render_lib PUBLIC SFML::Graphics SFML::Window SFML::System)