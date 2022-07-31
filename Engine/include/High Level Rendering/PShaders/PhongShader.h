#pragma once

#include <vector>

#include "PShader.h"
#include "Low Level Rendering/Shaders/ShaderStructs.h"

namespace Jade {
	class PhongShader : public PShader {
	public:
		PhongShader() : PShader(PHONG)  {}

		void bindAdditionals() override {
			getProgram().setPointLights("pointLights", pointLights);
			getProgram().setDirectionalLights("directionalLights", directionalLights);
		}

	private:
	};
}