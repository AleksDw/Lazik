#include "config.h"
#include "controller/app.h"

#include "components/camera_component.h"
#include "components/physics_component.h"
#include "components/render_component.h"
#include "components/transform_component.h"
#include "components/transformHitBox_component.h"

#include "factories/factory.h"

int main() 
{

	App* app = new App();
	Factory* factory = new Factory(
		app->physicsComponents, 
		app->renderComponents, app->renderComponentsHitbox,app->hitBoxComponentTerrain, app->transformComponents, app->transformComponentsHitbox);
	
	unsigned int roverEntity = factory->make_rover({ 5.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, {0.0f, 0.0f, 0.0f});
	app->roverID = roverEntity;
	for (int i = 0; i < 6; i++) {
		factory->make_bullet({ 0.0f, -30.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	}

	factory->make_terrain({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	factory->make_rockWalls({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, {0.0f,0.0f,0.0f});
	factory->make_bum({ 0.0f, 38.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
	factory->make_bum({ 0.0f, -38.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
	factory->make_bum2({ 38.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
	factory->make_bum2({ -38.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });

	factory->make_tree1({ 10.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	factory->make_tree2({ -5.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });

	factory->make_rocks1({ -15.0f, 0.0f,0.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	factory->make_rocks2({ -25.0f, -8.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	factory->make_rocks1({ 15.0f, 30.0f, -0.2f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	factory->make_rocks2({ 25.0f, 0.0f, -0.7f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	factory->make_rocks1({ -25.0f, 15.0f, 0.7f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	factory->make_rocks2({ -25.0f, -25.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });


	unsigned int cameraEntity = factory->make_camera(
		{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f,0.0f});

	CameraComponent* camera = new CameraComponent();
	app->cameraComponent = camera;
	app->cameraID = cameraEntity;

	app->set_up_opengl();
	app->make_systems();

	app->run();

	delete factory;
	delete app;
	return 0;
}