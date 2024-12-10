#include "rover_system.h"
#include <iostream>

RoverSystem::RoverSystem(GLFWwindow* window)
{
	this->window = window;
}

void RoverSystem::update(
    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents, float dt, unsigned int controlledEntity)
{
    //Keys
    glm::vec3 velocity = { 0.0f, 0.0f, 0.0f };
	glm::vec3 eulerVelocity = { 0.0f, 0.0f, 0.0f };
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        velocity.x += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        velocity.y -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        velocity.x -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        velocity.y += 1.0f;
    }

	// TODO: add transformation(like motion_system.cpp)
	/*if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		eulerVelocity.z += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		eulerVelocity.z -= 1.0f;
	}*/
	if (glm::length(velocity) > 0.1f)
	{
		velocity = glm::normalize(velocity);
		physicsComponents[controlledEntity].velocity += 0.1f * velocity * dt;
		//physicsComponents[controlledEntity].eulerVelocity += 0.1f * eulerVelocity * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		physicsComponents[controlledEntity].velocity *= 0.999f; // hamowanie
		if(physicsComponents[controlledEntity].velocity.x > -0.5f && physicsComponents[controlledEntity].velocity.x < 0.5f) // zatrzymanie
		{
			physicsComponents[controlledEntity].velocity.x = 0;
		}
	}
	std::cout << physicsComponents[controlledEntity].velocity.x << std::endl;


}