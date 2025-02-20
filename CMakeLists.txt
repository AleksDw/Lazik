cmake_minimum_required(VERSION 3.12.0)
project(hello_window VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

add_subdirectory(dependencies/glfw EXCLUDE_FROM_ALL)

add_executable(hello_window
    src/config.h
    src/config.cpp
    src/main.cpp 
    src/glad.c
    src/factories/factory.cpp
    src/systems/camera_system.cpp
    src/systems/motion_system.cpp
    src/systems/render_system.cpp
    src/view/shader.cpp
    src/controller/app.cpp
 "src/systems/rover_system.cpp" "src/systems/rover_system.h" "src/components/hitBox_component.h" "src/components/transformHitBox_component.h" "src/components/hitBoxTerrain_component.h")

target_include_directories(hello_window 
    PRIVATE
    dependencies 
)

target_link_libraries(hello_window
    glfw
    OpenGL::GL 
)