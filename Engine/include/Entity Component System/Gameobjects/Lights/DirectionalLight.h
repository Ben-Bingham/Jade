#pragma once
#include "Light.h"
#include "High Level Rendering/Colour.h"

namespace Jade {
	class DirectionalLight : public Light {
	public:
		DirectionalLight(
			glm::vec3 Direction = glm::vec3(0.0f, -1.0f, 0.0f),
			Colour Ambient = Colour{ 0.2f },
			Colour Diffuse = Colour{ 0.5f },
			Colour Specular = Colour{ 1.0f }
		) : ambient(Ambient), diffuse(Diffuse), specular(Specular), direction(Direction) {
		}

		bool operator==(const DirectionalLight& other) const {
			return direction == other.direction && ambient == other.ambient && diffuse == other.diffuse && specular == other.specular;
		}

		bool operator!=(const DirectionalLight& other) const {
			return !operator==(other);
		}

		glm::vec3 direction{};

		Colour ambient{};
		Colour diffuse{};
		Colour specular{};
	};
}