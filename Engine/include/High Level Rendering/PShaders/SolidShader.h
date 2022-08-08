#pragma once

#include "PShader.h"

namespace Jade {
	class SolidShader : public PShader {
	public:
		SolidShader() : PShader(SOLID_COLOUR) {}

		void bindAdditionals() override{}
	};
}