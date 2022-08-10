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

		directionalShadowShader = std::make_shared<DirectionalShadowMapShader>();
		glCheckError();
		pointShadowShader = std::make_shared<PointShadowMapShader>();
		glCheckError();
		standardShader = std::make_shared<PhongShader>();
		solidShader = std::make_shared<SolidShader>();
		skyboxShader = std::make_shared<SkyboxShader>();
		
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
				if (std::find(directionalShadowShader->pointLights.begin(), directionalShadowShader->pointLights.end(), pointLight) == directionalShadowShader->pointLights.end()) { // the vector does not contain the light
					directionalShadowShader->addPointLight(pointLight);
				}

				if (std::find(standardShader->pointLights.begin(), standardShader->pointLights.end(), pointLight) == standardShader->pointLights.end()) { // the vector does not contain the light
					standardShader->addPointLight(pointLight);
				}

				if (std::find(pointShadowShader->pointLights.begin(), pointShadowShader->pointLights.end(), pointLight) == pointShadowShader->pointLights.end()) { // the vector does not contain the light
					pointShadowShader->addPointLight(pointLight);
				}
			}

			for (DirectionalLight dirLight : dirLights) {
				if (std::find(directionalShadowShader->directionalLights.begin(), directionalShadowShader->directionalLights.end(), dirLight) == directionalShadowShader->directionalLights.end()) { // the vector does not contain the light
					directionalShadowShader->addDirectionalLight(dirLight);
				}

				if (std::find(standardShader->directionalLights.begin(), standardShader->directionalLights.end(), dirLight) == standardShader->directionalLights.end()) { // the vector does not contain the light
					standardShader->addDirectionalLight(dirLight);
				}

				if (std::find(pointShadowShader->directionalLights.begin(), pointShadowShader->directionalLights.end(), dirLight) == pointShadowShader->directionalLights.end()) { // the vector does not contain the light
					pointShadowShader->addDirectionalLight(dirLight);
				}
			}
		}
	}

	void Scene::renderScene() {
		glCheckError();

		glCullFace(GL_FRONT);
		for (std::shared_ptr<Light> light : m_Lights) {
			DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(&*light);
			PointLight* pointLight = dynamic_cast<PointLight*>(&*light);
			if (dirLight != nullptr) {
				renderShadowMap(*dirLight);
				glCheckError();

			}
			else if (pointLight != nullptr) {
				renderShadowMap(*pointLight);
				glCheckError();

			}
		}

		glCullFace(GL_BACK);

		FrameBufferObject::unbind();
		glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, gWindow.getWidth(), gWindow.getHeight());
		glCheckError();

		// Normal rendering
		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			renderRenderComponent(gameobject);
			glCheckError();


			for (std::shared_ptr<Gameobject> gb : gameobject->getChildren()) {
				renderRenderComponent(gb);
				glCheckError();

			}
		}

		renderSkybox();
		glCheckError();

	}

	void Scene::renderSkybox() {
		skyboxShader->bind();
		glCheckError();

		skybox.render(*skyboxShader);
		glCheckError();

	}

	void Scene::renderShadowMap(DirectionalLight& dirLight) {
		glViewport(0, 0, (int)dirLight.shadowMapSize.x, (int)dirLight.shadowMapSize.y);
		dirLight.depthFBO.bind();

		glClear(GL_DEPTH_BUFFER_BIT);

		dirLight.makeLightSpaceMatrix();

		directionalShadowShader->bind();
		directionalShadowShader->getProgram().setMatrix4f("lightSpaceMatrix", dirLight.lightSpaceMatrix);

		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			renderRenderComponent(gameobject, directionalShadowShader);

			for (std::shared_ptr<Gameobject> gb : gameobject->getChildren()) {
				renderRenderComponent(gb, directionalShadowShader);
			}
		}
	}

	void Scene::renderShadowMap(PointLight& pointLight) {
		glViewport(0, 0, (int)pointLight.textureSizes.x, (int)pointLight.textureSizes.y);
		pointLight.shadowFBO.bind();
		glCheckError();

		glClear(GL_DEPTH_BUFFER_BIT);
		glCheckError();

		pointLight.makeLightSpaceMatricies();
		glCheckError();

		pointShadowShader->bind();
		pointShadowShader->getProgram().setMatrix4fs("shadowMatrices", pointLight.lightSpaceMatricies);
		glCheckError();

		for (std::shared_ptr<Gameobject> gameobject : m_Gameobjects) {
			renderRenderComponent(gameobject, pointShadowShader);

			for (std::shared_ptr<Gameobject> gb : gameobject->getChildren()) {
				renderRenderComponent(gb, pointShadowShader);
			}
		}
		glCheckError();

	}

	void Scene::renderRenderComponent(const std::shared_ptr<Gameobject> gb) {
		RenderComponent* renderComp = gb->getComponent<RenderComponent>();
		if (renderComp != nullptr) {
			SolidRenderingComponent* solidRenderComp = dynamic_cast<SolidRenderingComponent*>(renderComp);
			PhongRenderingComponent* phongRenderComp = dynamic_cast<PhongRenderingComponent*>(renderComp);
			if (solidRenderComp != nullptr) {
				solidShader->bind();
				solidRenderComp->render(solidShader);
				glCheckError();

			}
			else if (phongRenderComp != nullptr) {
				standardShader->bind();
				phongRenderComp->render(standardShader);
				glCheckError();

			}
		}
	}

	void Scene::renderRenderComponent(const std::shared_ptr<Gameobject> gb, std::shared_ptr<PShader> shader) {
		RenderComponent* renderComp = gb->getComponent<RenderComponent>();
		if (renderComp != nullptr) {
			shader->bind();
			renderComp->render(shader);
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