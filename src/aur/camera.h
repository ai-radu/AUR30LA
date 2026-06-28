#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "aur.h"
#include "view/shader.h"
#include "components.h"
struct CAMERA {
    bool move = false;
    bool firstClick = true;
    float fov = 45.0f;
    glm::vec3 location;
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float sensitivity = 80.0f;
    float speed = 0.1f;
    struct Component {
        vec3 right;
        vec3 up;
        vec3 forward;
    };
};
extern CAMERA camera;

void Camera(int width, int height, glm::vec3 fLocation);
void Matrix(float fov, float near, float far, Shader& shader, const char* uniform);
void Inputs(GLFWwindow* window);