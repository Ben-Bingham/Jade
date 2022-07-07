#pragma once

#include <glm/glm.hpp>

#include "Low Level Rendering/Shaders/ShaderStructs.h"

namespace Jade {
	class LightCreator {
	public:
		static PointLight DefaultPointLight() {
			return PointLight {
				glm::vec3(0.0f, 0.0f, 0.0f), // Position

				1.0f,						 // Constant
				0.09f,						 // Linear
				0.32f,						 // Quadratic

				glm::vec3(0.2f, 0.2f, 0.2f), // Ambient
				glm::vec3(0.5f, 0.5f, 0.5f), // Diffuse
				glm::vec3(1.0f, 1.0f, 1.0f)  // Specular
			};
		}

		static DirectionalLight DefaultDirectionalLight() {
			return DirectionalLight{
				glm::vec3(-0.2f, -1.0f, -0.3f),	// Direction

				glm::vec3(0.2f, 0.2f, 0.2f),	// Ambient
				glm::vec3(0.2f, 0.2f, 0.2f),	// Diffuse
				glm::vec3(1.0f, 1.0f, 1.0f)		// Specular
			};
		}
	};
}