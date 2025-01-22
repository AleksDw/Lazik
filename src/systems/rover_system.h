#pragma once
#include "../config.h"
#include "../components/transform_component.h"
#include "../components/physics_component.h"
#include "../components/render_component.h"
#include "../components/hitBox_component.h"
#include "../components/TransformHitBox_component.h"

class RoverSystem
{
public:

    RoverSystem(GLFWwindow* window);

    void update(std::unordered_map<unsigned int,
        TransformComponent>& transformComponents,
        std::unordered_map<unsigned int,
        TransformHitBoxComponent>& transformComponentsHitbox,
        std::unordered_map<unsigned int,
        PhysicsComponent>& physicsComponents,
        std::unordered_map<unsigned int,
        HitBoxComponent>& hitBoxComponentHitbox, float dt, unsigned int controlledEntity);

    glm::vec3 calculateMTV(const HitBoxComponent& boxA, const HitBoxComponent& boxB, const TransformHitBoxComponent& transformA, const TransformHitBoxComponent& transformB);

private:
    GLFWwindow* window;
    std::unordered_map<unsigned int, TransformComponent> tempPositions;
};