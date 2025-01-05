#include "motion_system.h"

void MotionSystem::update(
    std::unordered_map<unsigned int,TransformComponent> &transformComponents,
    std::unordered_map<unsigned int,PhysicsComponent> &physicsComponents,
    float dt) 
{
    for (auto& [entity, velocity] : physicsComponents) 
    {

    }
}