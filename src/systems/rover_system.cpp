#include "rover_system.h"
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

glm::vec3 position = { 0.0f, 0.0f, 0.0f };
float angle = 0.0f;
float speed = 0.0f;
float acceleration = 2.0f;
float maxSpeed = 5.0f;
float deceleration = 5.0f;
float turnSpeed = 0.5f;
float MPI = 3.14159265359;
const float wheelRadius = 0.5f;

RoverSystem::RoverSystem(GLFWwindow* window) {
    this->window = window;
}

void RoverSystem::update(
    std::unordered_map<unsigned int, TransformComponent>& transformComponents,
    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents, float dt, unsigned int controlledEntity)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        speed += acceleration * dt;
        if (speed > maxSpeed) speed = maxSpeed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            angle += turnSpeed * dt;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            angle -= turnSpeed * dt;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        speed -= acceleration * dt;
        if (speed < -maxSpeed) speed = -maxSpeed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            angle += turnSpeed * dt;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            angle -= turnSpeed * dt;
        }
    }

    angle = fmod(angle, 2.0f * MPI);
    if (angle < 0) {
        angle += 2.0f * MPI;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS) {
        if (speed > 0.0f) {
            speed = speed * 0.99;
            if (speed < 0.0f) speed = 0.0f;
        }
        else if (speed < 0.0f) {
            speed = speed * 0.99;
            if (speed > 0.0f) speed = 0.0f;
        }
    }
    glm::vec2 direction = glm::rotate(glm::vec2(1.0f, 0.0f), angle);
    for (int i = 0; i <= controlledEntity; i++) {
        if (i > 0) {
            glm::vec3 localOffset;
            switch (i) {
            case 1:
                localOffset = glm::vec3(5, 5, -1.0f);
                break;
            case 2:
                localOffset = glm::vec3(1.85486f, -0.64958f, -0.686f);
                break;
            case 3:
                localOffset = glm::vec3(5, 5, -1.0f);
                break;
            case 4:
                localOffset = glm::vec3(5, 5, -1.0f);
                break;
            default:
                localOffset = glm::vec3(0.0f, 0.0f, 0.0f);
                break;
            }
            glm::vec3 rotatedOffset = glm::rotateZ(localOffset, glm::radians(transformComponents[0].eulers.z));
            transformComponents[i].position = transformComponents[0].position + rotatedOffset;
            physicsComponents[i].velocity = physicsComponents[0].velocity;

            transformComponents[i].eulers.y += speed;
			if (transformComponents[i].eulers.y > 360.0f) transformComponents[i].eulers.y -= 360.0f;
        }
        else {
            physicsComponents[i].velocity = glm::vec3(direction.x, direction.y, 0.0f) * speed;
        }
        transformComponents[i].eulers.z = angle * (180.0f / MPI);
        //std::cout << transformComponents[i].eulers.y << std::endl;
    }
    
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        speed *= 0.95f;
        if (std::abs(speed) < 0.1f) speed = 0.0f;
    }
}
