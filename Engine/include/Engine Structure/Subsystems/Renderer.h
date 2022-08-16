#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine Structure/Subsystems/Subsystem.h"
#include "High Level Rendering/Renderable Objects/RenderableObject.h"
#include "Entity Component System/Gameobjects/Lights/Light.h"
#include "High Level Rendering/PShaders/DirectionalShadowMapShader.h"
#include "High Level Rendering/PShaders/SkyboxShader.h"
#include "High Level Rendering/Renderable Objects/SkyboxRenderableObject.h"
#include "High Level Rendering/PShaders/PointShadowMapShader.h"
#include "High Level Rendering/PShaders/PShader.h"
#include "High Level Rendering/PShaders/PhongShader.h"
#include "High Level Rendering/PShaders/SolidShader.h"

namespace Jade {
	class Engine;

	class Renderer : public Subsystem {
	public:
		Renderer() {}

		void StartUp() override {
			directionalShadowShader = std::make_shared<DirectionalShadowMapShader>();
			pointShadowShader = std::make_shared<PointShadowMapShader>();
			phongShader = std::make_shared<PhongShader>();
		}

		void ShutDown() override {}

		void update() {
			glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void render(std::vector<std::shared_ptr<RenderableObject>> renderables, std::vector<std::shared_ptr<Light>> lights) {
			PhongShader* phong = dynamic_cast<PhongShader*>(&*phongShader);
			phong->clearLights();
			phong->setLights(lights);

			renderShadowMaps(renderables, lights);

			renderNormally(renderables, lights);
		}

	private:
		void renderObject(std::shared_ptr<RenderableObject> renderable, std::shared_ptr<PShader> shader) {
			shader->bind();
			shader->uploadUniforms();
			renderable->uploadUniforms(shader);
			renderable->render(shader);
		}

		void renderShadowMap(std::vector<std::shared_ptr<RenderableObject>> renderables, const DirectionalLight& dirLight) { //TODO remove overload
			glViewport(0, 0, (int)dirLight.shadowMapSize.x, (int)dirLight.shadowMapSize.y);
			dirLight.depthFBO.bind();

			glClear(GL_DEPTH_BUFFER_BIT);

			DirectionalShadowMapShader* dirLightShader = dynamic_cast<DirectionalShadowMapShader*>(&*directionalShadowShader);
			dirLightShader->setLight(dirLight);

			for (std::shared_ptr<RenderableObject> renderable : renderables) {
				renderObject(renderable, pointShadowShader);
			}
		}

		void renderShadowMap(std::vector<std::shared_ptr<RenderableObject>> renderables, const PointLight& pointLight) {
			glViewport(0, 0, (int)pointLight.textureSizes.x, (int)pointLight.textureSizes.y);
			pointLight.shadowFBO.bind();

			glClear(GL_DEPTH_BUFFER_BIT);

			PointShadowMapShader* pointLightShader = dynamic_cast<PointShadowMapShader*>(&*pointShadowShader);
			pointLightShader->setLight(pointLight);

			for (std::shared_ptr<RenderableObject> renderable : renderables) {
				renderObject(renderable, pointShadowShader);
			}
		}

		void renderShadowMaps(std::vector<std::shared_ptr<RenderableObject>> renderables, std::vector<std::shared_ptr<Light>> lights) {
			glCullFace(GL_FRONT);
			for (std::shared_ptr<Light> light : lights) {
				DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(&*light);
				PointLight* pointLight = dynamic_cast<PointLight*>(&*light);
				if (dirLight != nullptr) {
					renderShadowMap(renderables, *dirLight);
				}
				else if (pointLight != nullptr) {
					renderShadowMap(renderables, *pointLight);
				}
			}
			glCullFace(GL_BACK);

			FrameBufferObject::unbind();
		}

		void renderNormally(std::vector<std::shared_ptr<RenderableObject>> renderables, std::vector<std::shared_ptr<Light>> lights);

		void renderSkybox(Cubemap skybox) { //TODO

		}

		std::shared_ptr<PShader> directionalShadowShader{ nullptr }; //TODO make these global or static
		std::shared_ptr<PShader> pointShadowShader{ nullptr };
		std::shared_ptr<PShader> phongShader{ nullptr };
	};
}