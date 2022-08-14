#pragma once
#include "High Level Rendering/PShaders/PShader.h"

namespace Jade {
	class SkyboxShader : public PShader {
	public:
		SkyboxShader() : PShader("..\\Engine\\assets\\shaders\\SkyboxShader.vert", "..\\Engine\\assets\\shaders\\SkyboxShader.frag") {}

		void uploadUniforms() override {}
	};
}