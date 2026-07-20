cmake_minimum_required(VERSION 3.10...3.50) # leave it as range <min>...<max>
project(aur)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
add_library(miniaudio STATIC includes/miniaudio.c)
add_executable(aur
    # includes
    includes/cmath.cpp
    includes/glad/glad.c
    includes/imgui/backends/imgui_impl_glfw.cpp
    includes/imgui/backends/imgui_impl_opengl3.cpp
    includes/imgui/imgui_tables.cpp
    includes/imgui/imgui_demo.cpp
    includes/imgui/imgui_widgets.cpp
    includes/imgui/imgui_draw.cpp
    includes/imgui/imgui.cpp
    includes/imgui/imgui_demo.cpp
    includes/stb_image.cpp
    includes/miniaudio.c
    src/main.cpp
    # aur
    src/aur/aur.cpp
    src/aur/camera.cpp
    # will change later
    src/aur/view/shader.cpp
    src/aur/view/VAO.cpp
    src/aur/view/VBO.cpp
    src/aur/view/EBO.cpp
    src/aur/view/texture.cpp
    # editor
    src/editor/viewportEditor.cpp
    src/editor/materialMaker.cpp
    src/editor/objectManipulator.cpp
    src/editor/soundOrganizer.cpp
    src/editor/settings.cpp
    # project
    src/project/project.cpp
)
target_include_directories(aur PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/aur
    ${CMAKE_SOURCE_DIR}/src/aur/view
    ${CMAKE_SOURCE_DIR}/src/editor
    ${CMAKE_SOURCE_DIR}/src/project
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_SOURCE_DIR}/includes
    ${CMAKE_SOURCE_DIR}/includes/glad
    ${CMAKE_SOURCE_DIR}/includes/glad/include
    ${CMAKE_SOURCE_DIR}/includes/imgui
    ${CMAKE_SOURCE_DIR}/includes/imgui/backends
)
target_compile_definitions(aur PRIVATE # to be removed ?
    IMGUI_IMPL_OPENGL_LOADER_GLAD
    AUR_DEVELOPER=1
    AUR_DEBUG=0
    AUR_RELEASE=0
)
target_compile_options(aur PRIVATE 
    -O3
    -g3
    # -Wall
    # -Wextra
    # -Wpedantic
    # -Wconversion
    # -Wsign-conversion
    # -Wfloat-conversion
    # -Wnarrowing
    # -Wuninitialized
    # -Winit-self
    # -Wnull-dereference
    # -Wuse-after-free
    # -Wdangling-pointer
    # -Wdangling-reference
    # -Waddress
    # -Wreorder
    # -Wno-array-bounds
    # -Woverloaded-virtual
    # -Wmissing-declarations
    # -Wmissing-prototypes
    # -Walloca
    -Wno-stringop-overflow # miniaudio
    # -Wdouble-promotion # annoying
    # -fsanitize=address
    # -fsanitize=undefined
)
# target_link_options(aur PRIVATE
    # -fsanitize=address
    # -fsanitize=undefined
# )
target_link_libraries(aur
    glfw
    OpenGL::GL
    miniaudio
)