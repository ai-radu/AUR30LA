cmake_minimum_required(VERSION 3.5)
project(AUR30LA)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(AUR30LA
    src/config.h
    src/main.cpp
    src/glad.c
    src/systems/camera_system.cpp
    src/systems/motion_system.cpp
    src/systems/render_system.cpp
    src/view/shader.cpp
    src/controller/app.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_draw.cpp
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
)

target_include_directories(AUR30LA PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_SOURCE_DIR}/dependencies
    ${CMAKE_SOURCE_DIR}/dependencies/glad/include
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
)

target_compile_definitions(AUR30LA PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLAD
)

target_compile_definitions(AUR30LA PRIVATE
    AUR_DEBUG=0
    AUR_EXPERIMENTAL=0
    AUR_EXPERIMENTAL_DEBUG=0
)

target_link_libraries(AUR30LA
    glfw
    OpenGL::GL
)