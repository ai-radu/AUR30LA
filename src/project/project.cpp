#include "project.h"
PROJECT project;

void saveProject() {
    nlohmann::json projectData;
    // vars
    projectData["name"] = project.name;
    
    std::ofstream file(project.saveData);
    if (!file.is_open()) { say("[WARNING] project.cpp > saveProjectData() ? !file.is_open"); return; }
    file << projectData.dump(4);
    file.close();
    say("[NOTIF] project.cpp > saveProjectData()");
}
void loadProject() {
    std::ifstream file(project.saveData);
    if (!file.is_open()) { say("[WARNING] project.cpp > loadProjectData() ? !file.is_open"); return; }
    nlohmann::json projectData;
    file >> projectData;
    // vars
    project.name = projectData["name"];

    say("[NOTIF] project.cpp > loadProjectData()");
}