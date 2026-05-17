#include "camera_system.h"
#include "engine.h"

CameraSystem::CameraSystem(unsigned int shader, GLFWwindow* window) {
    this->window = window;

    glUseProgram(shader);
    viewLocation = glGetUniformLocation(shader, "view");
}

bool CameraSystem::update(
    std::unordered_map<unsigned int,TransformComponent> &transformComponents,
    unsigned int cameraID, CameraComponent& cameraComponent, float dt, double scrollY) {

    glm::vec3& pos = transformComponents[cameraID].position;
    glm::vec3& eulers = transformComponents[cameraID].eulers;
    float theta = glm::radians(eulers.z);
    float phi = glm::radians(eulers.y);

    glm::vec3& right = cameraComponent.right;
    glm::vec3& up = cameraComponent.up;
    glm::vec3& forwards = cameraComponent.forwards;

    forwards = glm::normalize(glm::vec3(
        glm::cos(theta) * glm::cos(phi),
        glm::sin(theta) * glm::cos(phi),
        glm::sin(phi)
    ));
    right = glm::normalize(glm::cross(forwards, global_up));
    up = glm::normalize(glm::cross(right, forwards));
    
    glm::mat4 view = glm::lookAt(pos, pos + forwards, up);
    
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    
    //Keys
    glm::vec3 dPos{0.0f};
    float speedIncrement = 0.01f;
    // keep them ?
    // if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) speedIncrement = 0.1f;
    // if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) speedIncrement = 0.01f;
    moveSpeed = glm::clamp(moveSpeed + float(scrollY) * speedIncrement, 0.01f, 1.0f);
    
    if (!aur.askExit)
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) aur.askExit = true;
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) dPos.x += 1.0f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) dPos.y -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) dPos.x -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) dPos.y += 1.0f;
    
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) dPos.z += 1.0f;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) dPos.z -= 1.0f;
    
    if (glm::length(dPos) > 0.0f) {
        dPos = glm::normalize(dPos);
        pos += moveSpeed * dPos.x * forwards;
        pos += moveSpeed * dPos.y * right;
        pos += moveSpeed * dPos.z * up;}

    // say("X " + std::to_string(forwards.x) + " Y " + std::to_string(right.y) + " Z " + std::to_string(up.z), -1, true);

    // mouse
    static bool prevMove = false;
    bool move;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        move = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        move = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);};
    
    static double last_x = 0.0, last_y = 0.0;
    double mouse_x, mouse_y;
    
    if (move) {
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        
        if (!prevMove) {
            last_x = mouse_x;
            last_y = mouse_y;}
        
        float dx = float(mouse_x - last_x);
        float dy = float(mouse_y - last_y);

        last_x = mouse_x;
        last_y = mouse_y;

        eulers.z += -cameraSens * dx;
        eulers.y += -cameraSens * dy;

        eulers.y = fminf(89.9f, fmaxf(-89.9f, eulers.y));

        if (eulers.z > 360.0f) eulers.z -= 360.0f;
        else if (eulers.z < 0.0f) eulers.z += 360.0f;
    }
    prevMove = move;

    return false;
}