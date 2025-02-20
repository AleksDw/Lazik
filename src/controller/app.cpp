#include "app.h"

#include <chrono>
#include <thread>

App::App() 
{
    set_up_glfw();
}

App::~App() 
{
    glDeleteProgram(shader);

	delete roverSystem;
    delete motionSystem;
    delete cameraSystem;
    delete renderSystem;
    
    glfwTerminate();
}

void App::run() 
{

	const auto frame_duration = std::chrono::milliseconds(16);

    while (!glfwWindowShouldClose(window)) 
	{

		auto frame_start = std::chrono::high_resolution_clock::now();
        motionSystem->update(
            transformComponents, physicsComponents, 16.67f/1000.0f);
		roverSystem->update(
			transformComponents,transformComponentsHitbox, physicsComponents,renderComponentsHitbox, hitBoxComponentTerrain, 16.67f / 1000.0f, roverID);

        bool should_close = cameraSystem->update(
            transformComponents, cameraID, *cameraComponent, 16.67f/1000.0f);
		if (should_close) 
		{
			break;
		}
		renderSystem->update(transformComponents, transformComponentsHitbox, renderComponents);

		auto frame_end = std::chrono::high_resolution_clock::now();
		auto frame_time = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end - frame_start);

		if (frame_duration > frame_time)
		{
			std::this_thread::sleep_for(frame_duration - frame_time);
		}

	}
}

void App::set_up_glfw() 
{

    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	char fullscreen;
	std::cout << "Fullscreen? (y/n): ";
	std::cin >> fullscreen;

	if (fullscreen == 'y')
	{
		window = glfwCreateWindow(mode->width, mode->height, "Hello Window!", monitor, NULL);
	}
	else
	{
		window = glfwCreateWindow(1280, 960, "Hello Window!", NULL, NULL);
	}
	
	
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
	}

}

void App::set_up_opengl() 
{

    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
	//Set the rendering region to the actual screen size
	int w,h;
	glfwGetFramebufferSize(window, &w, &h);
	//(left, top, width, height)
	glViewport(0,0,w,h);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    shader = make_shader(
		"../../../src/shaders/vertex.txt", 
		"../../../src/shaders/fragment.txt");
    
    glUseProgram(shader);
	unsigned int projLocation = glGetUniformLocation(shader, "projection");
	glm::mat4 projection = glm::perspective(
									// render distance
		45.0f, static_cast<float>(w) / static_cast<float>(h), 0.1f, 200.0f);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void App::make_systems() 
{
	roverSystem = new RoverSystem(window);
    motionSystem = new MotionSystem();
    cameraSystem = new CameraSystem(shader, window);
    renderSystem = new RenderSystem(shader, window);
}