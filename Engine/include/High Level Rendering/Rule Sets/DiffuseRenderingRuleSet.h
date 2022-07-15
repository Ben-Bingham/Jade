#pragma once

#include "High Level Rendering/Rule Sets/RenderingRuleSet.h"
#include "High Level Rendering/LightCreator.h"
#include "Core Systems/Logging/OpenGLErrors.h"

namespace Jade {
	class DiffuseRuleSet : public RenderingRuleSet {
	public:
		DiffuseRuleSet() : RenderingRuleSet(DIFFUSE), m_DirectionalLight(LightCreator::DefaultDirectionalLight()) {}

		void bindAdditionals() override {
			getProgram().setPointLights("lights", m_PointLights);
			glCheckError();
			getProgram().setFloat("numberOfLights", (float)m_PointLights.size());
			glCheckError();
			getProgram().setDirectionalLight("directionalLight", m_DirectionalLight);
			glCheckError();
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