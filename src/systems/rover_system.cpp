#include "rover_system.h"
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

glm::vec3 position = { 0.0f, 0.0f, 0.0f };
float angle = 0.0f;
float speed = 0.0f;
float turnSpeed = 0.5f;
float wheelAngle = 0.0f;
bool jebna = false;

const float acceleration = 2.0f;
const float deceleration = 5.0f;
const float MPI = 3.14159265359;
int const PRAWE_KOLO_PRZOD = 1;
int const PRAWE_KOLO_TYL = 2;
int const LEWE_KOLO_PRZOD = 3;
int const LEWE_KOLO_TYL = 4;
const float MAX_SPEED = 5.0f;
const float MAX_WHEEL_ANGLE = 30.0f;


RoverSystem::RoverSystem(GLFWwindow* window) {
    this->window = window;
    tempPositions = {};
}

void RoverSystem::update(
    std::unordered_map<unsigned int, TransformComponent>& transformComponents,
    std::unordered_map<unsigned int, TransformHitBoxComponent>& transformComponentsHitbox,
    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
    std::unordered_map<unsigned int, HitBoxComponent>& HitBoxComponent,
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
        angle += (dt * wheelAngle * turnSpeed)/30;
    }
    else
	{
        angle += (dt * wheelAngle * speed)/30;
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
            tempPositions[0].eulers.z = angle * (180.0f / MPI);
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
    for (const auto& [key, hitbox] : HitBoxComponent) {
        if (key > controlledEntity) {
        for (const auto& vertex : hitbox.vertices) {
            if (isPointInsideCube(vertex,HitBoxComponent[0].vertices, transformComponentsHitbox[0].position, transformComponentsHitbox[key].position) != 0) {
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
    }
    else {
        for (int i = 0; i <= controlledEntity; i++) {
        transformComponents[i] = tempPositions[i];
        }
    }

    jebna = false;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        speed *= 0.95f;
        if (std::abs(speed) < 0.1f) speed = 0.0f;
    }
}

int RoverSystem::isPointInsideCube(const glm::vec3& point, const std::vector<glm::vec3>& vertices, const glm::vec3& positionRover, const glm::vec3& positionPoint) {
    float minX = std::min({ vertices[0].x + positionRover.x, vertices[1].x + positionRover.x, vertices[2].x + positionRover.x, vertices[3].x + positionRover.x,
                           vertices[4].x + positionRover.x, vertices[5].x + positionRover.x, vertices[6].x + positionRover.x, vertices[7].x + positionRover.x });
    float maxX = std::max({ vertices[0].x + positionRover.x, vertices[1].x + positionRover.x, vertices[2].x + positionRover.x, vertices[3].x + positionRover.x,
                           vertices[4].x + positionRover.x, vertices[5].x + positionRover.x, vertices[6].x + positionRover.x, vertices[7].x + positionRover.x });

    float minY = std::min({ vertices[0].y + positionRover.y, vertices[1].y + positionRover.y, vertices[2].y + positionRover.y, vertices[3].y + positionRover.y,
                           vertices[4].y + positionRover.y, vertices[5].y + positionRover.y, vertices[6].y + positionRover.y, vertices[7].y + positionRover.y });
    float maxY = std::max({ vertices[0].y + positionRover.y, vertices[1].y + positionRover.y, vertices[2].y + positionRover.y, vertices[3].y + positionRover.y,
                           vertices[4].y + positionRover.y, vertices[5].y + positionRover.y, vertices[6].y + positionRover.y, vertices[7].y + positionRover.y });

    float minZ = std::min({ vertices[0].z + positionRover.z, vertices[1].z + positionRover.z, vertices[2].z + positionRover.z, vertices[3].z + positionRover.z,
                           vertices[4].z + positionRover.z, vertices[5].z + positionRover.z, vertices[6].z + positionRover.z, vertices[7].z + positionRover.z });
    float maxZ = std::max({ vertices[0].z + positionRover.z, vertices[1].z + positionRover.z, vertices[2].z + positionRover.z, vertices[3].z + positionRover.z,
                           vertices[4].z + positionRover.z, vertices[5].z + positionRover.z, vertices[6].z + positionRover.z, vertices[7].z + positionRover.z });

    if (point.x + positionPoint.x >= minX && point.x + positionPoint.x <= maxX &&
        point.y + positionPoint.y >= minY && point.y + positionPoint.y <= maxY &&
        point.z + positionPoint.z >= minZ && point.z + positionPoint.z <= maxZ)
    {
        return 1;
    }
    return 0;
}

