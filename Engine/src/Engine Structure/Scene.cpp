#include <algorithm>

#include "Engine Structure/Scene.h"
#include "Engine Structure/Engine.h"
#include "Entity Component System/Gameobjects/Lights/Light.h"
#include "High Level Rendering/PShaders/ShadowMapShader.h"

namespace Jade {
	Scene::~Scene() {}

	void Scene::begin() {
		Begin();

		depthShader = std::make_shared<ShadowMapShader>();

		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			applyAllLights(*gameobject);

			for (std::shared_ptr<Gameobject> gb : gameobject->getChildren()) {
				applyAllLights(*gb);
			}

			gameobject->begin();
		}
	}

	void Scene::applyAllLights(Gameobject& gb) {
		RenderComponent* renderComp = gb.getComponent<RenderComponent>();
		if (renderComp != nullptr) {
			std::vector<PointLight> pointLights;
			std::vector<DirectionalLight> dirLights;
			for (std::shared_ptr<Light> light : m_Lights) {
				Light* lightPtr = light.get();

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
					depthShader->addPointLight(pointLight);
				}
			}

			for (DirectionalLight dirLight : dirLights) {
				if (std::find(renderComp->shader->directionalLights.begin(), renderComp->shader->directionalLights.end(), dirLight) == renderComp->shader->directionalLights.end()) { // the vector does not contain the light
					renderComp->shader->addDirectionalLight(dirLight);
					depthShader->addDirectionalLight(dirLight);
				}
			}
		}
	}

	void Scene::renderScene() {
		glCullFace(GL_FRONT);
		for (std::shared_ptr<Light> light : m_Lights) {
			DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(&*light);
			if (dirLight != nullptr) {
				renderShadowMap(*dirLight);
			}
		}

		glCullFace(GL_BACK);

		FrameBufferObject::unbind();
		glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, gWindow.getWidth(), gWindow.getHeight());

		// Normal rendering
		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			renderRenderComponent(gameobject);

			for (std::shared_ptr<Gameobject> gb : gameobject->getChildren()) {
				renderRenderComponent(gb);
			}
		}
	}

	void Scene::renderShadowMap(DirectionalLight& dirLight) {
		glViewport(0, 0, (int)dirLight.shadowMapSize.x, (int)dirLight.shadowMapSize.y);
		dirLight.depthFBO.bind();

		glClear(GL_DEPTH_BUFFER_BIT);

		dirLight.makeLightSpaceMatrix();

		depthShader->bind();
		depthShader->getProgram().setMatrix4f("lightSpaceMatrix", dirLight.lightSpaceMatrix);

		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			renderRenderComponent(gameobject, depthShader);

			for (std::shared_ptr<Gameobject> gb : gameobject->getChildren()) {
				renderRenderComponent(gb, depthShader);
			}
		}
	}

	void Scene::update() {
		Update();

		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			gameobject->update();
		}

		renderScene();
	}

	void Scene::cleanup() {
		Cleanup();
		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			gameobject->cleanup();
		}
	}
}