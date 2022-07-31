#include <memory>

#include "Engine Structure/Subsystems/Renderer.h"
#include "Engine Structure/Engine.h"
#include "Entity Component System/Gameobjects/Lights/PointLight.h"

namespace Jade {
	void Renderer::addRenderable(RenderableObject* renderable) {
		int count = 0;
		for (PShader* ruleSet : m_PShaders) {
			if (renderable->followsRuleSet(*ruleSet)) {
				m_Renderables[count].push_back(renderable);
				return;
			}
			count++;
		}
		LOG("Renderer does not have a rule set that can support that renderable.", WARNING);
	}

	void Renderer::render() {
		int count = 0;
		for (PShader* ruleSet : m_PShaders) {
			ruleSet->bind();
			ruleSet->getProgram().setVector3f("cameraPosition", gCamera.getComponent<Transform>()->position);
			ruleSet->bindAdditionals();

			ruleSet->getProgram().setMatrix4f("view", gCamera.getViewMatrix());
			ruleSet->getProgram().setMatrix4f("projection", gWindow.getProjectionMatrix());

			std::vector<RenderableObject*>::iterator it;
			for (it = m_Renderables[count].begin(); it != m_Renderables[count].end(); ++it) {
				(*it)->render(*ruleSet);
			}
			count++;
		}
	}

	void Renderer::update() {
		glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render();
	}

	void Renderer::loadScene(Scene* scene) {
		for (PShader* shader : m_PShaders) {
			shader->clearLights();

			for (std::shared_ptr<Light> light : scene->getLights()) {
				PointLight* pointLight = dynamic_cast<PointLight*>(light.get());
				if (pointLight != nullptr) {
					shader->addPointLight(*pointLight);
				}
			}
		}
	}
}