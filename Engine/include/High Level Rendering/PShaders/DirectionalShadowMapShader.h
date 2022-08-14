#pragma once

#include <vector>

#include "PShader.h"

namespace Jade {
	class DirectionalShadowMapShader : public PShader {
	public:
		DirectionalShadowMapShader() 
			: PShader("..\\Engine\\assets\\shaders\\DirectionalDepthShader.vert", "..\\Engine\\assets\\shaders\\DirectionalDepthShader.frag") {}

		void uploadUniforms() override {
			bind();

			if (dirLight != nullptr) {
				dirLight->makeLightSpaceMatrix();
				getProgram().setMatrix4f("lightSpaceMatrix", dirLight->lightSpaceMatrix);
			}	
		}

		void setLight(const DirectionalLight& light) { dirLight = std::make_shared<DirectionalLight>(light); }

	private:
		std::shared_ptr<DirectionalLight> dirLight{ nullptr };
	};
}