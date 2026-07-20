#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "aur.hpp"
#include "view/shader.hpp"
#include "components.hpp"
struct CAMERA {
    inline static c1 move = false;
    inline static c1 firstClick = true;
    inline static f32 fov = 45.0f;
    inline static glm::vec3 location;
    inline static glm::vec3 rotation = glm::vec3(0.0f, 0.0f, -1.0f);
    inline static glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    inline static f32 sensitivity = 80.0f;
    inline static f32 speed = 1000.0f;
    struct Component {
        v3 right;
        v3 up;
        v3 forward;
    };
};
extern CAMERA camera;

void Camera(c32 width, c32 height, glm::vec3 fLocation);
void Matrix(f32 fov, f32 near, f32 far, Shader& shader, const c8* uniform);