#pragma once

#include "Low Level Rendering/Shaders/ShaderStructs.h"

namespace Jade {
	class MaterialCreator {
	public:
		static Material DefaultMaterial() {
			return Material{
				glm::vec3(1.0f, 0.5f, 0.31f), // Ambient  
				glm::vec3(1.0f, 0.5f, 0.31f), // Diffuse  
				glm::vec3(0.5f, 0.5f, 0.5f),  // Specular 

				32.0f						  // Shininess
			};
		}
	};
}