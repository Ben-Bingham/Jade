#include "Engine Structure/Engine.h"
#include "DemoScene.h"
#include "Entity Component System/Components/FPSController.h"

int main() {
	Jade::Engine engine{};
	engine.StartUp();

	Jade::Camera camera;
	engine.setCamera(camera);

	Jade::FPSController fpsController;
	camera.addComponent(fpsController);

	DemoScene scene{};
	scene.addGameobject(camera);

	engine.LoadScene(scene);

	engine.ShutDown();
	return 0;
}
