#pragma once
#include "aur.hpp"
#include <filesystem>
#include <nlohmann/json.hpp>

struct PROJECT {
    // char saveData[512] = "../save/project.json";
    // char name[256] = "NewProject";
    struct Graphics {
        inline static c32 Presets            = 2;
        inline static c32 ViewDistance       = 2;
        inline static c32 AntiAliasing       = 2;
        inline static c32 PostProcessing     = 2;
        inline static c32 Shadows            = 2;
        inline static c32 GlobalIllumination = 2;
        inline static c32 Reflections        = 2;
        inline static c32 Textures           = 2;
        inline static c32 Effects            = 2;
        inline static c32 Foliage            = 2;
        inline static c32 Shading            = 2;
        inline static c32 Landscape          = 2;
    };
};
extern PROJECT project;

void SaveProject();
void LoadProject();