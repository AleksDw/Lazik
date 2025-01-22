#include "rover_system.h"
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

glm::vec3 position = { 0.0f, 0.0f, 0.0f };
float angle = 0.0f;
float speed = 0.0f;
float turnSpeed = 0.5f;
float wheelAngle = 0.0f;
float cd = 60;

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

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        speed *= 0.95f;
        if (std::abs(speed) < 0.1f) speed = 0.0f;
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
        angle += (dt * wheelAngle * turnSpeed)/30;
    }
	else if (abs(speed) > turnSpeed)
	{
		angle += (dt * wheelAngle * -turnSpeed) / 30;
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
        if (i == PRAWE_KOLO_PRZOD || i == LEWE_KOLO_PRZOD)
            tempPositions[i].eulers.z = angle * (180.0f / MPI) + wheelAngle;
        else {
            tempPositions[i].eulers.z = angle * (180.0f / MPI);
            transformComponentsHitbox[0].eulers.z = angle * (180.0f / MPI);
            transformComponentsHitbox[0].position = tempPositions[0].position;
        }
        tempPositions[i].position += physicsComponents[i].velocity * dt;
        tempPositions[i].eulers += physicsComponents[i].eulerVelocity * dt;
        if (tempPositions[i].eulers.z > 360)
        {
            tempPositions[i].eulers.z -= 360;
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

				// odpowiedŸ na kolizje, przesuniecie obiektu o mtv (powoduje sliding)
                for (int i = 0; i <= controlledEntity; i++){
                    tempPositions[i].position += mtv;
                }
            }
        }
    }


    for (int i = 0; i <= controlledEntity; i++) {
        transformComponents[i] = tempPositions[i];
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