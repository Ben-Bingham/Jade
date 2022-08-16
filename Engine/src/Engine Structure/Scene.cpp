#include <algorithm>

#include "Engine Structure/Scene.h"
#include "Engine Structure/Engine.h"
#include "Entity Component System/Gameobjects/Lights/Light.h"
#include "High Level Rendering/PShaders/DirectionalShadowMapShader.h"
#include "High Level Rendering/PShaders/SkyboxShader.h"
#include "High Level Rendering/Renderable Objects/SkyboxRenderableObject.h"
#include "High Level Rendering/PShaders/PointShadowMapShader.h"

namespace Jade {
	Scene::~Scene() {}

	void Scene::begin() {
		Begin();
		
		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {		
			gameobject->begin();
		}
	}

	std::vector<std::shared_ptr<RenderableObject>> Scene::getRenderableObjects(const Gameobject& gameobject) {
		std::vector<std::shared_ptr<RenderableObject>> renderables;

		RenderComponent* renderComp = gameobject.getComponent<RenderComponent>();
		if (renderComp != nullptr) {
			for (std::shared_ptr<RenderableObject> renderable : renderComp->renderables) {
				renderables.push_back(renderable);
			}
		}

		return renderables;
	}

	void Scene::update() {
		Update();

		std::vector<std::shared_ptr<RenderableObject>> renderables; //TODO probably does not need to be created every frame and can stay the same

		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			gameobject->update();

			std::vector<std::shared_ptr<RenderableObject>> renderableObjects = getRenderableObjects(*gameobject);

			renderables.insert(renderables.end(), renderableObjects.begin(), renderableObjects.end());
		}

		gRenderer.render(renderables, m_Lights);

	}

	void Scene::cleanup() {
		Cleanup();
		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			gameobject->cleanup();
		}
	}
}