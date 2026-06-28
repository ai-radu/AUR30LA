## solo project. i have no idea what i'm doing. please don't sue me. thanks
### Libraries used
- [Assimp](https://github.com/assimp/assimp)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [Glad](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [JSON](https://github.com/nlohmann/json)
- [Khronos](https://www.khronos.org/)
- [miniaudio](https://github.com/mackron/miniaudio)
- [OpenGL](https://www.opengl.org/)
- [stb](https://github.com/nothings/stb)

### Prerequisites
*for a fresh install*

    sudo apt update
    sudo apt upgrade
    sudo apt install build-essential
    sudo apt install g++
    sudo apt install cmake
    sudo apt install ninja-build
    sudo apt install pkg-config
    sudo apt install libglfw3-dev
    sudo apt install git

## QuickStart

1. Download the source archive or clone the repository:

        git clone https://github.com/ai-radu/AUR30LA

2. Build, in root:

        rm -rf build && cmake -S . -B build -G Ninja && cmake --build build && cd build && ./aur