#pragma once

#include <vector>

#include "PShader.h"

namespace Jade {
	class ShadowMapShader : public PShader {
	public:
		ShadowMapShader() : PShader(SHADOW_MAP) {}

		void bindAdditionals() override {
			directionalLights[0].makeLightSpaceMatrix();
			getProgram().setMatrix4f("lightSpaceMatrix", directionalLights[0].lightSpaceMatrix);
		}
	};
}