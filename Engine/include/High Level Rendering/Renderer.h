#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "RenderingRuleSet.h"
#include "RenderableObject.h"

namespace Jade {
	class Renderer {
	public:
		Renderer(const RenderingRuleSet& ruleSet, glm::mat4& viewMatrix, glm::mat4& projectionMatrix) 
			: m_RuleSet(ruleSet), m_View(viewMatrix), m_Projection(projectionMatrix) { }

		void addRenderable(RenderableObject& renderable) {
			if (renderable.followsRuleSet(m_RuleSet)) {
				m_Renderables.push_back(renderable);
			}
		}

		void render() {
			m_RuleSet.bind();
			m_RuleSet.getProgram().setMatrix4f("view", m_View);				//upload view and projection matrixs
			m_RuleSet.getProgram().setMatrix4f("projection", m_Projection);
			
			//upload any additional data needed for ruleset like lights
			std::vector<RenderableObject>::iterator it;
			for (it = m_Renderables.begin(); it != m_Renderables.end(); it++) {
				it->render(m_RuleSet);
			}
			//for each renderalbe {
			//	render
			//}
			//
			//
			//
		}

	private:
		RenderingRuleSet m_RuleSet;
		std::vector<RenderableObject> m_Renderables;
		glm::mat4& m_View;
		glm::mat4& m_Projection;
	};
}