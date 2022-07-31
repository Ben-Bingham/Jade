#include <glm/glm.hpp>

#include "High Level Rendering/PShaders/PShader.h"
#include "High Level Rendering/PShaders/PhongShader.h"
#include "High Level Rendering/PShaders/SolidShader.h"
#include "High Level Rendering/Renderable Objects/SolidRenderableObject.h"
#include "High Level Rendering/Renderable Objects/PhongRenderableObject.h"
#include "High Level Rendering/MaterialCreator.h"
#include "Entity Component System/GameObjects/Gameobject.h"
#include "Entity Component System/Components/PhongRenderingComponent.h"
#include "Engine Structure/Engine.h"
#include "Level1.h"
#include "Entity Component System/Components/FPSController.h"

int main() {
	Jade::Engine engine{};
	engine.StartUp();

	Jade::Camera camera;
	engine.setCamera(camera);

	Jade::FPSController fpsController;
	camera.addComponent(&fpsController);

	Level1 lvl1{};
	lvl1.addGameobject(camera);

	engine.LoadScene(&lvl1);
	engine.LoadScene(&lvl1);

	engine.ShutDown();
	return 0;
}
