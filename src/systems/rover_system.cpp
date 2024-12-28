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


bool jedzie;

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

        if (controlledEntity == 1 || controlledEntity == 2)
        {
            jedzie = true;
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
    physicsComponents[controlledEntity].velocity = glm::vec3(direction.x, direction.y, 0.0f) * speed;
    transformComponents[controlledEntity].eulers.z = angle * (180.0f / MPI);
    if (jedzie) {
        // Rotate around x-axis like a spinning wheel
        float wheelRadius = 0.5f; // Example wheel radius
        float wheelSpin = 200;
        transformComponents[controlledEntity].eulers.x += glm::degrees(wheelSpin); // Update wheel rotation
    }
    jedzie = false;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        speed *= 0.95f;
        if (std::abs(speed) < 0.1f) speed = 0.0f;
    }
}
