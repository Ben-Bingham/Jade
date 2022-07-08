#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Rule Sets/RenderingRuleSet.h"
#include "RenderableObject.h"
#include "Core Systems/Logging/OpenGLErrors.h"

namespace Jade {
	class Renderer {
	public:
		Renderer(RenderingRuleSet* ruleSet, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
			: m_RuleSet(ruleSet), m_View(viewMatrix), m_Projection(projectionMatrix) { }

		void addRenderable(RenderableObject& renderable) {
			if (renderable.followsRuleSet(*m_RuleSet)) {
				m_Renderables.push_back(renderable);
			}
			else {
				LOGGER.log("Renderable did not follow rule set", WARNING);
			}
		}

		void render() {
			m_RuleSet->bind();

			m_RuleSet->getProgram().setMatrix4f("view", m_View);
			m_RuleSet->getProgram().setMatrix4f("projection", m_Projection);

			std::vector<std::reference_wrapper<RenderableObject>>::iterator it;
			for (it = m_Renderables.begin(); it != m_Renderables.end(); it++) {
				it->get().render(*m_RuleSet);
			}
		}

		void setMatrices(const glm::mat4& view, const glm::mat4& projection) {
			m_View = view;
			m_Projection = projection;
		}

		RenderingRuleSet* getRuleSet() const { return m_RuleSet; }

		void dispose() {
			std::vector<std::reference_wrapper<RenderableObject>>::iterator it;
			for (it = m_Renderables.begin(); it != m_Renderables.end(); it++) {
				it->get().dispose();
			}

			m_RuleSet->dispose();
		}

	private:
		RenderingRuleSet* m_RuleSet;
		std::vector<std::reference_wrapper<RenderableObject>> m_Renderables;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}