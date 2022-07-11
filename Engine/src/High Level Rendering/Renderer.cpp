#include "High Level Rendering/Renderer.h"

namespace Jade{
	void Renderer::addRenderable(RenderableObject* renderable) {
		if (renderable->followsRuleSet(*m_RuleSet)) {
			m_Renderables.push_back(renderable);
		}
		else {
			LOGGER.log("Renderable did not follow rule set", WARNING);
		}
	}

	void Renderer::render() {
		m_RuleSet->bind();

		m_RuleSet->getProgram().setMatrix4f("view", m_View);
		m_RuleSet->getProgram().setMatrix4f("projection", m_Projection);

		std::vector<RenderableObject*>::iterator it;
		for (it = m_Renderables.begin(); it != m_Renderables.end(); it++) {
			(*it)->render(*m_RuleSet);
		}
	}

	void Renderer::setMatrices(const glm::mat4& view, const glm::mat4& projection) {
		m_View = view;
		m_Projection = projection;
	}
}