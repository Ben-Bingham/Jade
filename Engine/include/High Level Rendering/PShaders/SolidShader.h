#pragma once

#include "PShader.h"

namespace Jade {
	class SolidShader : public PShader {
	public:
		SolidShader() : PShader("..\\Engine\\assets\\shaders\\SolidRuleSet.vert", "..\\Engine\\assets\\shaders\\SolidRuleSet.frag") {}

		void uploadUniforms() override{}
	};
}