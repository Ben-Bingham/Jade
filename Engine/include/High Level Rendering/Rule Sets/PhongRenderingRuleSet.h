#pragma once

#include <vector>

#include "RenderingRuleSet.h"
#include "Low Level Rendering/Shaders/ShaderStructs.h"

namespace Jade {
	class PhongRuleSet : public RenderingRuleSet{
	public:
		PhongRuleSet() : RenderingRuleSet(PHONG)  {}

		void bindAdditionals() override {
			getProgram().setPointLights("pointLights", m_PointLights);
			getProgram().setDirectionalLights("directionalLights", m_DirectionalLights);
		}

		void addPointLight(const PointLight& light) {
			m_PointLights.push_back(light);
		}

		void addDirectionalLight(const DirectionalLight& light) {
			m_DirectionalLights.push_back(light);
		}

	private:
		std::vector<PointLight> m_PointLights;
		std::vector<DirectionalLight> m_DirectionalLights;
	};
}