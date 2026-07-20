#pragma once
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <string>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <chrono>
#include <time.h>
#include <ctime>
#include <cmath>
#include <random>
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <nlohmann/json.hpp>
#include "miniaudio.h"
//
#include "view/texture.hpp"
#include "view/shader.hpp"
#include "view/VAO.hpp"
#include "view/VBO.hpp"
#include "view/EBO.hpp"
#include "camera.hpp"
#include "components.hpp"
#include "variables.hpp"
struct AUR {
    std::string saveData = "../save/aur.json";
    std::vector<std::string> m_vContent;
    struct Settings {
        inline static c32 tooltipOffset          = 0;
        inline static f32 hoverDelay             = 0.15f;
        inline static v2  buttonTextAlign        = v2(0.5f, 0.5f);
        inline static c1  antiAliasedLines       = true;
        inline static c1  antiAliasedLinesUseTex = true;
        inline static c1  antiAliasedFill        = true;
    };
    struct Editor {
        inline static f32 colorMarkerSize        = 3.0f;
        inline static VAR::Dir colorMarkerPosition = VAR::Dir_Right;
        inline static VAR::Dir viewportPanel     = VAR::Dir_Left;
        inline static c1 debugNOTIF              = false;
        inline static c1 shipNOTIF               = false;
        inline static c1 terminalNOTIF           = true;
        inline static c1 debugWARNING            = true;
        inline static c1 shipWARNING             = false;
        inline static c1 terminalWARNING         = true;
        inline static c1 debugERROR              = true;
        inline static c1 shipERROR               = true;
        inline static c1 terminalERROR           = true;
    };
    enum Theme {
        Dark,
        Light,
        Classic
    };
    Theme currentTheme = Dark;
    inline static uiSliderFlags sliderFlags = 0;
    GLFWwindow* window;
    inline static c32 screenMode   = 0; // 0 windowed 1 borderless 2 fullscreen
    inline static c32 windowWidth  = 1240;
    inline static c32 windowHeight = 720;
    inline static c32 viewportWidth, viewportHeight;
    inline static v2  viewportPosition;
    u32 frameBuffer, framebufferTexture, renderBuffer;
    inline static f32 currentFrame, lastFrame, deltaTime;
    inline static v4 backgroundColor = {0.4f, 0.5f, 0.6f, 1.0f};
    inline static c1 autoSave = true;
    inline static c1 autoLoad = true;
    struct Snap {
        inline static std::array<f32, 8> MovePresets = {
            0.1f,   // 0
            0.5f,   // 1
            1.0f,   // 2
            5.0f,   // 3
            10.0f,  // 4
            25.0f,  // 5
            50.0f,  // 6
            100.0f, // 7
        };
        inline static u32 MoveIndex = 2;
        inline static f32 Move() { return MovePresets[MoveIndex]; }
        
        inline static std::array<f32, 9> RotatePresets = {
            0.5f,  // 0
            1.0f,  // 1
            2.5f,  // 2
            5.0f,  // 3
            10.0f, // 4
            15.0f, // 5
            45.0f, // 6
            90.0f, // 7
            180.0f // 8
        };
        inline static u32 RotateIndex = 5;
        inline static f32 Rotate() { return RotatePresets[RotateIndex]; }
        
        inline static std::array<f32, 9> ScalePresets = {
            0.01f, // 0
            0.1f,  // 1
            0.25f, // 2
            0.5f,  // 3
            0.75f, // 4
            1.0f,  // 5
            5.0f,  // 6
            10.0f, // 7
            50.0f, // 8
        };
        inline static u32 ScaleIndex = 5;
        inline static f32 Scale() { return ScalePresets[ScaleIndex]; }
    };
    std::string currentDateTime() {
        time_t now = time(0);
        struct tm tstruct;
        c8 buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%d/%m/%Y | %X", &tstruct);
        return buf;
    }
};
extern AUR aur;
void Marker(cc8* text, c1 attention = false);
void tellme(const std::string& words, c1 flush = false);
template<typename T>
void showme(T);
void asBytes(std::ofstream &file, c32 value, c32 byte_size);
inline void setString(const std::string& sString, const size_t nItem = 0) {
    if (nItem >= aur.m_vContent.size()) aur.m_vContent.resize(nItem + 1);
    aur.m_vContent[nItem] = sString;
};
inline const std::string getString(const size_t nItem = 0) {
    if (nItem >= aur.m_vContent.size()) return "";
    else return aur.m_vContent[nItem];
};
// template<typename T>
// void aurWrite(std::ofstream& out, const T& variable) {
    // out.write(reinterpret_cast<cc8*>(&variable), sizeof(T));
    // std::cout << "save " << &variable << " - " << sizeof(T) << "\n";
// }
// template<typename T>
// void aurRead(std::istream& in, T& variable) {
    // in.read(reinterpret_cast<char*>(&variable), sizeof(T));
    // std::cout << "load " << &variable << " - " << sizeof(T) << "\n";
// }

// template<typename T>
// void aurWrite(std::ofstream& out, const T& variable) {
    // std::string savePath = std::string(path) + name + ".wav";
    // std::ofstream file(savePath, std::ios::binary);
    // out.write(reinterpret_cast<cc8*>(&variable), sizeof(T));
    // std::cout << "save " << &variable << " - " << sizeof(T) << "\n";
// }
// template<typename T>
// void aurRead(std::istream& in, T& variable) {
    // in.read(reinterpret_cast<char*>(&variable), sizeof(T));
    // std::cout << "load " << &variable << " - " << sizeof(T) << "\n";
// }
void urlButton(cc8* label, cc8* url);
void CreateDirectories();
// windows
void ViewportEditor(GLFWwindow* window, u32 texture);
void MaterialMaker();
void ObjectManipulator();

void SoundOrganizer();
void initAudio();
void uninitAudio();

void Settings();

void initGLFW();
void initOpenGL();
void framebuffer_size_callback(GLFWwindow* window, c32 width, c32 height);
void SwitchTheme (enum AUR::Theme theme);
void SaveEngine();
void LoadEngine();