#pragma once

#include <vector>

#include "PShader.h"

namespace Jade {
	class PhongShader : public PShader {
	public:
		PhongShader() : PShader(PHONG) {}

		void bindAdditionals() override;
	};
}