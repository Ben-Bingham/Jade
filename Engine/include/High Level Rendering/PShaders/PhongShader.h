#pragma once

#include <vector>

#include "PShader.h"

namespace Jade {
	class PhongShader : public PShader {
	public:
		PhongShader() : 
			PShader("..\\Engine\\assets\\shaders\\PhongRuleSet.vert", "..\\Engine\\assets\\shaders\\PhongRuleSet.frag") {}

		void uploadUniforms() override;

		void clearLights() {
			m_Lights.clear();
		}

		void setLights(std::vector<std::shared_ptr<Light>> lights) {
			m_Lights = std::move(lights);
		}

	private:
		std::vector<std::shared_ptr<Light>> m_Lights;
	};
}