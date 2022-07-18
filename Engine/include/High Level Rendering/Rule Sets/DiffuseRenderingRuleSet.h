#pragma once

#include "High Level Rendering/Rule Sets/RenderingRuleSet.h"
#include "High Level Rendering/LightCreator.h"

namespace Jade {
	class DiffuseRuleSet : public RenderingRuleSet {
	public:
		DiffuseRuleSet() : RenderingRuleSet(DIFFUSE), m_DirectionalLight(LightCreator::DefaultDirectionalLight()) {}

		void bindAdditionals() override {
			getProgram().setPointLights("lights", m_PointLights);
			getProgram().setDirectionalLight("directionalLight", m_DirectionalLight);
		}

		void addPointLight(const PointLight& light) {
			m_PointLights.push_back(light);
		}

		void setDirectionalLight(const DirectionalLight& light) {
			m_DirectionalLight = light;
		}

		std::vector<PointLight> getPointLights() { return m_PointLights; }

	private:
		std::vector<PointLight> m_PointLights;
		DirectionalLight m_DirectionalLight;
	};
}