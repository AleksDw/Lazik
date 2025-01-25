#include "rover_system.h"
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

glm::vec3 position = { 0.0f, 0.0f, 0.0f };
float angle = 0.0f;
float speed = 0.0f;
float turnSpeed = 0.5f;
float wheelAngle = 0.0f;
bool jebna = false;
float cd = 60;

glm::vec3 POD_PRAWE_KOLO_PRZOD;
glm::vec3 POD_PRAWE_KOLO_TYL;
glm::vec3 POD_LEWE_KOLO_PRZOD;
glm::vec3 POD_LEWE_KOLO_TYL;

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
        if(!jebna)
        angle += (dt * wheelAngle * turnSpeed)/30;
    }
    else
	{
        if (!jebna)
        angle += (dt * wheelAngle * speed)/30;
	}
    if(!jebna)
        angle = fmod(angle, 2.0f * MPI);
        if (angle < 0) {
            angle += 2.0f * MPI;
        }
    jebna = false;
    glm::vec2 direction = glm::rotate(glm::vec2(1.0f, 0.0f), angle);
    for (int i = 0; i <= controlledEntity; i++) {
        if (i > 0) {
            glm::vec3 localOffset;
            switch (i) {
            case PRAWE_KOLO_PRZOD:
                localOffset = glm::vec3(1.85486f, -0.64958f, -0.686f);
                break;
            case PRAWE_KOLO_TYL:
                localOffset = glm::vec3(-0.65486f, -0.64958f, -0.686f);
                break;
            case LEWE_KOLO_PRZOD:
                localOffset = glm::vec3(1.85486f, 0.64958f, -0.686f);
                break;
            case LEWE_KOLO_TYL:
                localOffset = glm::vec3(-0.65486f, 0.64958f, -0.686f);
                break;
            default:
                localOffset = glm::vec3(0.0f, 0.0f, 0.0f);
                break;
            }
            glm::vec3 rotatedOffset = glm::rotateZ(localOffset, glm::radians(tempPositions[0].eulers.z));
            tempPositions[i].position = tempPositions[0].position + rotatedOffset;
            physicsComponents[i].velocity = physicsComponents[0].velocity;

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
        for (const auto& vertex : hitbox.vertices) {
            if (isPointInsideCube(vertex,hitBoxComponent[0].vertices, transformComponentsHitbox[0].position, transformComponentsHitbox[key].position, transformComponentsHitbox[0].eulers) != 0) {
                jebna = true;
            }
        }
        }
    }

    if (jebna) {
        for (int i = 0; i <= controlledEntity; i++) {
            physicsComponents[i].velocity = {0,0,0};
        }
        transformComponentsHitbox[0].eulers.z = angle * (180.0f / MPI);
        transformComponentsHitbox[0].position = transformComponents[0].position;
        //speed = speed * 0.7;
    }
    else {
        for (int i = 0; i <= controlledEntity; i++) {
        transformComponents[i] = tempPositions[i];
        }
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
        transformComponents[PRAWE_KOLO_PRZOD].position.z = z[0] + 0.5;
        transformComponents[LEWE_KOLO_PRZOD].position.z = z[1] + 0.5;
        transformComponents[PRAWE_KOLO_TYL].position.z = z[2] + 0.5;
        transformComponents[LEWE_KOLO_TYL].position.z = z[3] + 0.5;
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

int RoverSystem::isPointInsideCube(const glm::vec3& point, const std::vector<glm::vec3>& vertices, const glm::vec3& positionRover, const glm::vec3& positionPoint, const glm::vec3& eulersRover) {


    // Create the rotation matrix for the cuboid's orientation
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(eulersRover.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(eulersRover.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(eulersRover.z), glm::vec3(0, 0, 1));

    // Transform each vertex of the cuboid based on its rotation and rover position
    std::vector<glm::vec3> transformedVertices;
    for (const auto& vertex : vertices) {
        glm::vec4 transformedVertex = rotationMatrix * glm::vec4(vertex, 1.0f);
        transformedVertices.push_back(glm::vec3(transformedVertex) + positionRover);
    }

    // Calculate the bounds of the cuboid (min and max for each axis)
    glm::vec3 min, max;

    min.x = std::min({ transformedVertices[0].x, transformedVertices[1].x, transformedVertices[2].x, transformedVertices[3].x,
                       transformedVertices[4].x, transformedVertices[5].x, transformedVertices[6].x, transformedVertices[7].x });
    max.x = std::max({ transformedVertices[0].x, transformedVertices[1].x, transformedVertices[2].x, transformedVertices[3].x,
                       transformedVertices[4].x, transformedVertices[5].x, transformedVertices[6].x, transformedVertices[7].x });

    min.y = std::min({ transformedVertices[0].y, transformedVertices[1].y, transformedVertices[2].y, transformedVertices[3].y,
                       transformedVertices[4].y, transformedVertices[5].y, transformedVertices[6].y, transformedVertices[7].y });
    max.y = std::max({ transformedVertices[0].y, transformedVertices[1].y, transformedVertices[2].y, transformedVertices[3].y,
                       transformedVertices[4].y, transformedVertices[5].y, transformedVertices[6].y, transformedVertices[7].y });

    min.z = std::min({ transformedVertices[0].z, transformedVertices[1].z, transformedVertices[2].z, transformedVertices[3].z,
                       transformedVertices[4].z, transformedVertices[5].z, transformedVertices[6].z, transformedVertices[7].z });
    max.z = std::max({ transformedVertices[0].z, transformedVertices[1].z, transformedVertices[2].z, transformedVertices[3].z,
                       transformedVertices[4].z, transformedVertices[5].z, transformedVertices[6].z, transformedVertices[7].z });

    // Check if the point is inside the cuboid
    if (point.x + positionPoint.x >= min.x && point.x + positionPoint.x <= max.x &&
        point.y + positionPoint.y >= min.y && point.y + positionPoint.y <= max.y &&
        point.z + positionPoint.z >= min.z && point.z + positionPoint.z <= max.z) {
        return 1; // Point is inside the cuboid
    }
    return 0; // Point is outside the cuboid
}

std::vector<float> RoverSystem::getTerrainHeights(const HitBoxComponentTerrain& terrain,
    const std::array<glm::vec2, 4>& points) {
    std::vector<float> heights;
    heights.reserve(4);

    // Iterate through each point
    for (const auto& p : points) {
        bool found = false;

        for (const auto& triangle : terrain.triangles) {
            // Extract triangle vertices
            glm::vec3 v0 = triangle[0];
            glm::vec3 v1 = triangle[1];
            glm::vec3 v2 = triangle[2];

            // Project triangle to 2D
            glm::vec2 A(v0.x, v0.y);
            glm::vec2 B(v1.x, v1.y);
            glm::vec2 C(v2.x, v2.y);

            // Check if the point is inside this triangle
            if (pointInTriangle2D(p, A, B, C)) {
                // Calculate plane equation: Ax + By + Cz + D = 0
                glm::vec3 edge1 = v1 - v0;
                glm::vec3 edge2 = v2 - v0;
                glm::vec3 normal = glm::cross(edge1, edge2);

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
                else {
                    throw std::runtime_error("getTerrainHeights: Degenerate plane with C = 0");
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
    auto cross = [](const glm::vec2& u, const glm::vec2& v) {
        return u.x * v.y - u.y * v.x;
        };

    glm::vec2 ab = b - a;
    glm::vec2 bc = c - b;
    glm::vec2 ca = a - c;

    glm::vec2 ap = p - a;
    glm::vec2 bp = p - b;
    glm::vec2 cp = p - c;

    float cross1 = cross(ab, ap);
    float cross2 = cross(bc, bp);
    float cross3 = cross(ca, cp);

    // Sprawdzenie, czy wszystkie iloczyny wektorowe mają ten sam znak
    return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0);
}
