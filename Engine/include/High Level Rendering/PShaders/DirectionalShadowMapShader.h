#pragma once

#include <vector>

#include "PShader.h"

namespace Jade {
	class DirectionalShadowMapShader : public PShader {
	public:
		DirectionalShadowMapShader() : PShader(DIRECTIONAL_SHADOW_MAP) {}

		void bindAdditionals() override {
			directionalLights[0].makeLightSpaceMatrix();
			getProgram().setMatrix4f("lightSpaceMatrix", directionalLights[0].lightSpaceMatrix);
		}
	};
}