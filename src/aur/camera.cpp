#include "camera.h"
CAMERA camera;

void Camera(int width, int height, glm::vec3 fLocation) {
    aur.viewportWidth = width;
    aur.viewportHeight = height;
    camera.location = fLocation;
}
void Matrix(float fov, float near, float far, Shader& shader, const char* uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 perspective = glm::mat4(1.0f);
    
    view = glm::lookAt(camera.location, camera.location + camera.rotation, camera.up);
    perspective = glm::perspective(glm::radians(fov), (float)aur.viewportWidth / (float)aur.viewportHeight, near, far);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(perspective * view));
}
void Inputs(GLFWwindow* window) {
    if (camera.move) {
        // forward
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.location += camera.speed * camera.rotation;
        };
        // left
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.location += camera.speed * -glm::normalize(glm::cross(camera.rotation, camera.up));
        };
        // backwards
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.location += camera.speed * -camera.rotation;
        };
        // right
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera.location += camera.speed * glm::normalize(glm::cross(camera.rotation, camera.up));
        };
        // up
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            camera.location += camera.speed * camera.up;
        };
        // down
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            camera.location += camera.speed * -camera.up;
        };
    }
    // mouse
    double mouseX, mouseY;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera.move = true;
        if (camera.firstClick) {
            glfwSetCursorPos(window, (aur.windowWidth / 2), (aur.windowHeight / 2));
            camera.firstClick = false;
        }
        glfwGetCursorPos(window, &mouseX, &mouseY);
        
        float rotx = camera.sensitivity * (float)(mouseY - (aur.windowHeight / 2)) / aur.windowHeight;
        float roty = camera.sensitivity * (float)(mouseX - (aur.windowWidth  / 2)) / aur.windowWidth;

        glm::vec3 newRotation = glm::rotate(
            camera.rotation,
            glm::radians(-rotx),
            glm::normalize(glm::cross(camera.rotation, camera.up))
        );
        if (!((glm::angle(newRotation, camera.up) <= glm::radians(5.0f)) 
        or (glm::angle(newRotation, -camera.up) <= glm::radians(5.0f)))) {
            camera.rotation = newRotation;
        }
        camera.rotation = glm::rotate(camera.rotation, glm::radians(-roty), camera.up);
        
        glfwSetCursorPos(window, (aur.windowWidth / 2), (aur.windowHeight / 2));
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        camera.move = false;
        camera.firstClick = true;
    }
}