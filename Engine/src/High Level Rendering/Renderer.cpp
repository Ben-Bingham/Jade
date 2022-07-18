#include "High Level Rendering/Renderer.h"

namespace Jade{
	void Renderer::addRenderable(RenderableObject* renderable) {
		int count = 0;
		for (RenderingRuleSet* ruleSet : m_RuleSets) {
			if (renderable->followsRuleSet(*ruleSet)) {
				m_Renderables[count].push_back(renderable);
				return;
			}
			count++;
		}
		LOGGER.log("Renderer does not have a rule set that can support that renderable.", WARNING);
	}

	void Renderer::render(glm::vec3 cameraPos) {
		int count = 0;
		for (RenderingRuleSet* ruleSet : m_RuleSets) {
			ruleSet->bind();
			ruleSet->getProgram().setVector3f("cameraPosition", cameraPos);
			ruleSet->bindAdditionals();

			ruleSet->getProgram().setMatrix4f("view", m_View);
			ruleSet->getProgram().setMatrix4f("projection", m_Projection);

			std::vector<RenderableObject*>::iterator it;
			for (it = m_Renderables[count].begin(); it != m_Renderables[count].end(); ++it) {
				(*it)->render(*ruleSet);
			}
			count++;
		}
	}

	void Renderer::setMatrices(const glm::mat4& view, const glm::mat4& projection) {
		m_View = view;
		m_Projection = projection;
	}
}