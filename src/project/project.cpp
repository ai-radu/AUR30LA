#include "project.hpp"
PROJECT project;

void SaveProject() {
    // nlohmann::json projectData;
    // vars
    // projectData["name"] = project.name;
    
    // std::ofstream file(project.saveData);
    // if (!file.is_open()) { tellme("[WARNING] project.cpp > saveProject() ? !file.is_open"); return; }
    // file << projectData.dump(4);
    // file.close();
    // if (AUR::Editor::terminalNOTIF) tellme("[NOTIF] project.cpp > saveProject()");
}
void LoadProject() {
    // std::ifstream file(project.saveData);
    // if (!file.is_open()) { tellme("[WARNING] project.cpp > loadProject() ? !file.is_open"); return; }
    // nlohmann::json projectData;
    // file >> projectData;
    // vars
    // project.name = projectData["name"];
    
    // if (AUR::Editor::terminalNOTIF) tellme("[NOTIF] project.cpp > loadProject()");
}