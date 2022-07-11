#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Rule Sets/RenderingRuleSet.h"
#include "High Level Rendering/Renderable Objects/RenderableObject.h"
#include "Core Systems/Logging/OpenGLErrors.h"

namespace Jade {
	class Renderer {
	public:
		Renderer(RenderingRuleSet* ruleSet)
			: m_RuleSet(ruleSet), m_View(glm::mat4(1.0f)), m_Projection(glm::mat4(1.0f)) {}

		void addRenderable(RenderableObject* renderable);

		void render();

		void setMatrices(const glm::mat4& view, const glm::mat4& projection);

		RenderingRuleSet* getRuleSet() const { return m_RuleSet; }

		void dispose() {
			std::vector<RenderableObject*>::iterator it;
			for (it = m_Renderables.begin(); it != m_Renderables.end(); it++) {
				(*it)->dispose();
			}

			m_RuleSet->dispose();
		}

	private:
		RenderingRuleSet* m_RuleSet;
		std::vector<RenderableObject*> m_Renderables;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}