#pragma once
#include "../config.h"

#include "../components/camera_component.h"
#include "../components/physics_component.h"
#include "../components/render_component.h"
#include "../components/transform_component.h"
#include "../components/hitBox_component.h"
#include "../components/transformHitBox_component.h"

#include "../systems/camera_system.h"
#include "../systems/motion_system.h"
#include "../systems/render_system.h"
#include "../systems/rover_system.h"


#include "../view/shader.h"

class App 
{
public:
    App();
    ~App();
    void run();
    void set_up_opengl();
    void make_systems();

    //Components
    std::unordered_map<unsigned int, TransformComponent> transformComponents;
    std::unordered_map<unsigned int, TransformHitBoxComponent> transformComponentsHitbox;
    std::unordered_map<unsigned int, PhysicsComponent> physicsComponents;
    CameraComponent* cameraComponent;
    unsigned int cameraID;
    unsigned int roverID;
    std::unordered_map<unsigned int, RenderComponent> renderComponents;
    std::unordered_map<unsigned int, HitBoxComponent> renderComponentsHitbox;
    std::unordered_map<unsigned int, HitBoxComponentTerrain> hitBoxComponentTerrain;
    
private:
    void set_up_glfw();

    GLFWwindow* window;

    unsigned int shader;

    //Systems
	RoverSystem* roverSystem;
    MotionSystem* motionSystem;
    CameraSystem* cameraSystem;
    RenderSystem* renderSystem;
};