//#include "Core Systems/Application/Application.h" // Must be included first
//
//#include <iostream>
//#include <memory>
//
//#include "Core Systems/Game Objects System/GameObject.h"
//#include "Core Systems/Game Objects System/Scene.h"
//
//#include "Jade.h"
//
//int main() {
//
//	Jade::Application app("Jade test");
//	app.Begin(); // must be called first
//
//	Jade::Scene scene;
//
//	Jade::GameObject testCube;
//
//	testCube.transform->setPositon(glm::vec3(testCube.transform->getPosition().x, testCube.transform->getPosition().y, testCube.transform->getPosition().z + 3));
//
//	scene.addGameObject(testCube);
//
//	app.setActiveScene(scene);
//
//	while (app.GAME_OPEN) {
//		app.Update();
//
//		app.LateUpdate();
//	}
//
//	app.Cleanup();
//
//	return 0;
//}