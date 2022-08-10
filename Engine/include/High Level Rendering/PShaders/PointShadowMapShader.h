#pragma once

#include "PShader.h"

namespace Jade {
	class PointShadowMapShader : public PShader {
	public:
		PointShadowMapShader() : PShader(POINT_SHADOW_MAP) {}

		void bindAdditionals() override {
			if (pointLights.size() != 0) {
				pointLights[0].makeLightSpaceMatricies();
				getProgram().setMatrix4fs("shadowMatrices", pointLights[0].lightSpaceMatricies);

				getProgram().setFloat("far_plane", pointLights[0].farPlane);
				getProgram().setVector3f("lightPos", pointLights[0].getComponent<Transform>()->position);
			}
		}
	};
}