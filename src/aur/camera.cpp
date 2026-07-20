#include "camera.hpp"
CAMERA camera;

void Camera(c32 width, c32 height, glm::vec3 fLocation) {
    aur.viewportWidth = width;
    aur.viewportHeight = height;
    camera.location = fLocation;
}
void Matrix(f32 fov, f32 near, f32 far, Shader& shader, cc8* uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 perspective = glm::mat4(1.0f);
    
    view = glm::lookAt(camera.location, camera.location + camera.rotation, camera.up);
    perspective = glm::perspective(glm::radians(fov), (f32)aur.viewportWidth / (f32)aur.viewportHeight, near, far);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(perspective * view));
}