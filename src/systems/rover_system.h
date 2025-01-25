#pragma once
#include "../config.h"
#include "../components/transform_component.h"
#include "../components/physics_component.h"
#include "../components/render_component.h"
#include "../components/hitBox_component.h"
#include "../components/hitBoxTerrain_component.h"
#include "../components/TransformHitBox_component.h"

class RoverSystem
{
public:

    RoverSystem(GLFWwindow* window);

    void update(std::unordered_map<unsigned int, TransformComponent>& transformComponents, std::unordered_map<unsigned int, TransformHitBoxComponent>& transformComponentsHitbox, std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents, std::unordered_map<unsigned int, HitBoxComponent>& hitBoxComponent, std::unordered_map<unsigned int, HitBoxComponentTerrain>& renderComponentsHitboxTerrain, float dt, unsigned int controlledEntity);

    int isPointInsideCube(const glm::vec3& point, const std::vector<glm::vec3>& vertices, const glm::vec3& positionRover, const glm::vec3& positionPoint, const glm::vec3& eulersRover);

    std::vector<float> getTerrainHeights(const HitBoxComponentTerrain& terrain, const std::array<glm::vec2, 4>& points);

    bool pointInTriangle2D(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);


private:
    GLFWwindow* window;
    std::unordered_map<unsigned int, TransformComponent> tempPositions;
};