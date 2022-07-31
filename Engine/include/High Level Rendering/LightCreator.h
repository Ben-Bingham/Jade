#pragma once

#include <glm/glm.hpp>

#include "Low Level Rendering/Shaders/ShaderStructs.h"

namespace Jade {
	class LightCreator {
	public:

		static DirectionalLight DefaultDirectionalLight() {
			return DirectionalLight {
				glm::vec3(-0.2f, -1.0f, -0.3f),	// Direction

				glm::vec3(0.2f, 0.2f, 0.2f),	// Ambient
				glm::vec3(0.5f, 0.5f, 0.5f),	// Diffuse
				glm::vec3(1.0f, 1.0f, 1.0f)		// Specular
			};
		}
	};
}