#include "rover_system.h"
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

glm::vec3 position = { 0.0f, 0.0f, 0.0f };
float angle = 0.0f;
float speed = 0.0f;
float turnSpeed = 0.5f;
float wheelAngle = 0.0f;

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
}

void RoverSystem::update(
    std::unordered_map<unsigned int, TransformComponent>& transformComponents,
    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents, float dt, unsigned int controlledEntity)
{
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
            glm::vec3 rotatedOffset = glm::rotateZ(localOffset, glm::radians(transformComponents[0].eulers.z));
            transformComponents[i].position = transformComponents[0].position + rotatedOffset;
            physicsComponents[i].velocity = physicsComponents[0].velocity;

            transformComponents[i].eulers.y += speed;
			if (transformComponents[i].eulers.y > 360.0f) transformComponents[i].eulers.y -= 360.0f;
        }
        else {
            physicsComponents[i].velocity = glm::vec3(direction.x, direction.y, 0.0f) * speed;
        }
        if(i == PRAWE_KOLO_PRZOD || i == LEWE_KOLO_PRZOD)
			transformComponents[i].eulers.z = angle * (180.0f / MPI) + wheelAngle;
        else
            transformComponents[i].eulers.z = angle * (180.0f / MPI);
		
        //std::cout << transformComponents[i].eulers.y << std::endl;
    }
    
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        speed *= 0.95f;
        if (std::abs(speed) < 0.1f) speed = 0.0f;
    }
}
