#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "High Level Rendering/PShaders/PShader.h"
#include "High Level Rendering/Renderable Objects/RenderableObject.h"
#include "Core Systems/Logging/OpenGLErrors.h"
#include "Engine Structure/Subsystems/Subsystem.h"
#include "High Level Rendering/PShaders/PhongShader.h"
#include "High Level Rendering/PShaders/SolidShader.h"
#include "High Level Rendering/LightCreator.h"

namespace Jade {
	class Engine;

	class Renderer : public Subsystem {
	public:
		Renderer()
			: m_View(glm::mat4(1.0f)), m_Projection(glm::mat4(1.0f)) {}

		void StartUp() override {
			PhongShader* phongShader = new PhongShader{};
			phongShader->addPointLight(LightCreator::DefaultPointLight()); //TODO remove
			phongShader->addDirectionalLight(LightCreator::DefaultDirectionalLight()); //TODO remove

			addShader(phongShader);

			SolidShader* solidShader = new SolidShader{};

			addShader(solidShader);
		}

		void ShutDown() override {
			for (std::vector<RenderableObject*> renderableVector : m_Renderables) {
				for (RenderableObject* renderable : renderableVector) {
					renderable->dispose();
				}
			}

			for (PShader* shader : m_PShaders) {
				shader->dispose();
				delete shader;
			}
		}

		void update();

		void addRenderable(RenderableObject* renderable);

		void render();

		void setMatrices(const glm::mat4& view, const glm::mat4& projection);

		void addShader(PShader* ruleSet) {
			for (PShader* rSet : m_PShaders) {
				if (rSet->ruleSet == ruleSet->ruleSet) {
					LOG("There is alread a ruleset of that type attached to the renderer, the one you added probably wont be used", WARNING);
					break;
				}
			}
			m_PShaders.push_back(ruleSet);
			m_Renderables.resize(m_PShaders.size());
		}

		void setVector3f(const std::string name, const glm::vec3& vector) {
			for (PShader* ruleSet : m_PShaders) {
				ruleSet->getProgram().use();
				ruleSet->getProgram().setVector3f(name, vector);
			}
		}

	private:
		std::vector<PShader*> m_PShaders;
		std::vector<std::vector<RenderableObject*>> m_Renderables;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}