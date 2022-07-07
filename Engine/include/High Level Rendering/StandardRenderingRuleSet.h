#pragma once

#include <vector>

#include "High Level Rendering/RenderingRuleSet.h"

namespace Jade {
	class StandardRuleSet : public RenderingRuleSet {
	public:
		StandardRuleSet() : RenderingRuleSet(STANDARD) {}

		void bindAdditionals() override {
			getProgram().setLights("lights", m_Lights);
			getProgram().setFloat("numberOfLights", m_Lights.size());
		}

		void addLight(const Light& light) {
			if (ruleSet == STANDARD || ruleSet == TEXTURE) {
				m_Lights.push_back(light);
			}
			else {
				std::string message = "The rule set with ID: ";
				message += std::to_string(getID());
				message += "does not support lights.";
				LOGGER.log(message, Jade::WARNING);
			}
		}

		std::vector<Light> getLights() { return m_Lights; }

	private:
		std::vector<Light> m_Lights;
	};
}