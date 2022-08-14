#pragma once

#include "PShader.h"

namespace Jade {
	class PointShadowMapShader : public PShader {
	public:
		PointShadowMapShader() 
			: PShader("..\\Engine\\assets\\shaders\\PointDepthShader.vert", "..\\Engine\\assets\\shaders\\PointDepthShader.geom", "..\\Engine\\assets\\shaders\\PointDepthShader.frag") {}

		void uploadUniforms() override {
			bind();

			if (pointLight != nullptr) {
				pointLight->makeLightSpaceMatricies();
				getProgram().setMatrix4fs("shadowMatrices", pointLight->lightSpaceMatricies);

				getProgram().setFloat("far_plane", pointLight->farPlane);
				getProgram().setVector3f("lightPos", pointLight->getComponent<Transform>()->position);
			}
		}

		void setLight(const PointLight& light) { pointLight = std::make_shared<PointLight>(light); }

	private:
		std::shared_ptr<PointLight> pointLight{ nullptr }; //TODO consider making just a normal variable that is not a pointer
	};
}