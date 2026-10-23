add_library(core_lib STATIC
    WorldState.cpp
    PhysicsEngine.cpp
)

#
target_include_directories(core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})