#pragma once
#include "../config.h"

#include "../components/camera_component.h"
#include "../components/physics_component.h"
#include "../components/render_component.h"
#include "../components/transform_component.h"

#include "../systems/camera_system.h"
#include "../systems/motion_system.h"
#include "../systems/render_system.h"

#include "../view/shader.h"

class App {
public:
    // vars
    int screenW = 800;
    int screenH = 600;
    double scrollY = 0.0;
    glm::vec4 clearColor = {0.1f, 0.2f, 0.3f, 1.0f};
    
    App();
    ~App();
    void run();
    unsigned int make_entity();
    unsigned int make_cube_mesh(glm::vec3 size);
    unsigned int make_texture(const char* filename);
    void set_up_opengl();
    void make_systems();
    void update_projection();

    // components
    std::unordered_map<unsigned int, TransformComponent> transformComponents;
    std::unordered_map<unsigned int, PhysicsComponent> physicsComponents;
    CameraComponent* cameraComponent;
    unsigned int cameraID;
    std::unordered_map<unsigned int, RenderComponent> renderComponents;
    
private:
    void set_up_glfw();

    unsigned int entity_count = 0;
    GLFWwindow* window;

    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<unsigned int> textures;

    unsigned int shader;

    // systems
    MotionSystem* motionSystem;
    CameraSystem* cameraSystem;
    RenderSystem* renderSystem;
};