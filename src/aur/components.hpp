#pragma once
#include "variables.hpp"

struct RenderComponent {
    u32 material;
    u32 mesh;
};
struct TransformComponent {
    v3 position;
    v3 eulers;
};
struct PhysicsComponent {
    v3 velocity;
    v3 eulerVelocity;
};
struct CameraComponent {
    v3 right;
    v3 up;
    v3 forward;
};