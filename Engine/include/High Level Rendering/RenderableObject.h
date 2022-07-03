#pragma once
#include <vector>

#include "RenderingRuleSet.h"

namespace Jade {
	class RenderableObject {
	public:
		RenderableObject() {}

		bool followsRuleSet(RenderingRuleSet& ruleSet) {
			//if this object contains at least all all the required rules in the rule set
		}

		void render() {
			// bind VAO
			// upload custom uniforms such as colour
			// call the draw function
		}

	private:
		std::vector<RenderingRule> m_RenderingRules;
		// VAO
		// VBO
		// EBO //TODO
		// Possibly textures
	};
}