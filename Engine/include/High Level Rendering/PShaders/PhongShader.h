#pragma once

#include <vector>

#include "PShader.h"

namespace Jade {
	class PhongShader : public PShader {
	public:
		PhongShader() : PShader(PHONG)  {}

		void bindAdditionals() override {
#ifdef JADE_DEBUG
			if (pointLights.size() == 0 && directionalLights.size() == 0) {
				LOG("No lights are active, scene will be dark.", WARNING);
			}
#endif // JADE_DEBUG

			getProgram().setPointLights("pointLights", pointLights);
			getProgram().setDirectionalLights("directionalLights", directionalLights);
		}

	private:
	};
}