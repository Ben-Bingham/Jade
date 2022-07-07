#pragma once

#include <vector>

#include "High Level Rendering/RenderingRuleSet.h"

namespace Jade {
	class StandardRuleSet : public RenderingRuleSet {
	public:
		StandardRuleSet() : RenderingRuleSet(STANDARD) {}

		void bindAdditionals() override {
			getProgram().setPointLights("lights", m_PointLights);
			getProgram().setFloat("numberOfLights", m_PointLights.size());
			getProgram().setDirectionalLight("directionalLight", m_DirectionalLight);
		}

		void addLight(const PointLight& light) {
			m_PointLights.push_back(light);
		}

		std::vector<PointLight> getPointLights() { return m_PointLights; }

	private:
		std::vector<PointLight> m_PointLights;
		DirectionalLight m_DirectionalLight;
	};
}