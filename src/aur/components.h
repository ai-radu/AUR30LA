#pragma once
#include "variables.h"

struct RenderComponent {
    unsigned int material;
    unsigned int mesh;
};
struct TransformComponent {
    vec3 position;
    vec3 eulers;
};
struct PhysicsComponent {
    vec3 velocity;
    vec3 eulerVelocity;
};
struct CameraComponent {
    vec3 right;
    vec3 up;
    vec3 forward;
};