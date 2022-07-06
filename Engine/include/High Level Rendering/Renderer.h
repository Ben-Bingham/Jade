#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "RenderingRuleSet.h"
#include "RenderableObject.h"

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
			/*LOGGER.log(glm::to_string(m_View), INFO);
			LOGGER.log(glm::to_string(m_Projection), INFO);*/
			m_RuleSet.getProgram().setMatrix4f("view", m_View);
			m_RuleSet.getProgram().setMatrix4f("projection", m_Projection);
			
			//upload any additional data needed for ruleset like lights TODO
			std::vector<RenderableObject>::iterator it;
			for (it = m_Renderables.begin(); it != m_Renderables.end(); it++) {
				it->render(m_RuleSet);
			}
		}

		void setMatrices(const glm::mat4& view, const glm::mat4& projection) {
			m_View = view;
			m_Projection = projection;
		}

	private:
		RenderingRuleSet m_RuleSet;
		std::vector<RenderableObject> m_Renderables;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}