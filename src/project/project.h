#pragma once
#include "aur.h"
#include <filesystem>
#include <nlohmann/json.hpp>

struct PROJECT {
    std::string saveData = "../save/project.json";
    std::string name = "NewProject.aur";
};
extern PROJECT project;

void saveProject();
void loadProject();