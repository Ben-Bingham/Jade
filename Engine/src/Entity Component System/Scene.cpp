#include "Entity Component System/Scene.h"
#include "Engine Structure/Application.h"

namespace Jade {
	Scene::~Scene() {}

	void Scene::begin(/*Application& app*/) {
		for (Gameobject* gameobject : m_Gameobjects) {
			gameobject->begin();

			/*PhongRenderingComponent* phongRenderingComponent = gameobject->getComponent<PhongRenderingComponent>();
			if (phongRenderingComponent != nullptr) {
				phongRenderingComponent->addRenderables(app);
			}*/
		}
	}

	void Scene::update() {
		for (Gameobject* gameobject : m_Gameobjects) {
			gameobject->update();
		}
	}

	void Scene::cleanup() {
		for (Gameobject* gameobject : m_Gameobjects) {
			gameobject->cleanup();
		}
	}
}