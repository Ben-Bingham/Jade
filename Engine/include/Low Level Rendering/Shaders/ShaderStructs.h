#pragma once

#include "glm/glm.hpp"

namespace Jade {
	struct Light {
		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct Material {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
}