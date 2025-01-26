#include "rover_system.h"
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>
#include <cmath>
glm::vec3 position = { 0.0f, 0.0f, 0.0f };
float angle = 0.0f;
float speed = 0.0f;
float turnSpeed = 0.5f;
float wheelAngle = 0.0f;
float cd = 60;

glm::vec3 POD_PRAWE_KOLO_PRZOD;
glm::vec3 POD_PRAWE_KOLO_TYL;
glm::vec3 POD_LEWE_KOLO_PRZOD;
glm::vec3 POD_LEWE_KOLO_TYL;

float y_dostosuj_speed = 0;
const float spring = 0.3f;
const float acceleration = 2.0f;
const float deceleration = 5.0f;
const float MPI = 3.14159265359;
int const PRAWE_KOLO_PRZOD = 1;
int const PRAWE_KOLO_TYL = 2;
int const LEWE_KOLO_PRZOD = 3;
int const LEWE_KOLO_TYL = 4;
const float MAX_SPEED = 5.0f;
const float MAX_WHEEL_ANGLE = 30.0f;
bool bullet_list[5] = { false };
float bullet_speed = 5.0f;

RoverSystem::RoverSystem(GLFWwindow* window) {
    this->window = window;
    tempPositions = {};
}

void RoverSystem::update(
    std::unordered_map<unsigned int, TransformComponent>& transformComponents,
    std::unordered_map<unsigned int, TransformHitBoxComponent>& transformComponentsHitbox,
    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
    std::unordered_map<unsigned int, HitBoxComponent>& hitBoxComponent,
    std::unordered_map<unsigned int, HitBoxComponentTerrain>& renderComponentsHitboxTerrain,
    float dt, unsigned int controlledEntity)
{
    for (int i = 0; i <= controlledEntity; i++) {
        tempPositions[i] = transformComponents[i];
    }

    // sterowanie
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        speed += acceleration * dt;
        if (speed > MAX_SPEED) speed = MAX_SPEED;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        speed -= acceleration * dt;
        if (speed < -MAX_SPEED) speed = -MAX_SPEED;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        wheelAngle++;
        if (wheelAngle > MAX_WHEEL_ANGLE) wheelAngle = MAX_WHEEL_ANGLE;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        wheelAngle--;
        if (wheelAngle < -MAX_WHEEL_ANGLE) wheelAngle = -MAX_WHEEL_ANGLE;
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && cd >= 60) {
        for (int i = 0; i <= 5; i++) {
            if (!bullet_list[i]) {
                bullet_list[i] = true;
                transformComponents[controlledEntity + i + 1].position.x = transformComponents[controlledEntity].position.x;
                transformComponents[controlledEntity + i + 1].position.y = transformComponents[controlledEntity].position.y;
                transformComponents[controlledEntity + i + 1].position.z = transformComponents[controlledEntity].position.z;
                transformComponents[controlledEntity + i + 1].eulers.x = transformComponents[controlledEntity].eulers.x;
                transformComponents[controlledEntity + i + 1].eulers.z = transformComponents[controlledEntity].eulers.z;
                glm::vec2 direction = glm::rotate(glm::vec2(1.0f, 0.0f), angle);
                physicsComponents[controlledEntity + i + 1].velocity = glm::vec3(direction.x, direction.y, 0.0f) * bullet_speed + glm::vec3(direction.x, direction.y, 0.0f) * speed;
                physicsComponents[controlledEntity + i + 1].velocity.z = 2;
                cd = 0;
                break;
            }
        }
    }
    if (cd < 120) {
        cd++;
    }
    for (int i = 0; i <= 5; i++) {
        if (bullet_list[i]) {
            transformComponents[controlledEntity + i + 1].position += physicsComponents[controlledEntity + i + 1].velocity * dt;
            physicsComponents[controlledEntity + i + 1].velocity.z -= 0.01;
        }
    }

	// jezeli nie wcisnieto lub wcisnieto lewego i prawego to kat kola powinien malec
    if ((glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS) || 
        glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (wheelAngle > 0)
            wheelAngle--;
        else if (wheelAngle < 0)
            wheelAngle++;
    }

	// jezeli nie wcisnieto lub wcisnieto gory i dolu to predkosc powinna malec
    if ((glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS) ||
        glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (speed > 0.0f) {
            speed = speed * 0.99;
            if (speed < 0.0f) speed = 0.0f;
        }
        else if (speed < 0.0f) {
            speed = speed * 0.99;
            if (speed > 0.0f) speed = 0.0f;
        }
    }

    // obliczanie zmiany kata obrotu lazika
    if (speed > turnSpeed)
    {
        angle += (dt * wheelAngle * turnSpeed) / 30;
    }
    else if (abs(speed) > turnSpeed)
    {
        angle += (dt * wheelAngle * -turnSpeed) / 30;
    }
    else
    {
        angle += (dt * wheelAngle * speed) / 30;
    }

    angle = fmod(angle, 2.0f * MPI);
    if (angle < 0) {
        angle += 2.0f * MPI;
    }

    glm::vec2 direction = glm::rotate(glm::vec2(1.0f, 0.0f), angle);
    for (int i = 0; i <= controlledEntity; i++) {
        if (i > 0) {
            glm::vec3 localOffset;
            switch (i) {
            case PRAWE_KOLO_PRZOD:
                localOffset = glm::vec3(1.25f, -0.64958f, -0.686f);
                break;
            case PRAWE_KOLO_TYL:
                localOffset = glm::vec3(-1.25f, -0.64958f, -0.686f);
                break;
            case LEWE_KOLO_PRZOD:
                localOffset = glm::vec3(1.25f, 0.64958f, -0.686f);
                break;
            case LEWE_KOLO_TYL:
                localOffset = glm::vec3(-1.25f, 0.64958f, -0.686f);
                break;
            default:
                localOffset = glm::vec3(0.0f, 0.0f, 0.0f);
                break;
            }
            glm::vec3 rotatedOffsetZ = glm::rotateZ(localOffset, glm::radians(tempPositions[0].eulers.z));
            tempPositions[i].position = tempPositions[0].position + rotatedOffsetZ;
            physicsComponents[i].velocity = physicsComponents[0].velocity;

            //glm::vec3 rotatedOffsetY = glm::rotateY(localOffset, glm::radians(tempPositions[0].eulers.y));
            //tempPositions[i].position = tempPositions[0].position + rotatedOffsetY;

            //glm::vec3 rotatedOffsetX = glm::rotateX(localOffset, glm::radians(tempPositions[0].eulers.x));
            //tempPositions[i].position = tempPositions[0].position + rotatedOffsetX;

            tempPositions[i].eulers.y += speed;
			if (tempPositions[i].eulers.y > 360.0f) tempPositions[i].eulers.y -= 360.0f;
        }
        else {
            physicsComponents[i].velocity = glm::vec3(direction.x, direction.y, 0.0f) * speed;
        }
        if(i == PRAWE_KOLO_PRZOD || i == LEWE_KOLO_PRZOD)
            tempPositions[i].eulers.z = angle * (180.0f / MPI) + wheelAngle;
        else {
            tempPositions[i].eulers.z = angle * (180.0f / MPI);
            transformComponentsHitbox[0].eulers.z = angle * (180.0f / MPI);
            transformComponentsHitbox[0].position = tempPositions[0].position;
        }
        tempPositions[i].position += physicsComponents[i].velocity * dt;
        tempPositions[i].eulers += physicsComponents[i].eulerVelocity * dt;
        if (transformComponents[i].eulers.z > 360)
        {
            transformComponents[i].eulers.z -= 360;
        }
    }
    
    for (const auto& [key, hitbox] : hitBoxComponent) {
        if (key > controlledEntity) {
            glm::vec3 mtv = calculateMTV(
                hitBoxComponent[0], hitbox,
                transformComponentsHitbox[0], transformComponentsHitbox[key]
            );

            // jesli mtv nie jest zerowy to znaczy ze doszlo do kolizji
            if (glm::length(mtv) > 0.0f) {
                std::cout << "collision detected\n";

                //lekkie odbicie
				speed *= -0.2f;

                // odpowiedź na kolizje, przesuniecie obiektu o mtv (powoduje sliding)
                for (int i = 0; i <= controlledEntity; i++) {
                    tempPositions[i].position += mtv;
                }

            }
        }
    }

    for (int i = 0; i <= controlledEntity; i++) {
        transformComponents[i] = tempPositions[i];

    }

    std::array<glm::vec2, 4> points = {
    glm::vec2(transformComponents[PRAWE_KOLO_PRZOD].position.x, transformComponents[PRAWE_KOLO_PRZOD].position.y),
    glm::vec2(transformComponents[LEWE_KOLO_PRZOD].position.x, transformComponents[LEWE_KOLO_PRZOD].position.y),
    glm::vec2(transformComponents[PRAWE_KOLO_TYL].position.x,transformComponents[PRAWE_KOLO_TYL].position.y),
    glm::vec2(transformComponents[LEWE_KOLO_TYL].position.x, transformComponents[LEWE_KOLO_TYL].position.y)
    };

    try
    {
        std::vector<float> z = getTerrainHeights(renderComponentsHitboxTerrain[0], points);
        float position_after_PRAWE_KOLO_PRZOD = z[0] + 0.5f;
        float position_after_LEWE_KOLO_PRZOD = z[1] + 0.5f;
        float position_after_PRAWE_KOLO_TYL = z[2] + 0.5f;
        float position_after_LEWE_KOLO_TYL = z[3] + 0.5f;

        double krotsze_PRAWE_KOLO_PRZOD = atan((transformComponents[PRAWE_KOLO_PRZOD].position.z - position_after_PRAWE_KOLO_PRZOD + 0.5f) / 1.65715);
        double dluzsze_PRAWE_KOLO_PRZOD = atan((transformComponents[PRAWE_KOLO_PRZOD].position.z - position_after_PRAWE_KOLO_PRZOD + 0.5f)/ 2.65415);

        double krotsze_LEWE_KOLO_PRZOD = atan((transformComponents[LEWE_KOLO_PRZOD].position.z - position_after_LEWE_KOLO_PRZOD + 0.5f) / 1.65715);
        double dluzsze_LEWE_KOLO_PRZOD = atan((transformComponents[LEWE_KOLO_PRZOD].position.z - position_after_LEWE_KOLO_PRZOD + 0.5f) / 2.65415);

        double krotsze_PRAWE_KOLO_TYL = atan((transformComponents[PRAWE_KOLO_TYL].position.z - position_after_PRAWE_KOLO_TYL + 0.5f) / 1.65715);
        double dluzsze_PRAWE_KOLO_TYL = atan((transformComponents[PRAWE_KOLO_TYL].position.z - position_after_PRAWE_KOLO_TYL + 0.5f) / 2.65415);

        double krotsze_LEWE_KOLO_TYL = atan((transformComponents[LEWE_KOLO_TYL].position.z - position_after_LEWE_KOLO_TYL + 0.5f) / 1.65715);
        double dluzsze_LEWE_KOLO_TYL = atan((transformComponents[LEWE_KOLO_TYL].position.z - position_after_LEWE_KOLO_TYL + 0.5f) / 2.65415);
        
        transformComponents[0].position.z = 0.64958f + position_after_PRAWE_KOLO_PRZOD - (position_after_PRAWE_KOLO_PRZOD - position_after_LEWE_KOLO_TYL) / 2;

        transformComponents[0].eulers.y = 17 * (krotsze_PRAWE_KOLO_PRZOD + krotsze_LEWE_KOLO_PRZOD - krotsze_PRAWE_KOLO_TYL - krotsze_LEWE_KOLO_TYL);
        transformComponents[0].eulers.x = 17 * (dluzsze_PRAWE_KOLO_PRZOD - dluzsze_LEWE_KOLO_PRZOD + dluzsze_PRAWE_KOLO_TYL - dluzsze_LEWE_KOLO_TYL);

        for (int i = 0; i <= controlledEntity; i++) {
            if (i > 0) {
                glm::vec3 localOffset;
                switch (i) {
                case PRAWE_KOLO_PRZOD:
                    localOffset = glm::vec3(1.25f, -0.64958f, -0.686f);
                    break;
                case PRAWE_KOLO_TYL:
                    localOffset = glm::vec3(-1.25f, -0.64958f, -0.686f);
                    break;
                case LEWE_KOLO_PRZOD:
                    localOffset = glm::vec3(1.25f, 0.64958f, -0.686f);
                    break;
                case LEWE_KOLO_TYL:
                    localOffset = glm::vec3(-1.25f, 0.64958f, -0.686f);
                    break;
                default:
                    localOffset = glm::vec3(0.0f, 0.0f, 0.0f);
                    break;
                }
                glm::vec3 rotationRadians = glm::radians(transformComponents[0].eulers);
                glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationRadians.z, glm::vec3(0.0f, 0.0f, 1.0f))
                    * glm::rotate(glm::mat4(1.0f), rotationRadians.y, glm::vec3(0.0f, 1.0f, 0.0f))
                    * glm::rotate(glm::mat4(1.0f), rotationRadians.x, glm::vec3(1.0f, 0.0f, 0.0f));

                glm::vec4 rotatedOffset = rotationMatrix * glm::vec4(localOffset, 1.0f);
                transformComponents[i].position = transformComponents[0].position + glm::vec3(rotatedOffset);
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        speed *= 0.95f;
        if (std::abs(speed) < 0.1f) speed = 0.0f;
    }
}

// oblicza minimalny wektor przesuniecia(minimal transform vector) dla hitboxa boxA, aby nie kolidowal z boxB
glm::vec3 RoverSystem::calculateMTV(
    const HitBoxComponent& boxA, const HitBoxComponent& boxB,
    const TransformHitBoxComponent& transformA, const TransformHitBoxComponent& transformB) {

    glm::vec3 smallestOverlapAxis(0.0f);
    float smallestOverlap = std::numeric_limits<float>::max();

    // Compute rotation matrices for both hitboxes
    glm::mat4 rotationMatrixA = glm::mat4(1.0f);
    rotationMatrixA = glm::rotate(rotationMatrixA, glm::radians(transformA.eulers.x), glm::vec3(1, 0, 0));
    rotationMatrixA = glm::rotate(rotationMatrixA, glm::radians(transformA.eulers.y), glm::vec3(0, 1, 0));
    rotationMatrixA = glm::rotate(rotationMatrixA, glm::radians(transformA.eulers.z), glm::vec3(0, 0, 1));

    glm::mat4 rotationMatrixB = glm::mat4(1.0f);
    rotationMatrixB = glm::rotate(rotationMatrixB, glm::radians(transformB.eulers.x), glm::vec3(1, 0, 0));
    rotationMatrixB = glm::rotate(rotationMatrixB, glm::radians(transformB.eulers.y), glm::vec3(0, 1, 0));
    rotationMatrixB = glm::rotate(rotationMatrixB, glm::radians(transformB.eulers.z), glm::vec3(0, 0, 1));

    // Axes to test for collision
    std::vector<glm::vec3> axes = {
        glm::vec3(1.0f, 0.0f, 0.0f), // X-axis
        glm::vec3(0.0f, 1.0f, 0.0f), // Y-axis
        glm::vec3(0.0f, 0.0f, 1.0f)  // Z-axis
    };

    for (const auto& axis : axes) {
        glm::vec3 normalizedAxis = glm::normalize(axis);

        // Compute min/max projections for boxA
        float minA = std::numeric_limits<float>::max();
        float maxA = std::numeric_limits<float>::lowest();
        for (size_t i = 0; i < boxA.vertexCount; ++i) {
            // Transform vertex using rotation matrix
            glm::vec4 rotatedVertexA = rotationMatrixA * glm::vec4(boxA.vertices[i], 1.0f);
            glm::vec3 worldVertexA = transformA.position + glm::vec3(rotatedVertexA);

            // Project onto the axis
            float projection = glm::dot(worldVertexA, normalizedAxis);
            minA = std::min(minA, projection);
            maxA = std::max(maxA, projection);
        }

        // Compute min/max projections for boxB
        float minB = std::numeric_limits<float>::max();
        float maxB = std::numeric_limits<float>::lowest();
        for (size_t i = 0; i < boxB.vertexCount; ++i) {
            // Transform vertex using rotation matrix
            glm::vec4 rotatedVertexB = rotationMatrixB * glm::vec4(boxB.vertices[i], 1.0f);
            glm::vec3 worldVertexB = transformB.position + glm::vec3(rotatedVertexB);

            // Project onto the axis
            float projection = glm::dot(worldVertexB, normalizedAxis);
            minB = std::min(minB, projection);
            maxB = std::max(maxB, projection);
        }

        // Check for overlap on this axis
        float overlap = std::min(maxA, maxB) - std::max(minA, minB);
        if (overlap < 0) {
            // No collision
            return glm::vec3(0.0f);
        }

        // Track smallest overlap
        if (overlap < smallestOverlap) {
            smallestOverlap = overlap;
            smallestOverlapAxis = normalizedAxis * ((minA < minB) ? -1.0f : 1.0f);
        }
    }

    return smallestOverlapAxis * smallestOverlap;
}

std::vector<float> RoverSystem::getTerrainHeights(const HitBoxComponentTerrain& terrain,
    const std::array<glm::vec2, 4>& points) {

    std::vector<float> heights;
    heights.reserve(points.size());

    // Iterate through each point
    for (const auto& p : points) {
        bool found = false;

        for (const auto& triangle : terrain.triangles) {
            // Extract triangle vertices
            const glm::vec3& v0 = triangle[0];
            const glm::vec3& v1 = triangle[1];
            const glm::vec3& v2 = triangle[2];

            // Project triangle to 2D once
            glm::vec2 A(v0.x, v0.y);
            glm::vec2 B(v1.x, v1.y);
            glm::vec2 C(v2.x, v2.y);

            // Check if the point is inside this triangle
            if (pointInTriangle2D(p, A, B, C)) {
                // Calculate normal vector for the triangle plane
                glm::vec3 edge1 = v1 - v0;
                glm::vec3 edge2 = v2 - v0;
                glm::vec3 normal = glm::cross(edge1, edge2);

                // Calculate plane equation: Ax + By + Cz + D = 0
                float A = normal.x;
                float B = normal.y;
                float C = normal.z;
                float D = -glm::dot(normal, v0);

                // Compute height (z) for the given point (x, y)
                if (C != 0.0f) {
                    float z = -(A * p.x + B * p.y + D) / C;
                    heights.push_back(z);
                    found = true;
                    break; // Move to the next point
                }
            }
        }

        if (!found) {
            throw std::runtime_error(
                "getTerrainHeights: Point (" + std::to_string(p.x) + ", " + std::to_string(p.y) +
                ") is outside of terrain");
        }
    }

    return heights;
}

bool RoverSystem::pointInTriangle2D(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c) {
    // Helper lambda for 2D cross product
    auto cross = [](const glm::vec2& u, const glm::vec2& v) {
        return u.x * v.y - u.y * v.x;
        };

    // Precompute edges
    glm::vec2 ab = b - a;
    glm::vec2 bc = c - b;
    glm::vec2 ca = a - c;

    // Compute vectors from point to triangle vertices
    glm::vec2 ap = p - a;
    glm::vec2 bp = p - b;
    glm::vec2 cp = p - c;

    // Compute cross products to determine the point's location
    float cross1 = cross(ab, ap);
    float cross2 = cross(bc, bp);
    float cross3 = cross(ca, cp);

    // Check if all cross products have the same sign
    return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0);
}
