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
#include "view/texture.h"
#include "view/shader.h"
#include "view/VAO.h"
#include "view/VBO.h"
#include "view/EBO.h"
#include "camera.h"
#include "components.h"
struct AUR {
    std::string saveData = "../save/aur.json";
    
    std::vector<std::string> m_vContent;
    struct Engine {
        inline static float    mouseCursorScale       = 1.0f;
        inline static float    mouseDoubleClickTime   = 0.30f;
        inline static float    keyRepeatDelay         = 0.275f;
        inline static float    keyRepeatRate          = 0.050f;
        inline static int      tooltipOffset          = 0;
        inline static float    hoverDelay             = 0.15f;
        inline static float    colorMarkerSize        = 3.0f;
        inline static Var::Dir colorButtonPosition    = Var::Dir::Right;
        inline static vec2     buttonTextAlign        = vec2(0.5f, 0.5f);
        inline static bool     antiAliasedLines       = false;
        inline static bool     antiAliasedLinesUseTex = true;
        inline static bool     antiAliasedFill        = true;
    };
    struct Editor {
        inline static bool viewportPanelLocation = false; // left
    };
    inline static std::string wow = "woiw";
    
    GLFWwindow* window;
    int windowWidth  = 1240;
    int windowHeight = 720;
    int viewportWidth, viewportHeight;
    vec2 viewportPosition;
    unsigned int frameBuffer, framebufferTexture, renderBuffer;
    float currentFrame, lastFrame, deltaTime;
    vec4 backgroundColor = {0.4f, 0.5f, 0.6f, 1.0f};
    bool autoSave = true;
    bool autoLoad = true;
    struct Snap {
        static inline std::vector<float> MovePresets = {
            0.1f,   // 0
            0.5f,   // 1
            1.0f,   // 2
            5.0f,   // 3
            10.0f,  // 4
            25.0f,  // 5
            50.0f,  // 6
            100.0f, // 7
        };
        static inline std::vector<float> RotatePresets = {
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
        static inline std::vector<float> ScalePresets = {
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
        static inline int MoveIndex = 2;
        static inline int RotateIndex = 5;
        static inline int ScaleIndex = 5;
        static float Move()   {return MovePresets[MoveIndex];}
        static float Rotate() {return RotatePresets[RotateIndex];}
        static float Scale()  {return ScalePresets[ScaleIndex];}
    };
    enum Theme {
        Dark,
        Light,
        Classic
    };
    Theme currentTheme = Dark;
    std::string currentDateTime() {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%d/%m/%Y | %X", &tstruct);
        return buf;
    }
};
extern AUR aur;


void say(const std::string& words, bool flush = false);
void asBytes(std::ofstream &file, int value, int byte_size);

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
    // out.write(reinterpret_cast<const char*>(&variable), sizeof(T));
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
    // out.write(reinterpret_cast<const char*>(&variable), sizeof(T));
    // std::cout << "save " << &variable << " - " << sizeof(T) << "\n";
// }
// template<typename T>
// void aurRead(std::istream& in, T& variable) {
    // in.read(reinterpret_cast<char*>(&variable), sizeof(T));
    // std::cout << "load " << &variable << " - " << sizeof(T) << "\n";
// }

void urlButton(const char* label, const char* url);
void createDirectories();

// windows
void viewportEditor(unsigned int texture);
void materialMaker();
void objectManipulator();
void soundOrganizer();
void projectSettings();
void engineSettings();
void industrialSettings();
// panels
void materialPanel();
void objectPanel();
void soundPanel();
void projectPanel();
void enginePanel();
void industrialPanel();

void initGLFW();
void initOpenGL();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void switchTheme (enum AUR::Theme theme);
void saveEngine();
void loadEngine();