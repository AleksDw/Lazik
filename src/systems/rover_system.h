#pragma once
#include "../config.h"
#include "../components/transform_component.h"
#include "../components/physics_component.h"

class RoverSystem
{
public:

    RoverSystem(GLFWwindow* window);

    void update(std::unordered_map<unsigned int, TransformComponent>& transformComponents, std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents, float dt, unsigned int controlledEntity);

    void update(
        std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents, float dt, unsigned int controlledEntity);

private:
    GLFWwindow* window;
};