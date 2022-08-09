#pragma once
#include "High Level Rendering/PShaders/PShader.h"

namespace Jade {
	class SkyboxShader : public PShader {
	public:
		SkyboxShader() : PShader(SKYBOX) {}

		void bindAdditionals() override {}
	};
}