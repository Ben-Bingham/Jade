#include "Engine Structure/Scene.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	Scene::~Scene() {}

	void Scene::begin(/*Application& app*/) {
		Begin();

		for (Gameobject* gameobject : m_Gameobjects) {
			gameobject->begin();
			RenderComponent* desiredComponent = gameobject->getComponent<RenderComponent>();
			if (desiredComponent != nullptr) {
				for (std::shared_ptr<RenderableObject> renderable : desiredComponent->renderables) {
					gRenderer.addRenderable(renderable);
				}
			}
		}
	}

	void Scene::update() {
		Update();
		for (Gameobject* gameobject : m_Gameobjects) {
			gameobject->update();			
		}
	}

	void Scene::cleanup() {
		Cleanup();
		for (Gameobject* gameobject : m_Gameobjects) {
			gameobject->cleanup();
		}
	}
}