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

		void addLight(const PointLight& light) {
			m_PointLights.push_back(light);
		}

		std::vector<Light> getLights() { return m_Lights; }

	private:
		std::vector<Light> m_Lights;
	};
}