#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "PShaders/PShader.h"
#include "High Level Rendering/Renderable Objects/RenderableObject.h"
#include "Core Systems/Logging/OpenGLErrors.h"

namespace Jade {
	class Renderer {
	public:
		Renderer()
			: m_View(glm::mat4(1.0f)), m_Projection(glm::mat4(1.0f)) {}

		void addRenderable(RenderableObject* renderable);

		void render(glm::vec3 cameraPos);

		void setMatrices(const glm::mat4& view, const glm::mat4& projection);

		void addRuleSet(PShader* ruleSet) {
			for (PShader* rSet : m_RuleSets) {
				if (rSet->ruleSet == ruleSet->ruleSet) {
					LOG("There is alread a ruleset of that type attached to the renderer, the one you added probably wont be uses", WARNING);
					break;
				}
			}
			m_RuleSets.push_back(ruleSet);
			m_Renderables.resize(m_RuleSets.size());
		}

		void setVector3f(const std::string name, const glm::vec3& vector) {
			for (PShader* ruleSet : m_RuleSets) {
				ruleSet->getProgram().use();
				ruleSet->getProgram().setVector3f(name, vector);
			}
		}

		void dispose() {
			for (std::vector<RenderableObject*> renderableVector : m_Renderables) {
				for (RenderableObject* renderable : renderableVector) {
					renderable->dispose();
				}
			}

			for (PShader* ruleSet : m_RuleSets) {
				ruleSet->dispose();
			}
		}

	private:
		std::vector<PShader*> m_RuleSets;
		std::vector<std::vector<RenderableObject*>> m_Renderables;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}