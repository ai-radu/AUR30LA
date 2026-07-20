#pragma once
#include "aur.hpp"

class Render {
public:
    Render(unsigned int shader, GLFWwindow* window);
    void update(
        std::unordered_map<unsigned int, TransformComponent> &transformComponents,
        std::unordered_map<unsigned int, RenderComponent> &renderComponents);
private:
    unsigned int modelLocation;
    GLFWwindow* window;
};