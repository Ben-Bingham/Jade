#pragma once
#include <vector>

#include "RenderingRuleSet.h"
#include "RenderableObject.h"

namespace Jade {
	class Renderer {
	public:
		Renderer(const RenderingRuleSet& ruleSet) : m_RuleSet(ruleSet) {}

		void addRenderable(RenderableObject& renderable) {
			if (renderable.followsRuleSet(m_RuleSet)) {
				m_Renderables.push_back(renderable);
			}
		}

		void render() {
			m_RuleSet.bind();
		}

	private:
		RenderingRuleSet m_RuleSet;
		std::vector<RenderableObject> m_Renderables;
	};
}