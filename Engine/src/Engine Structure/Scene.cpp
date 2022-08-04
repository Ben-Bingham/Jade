#include <algorithm>

#include "Engine Structure/Scene.h"
#include "Engine Structure/Engine.h"
#include "Entity Component System/Gameobjects/Lights/Light.h"

namespace Jade {
	Scene::~Scene() {}

	void Scene::begin() {
		Begin();

		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			RenderComponent* renderComp = gameobject->getComponent<RenderComponent>();
			if (renderComp != nullptr) {
				std::vector<PointLight> pointLights;
				std::vector<DirectionalLight> dirLights;
				for (std::shared_ptr<Light> light : m_Lights) {
					Light* lightPtr = light.get(); //TODO

					PointLight* pointLight = dynamic_cast<PointLight*>(lightPtr);
					DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(lightPtr);

					if (pointLight != nullptr) {
						pointLights.push_back(*pointLight);
					}
					else if (dirLight != nullptr) {
						dirLights.push_back(*dirLight);
					}
				}

				for (PointLight pointLight : pointLights) {
					if (std::find(renderComp->shader->pointLights.begin(), renderComp->shader->pointLights.end(), pointLight) == renderComp->shader->pointLights.end()) { // the vector does not contain the light
						renderComp->shader->addPointLight(pointLight);
					}
				}

				for (DirectionalLight dirLight : dirLights) {
					if (std::find(renderComp->shader->directionalLights.begin(), renderComp->shader->directionalLights.end(), dirLight) == renderComp->shader->directionalLights.end()) { // the vector does not contain the light
						renderComp->shader->addDirectionalLight(dirLight);
					}
				}
			}
			
			gameobject->begin();
		}
	}

	void Scene::update() {
		Update();
		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			gameobject->update();	

			render(gameobject);
			for (std::shared_ptr<Gameobject> gb : gameobject->getChildren()) {
				render(gb);
			}
		}
	}

	void Scene::cleanup() {
		Cleanup();
		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			gameobject->cleanup();
		}
	}
}