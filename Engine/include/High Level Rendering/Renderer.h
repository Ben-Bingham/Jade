#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "RenderingRuleSet.h"
#include "RenderableObject.h"
#include "Core Systems/Logging/OpenGLErrors.h"

namespace Jade {
	class Renderer {
	public:
		Renderer(const RenderingRuleSet& ruleSet, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
			: m_RuleSet(ruleSet), m_View(viewMatrix), m_Projection(projectionMatrix) { }

		void addRenderable(RenderableObject& renderable) {
			if (renderable.followsRuleSet(m_RuleSet)) {
				m_Renderables.push_back(renderable);
			}
			else {
				LOGGER.log("Renderable did not follow rule set", WARNING);
			}
		}

		void render() {
			m_RuleSet.bind();
			glCheckError();

			m_RuleSet.getProgram().setMatrix4f("view", m_View);
			glCheckError();

			m_RuleSet.getProgram().setMatrix4f("projection", m_Projection);
			glCheckError();

			//upload any additional data needed for ruleset like lights
			m_RuleSet.getProgram().setLight("light", m_RuleSet.getLight());
			glCheckError();

			std::vector<std::reference_wrapper<RenderableObject>>::iterator it;
			for (it = m_Renderables.begin(); it != m_Renderables.end(); it++) {
				it->get().render(m_RuleSet);
			}
			glCheckError();

		}

		void setMatrices(const glm::mat4& view, const glm::mat4& projection) {
			m_View = view;
			m_Projection = projection;
		}

		RenderingRuleSet getRuleSet() { return m_RuleSet; }

		void dispose() {
			std::vector<std::reference_wrapper<RenderableObject>>::iterator it;
			for (it = m_Renderables.begin(); it != m_Renderables.end(); it++) {
				it->get().dispose();
			}

			m_RuleSet.dispose();
		}

	private:
		RenderingRuleSet m_RuleSet;
		std::vector<std::reference_wrapper<RenderableObject>> m_Renderables;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}