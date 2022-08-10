#pragma once
#include "Light.h"
#include "High Level Rendering/Colour.h"
#include "Low Level Rendering/Rendering Objects/Cubemap.h"
#include "Low Level Rendering/Rendering Objects/FrameBufferObject.h"

namespace Jade {
	class PointLight : public Light {
	public:
		PointLight(
			Colour Ambient = Colour{0.2f},
			Colour Diffuse = Colour{0.5f},
			Colour Specular = Colour{1.0f},
			float Constant = 1.0f,
			float Linear = 0.09,
			float Quadratic = 0.032
		) : constant(Constant), linear(Linear), quadratic(Quadratic), ambient(Ambient), diffuse(Diffuse), specular(Specular) { }

		void makeLightSpaceMatricies() {
			float aspect = (float)textureSizes.x / (float)textureSizes.y;
			float near = 1.0f;

			glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, near, farPlane);

			glm::vec3 position = getComponent<Transform>()->position;
			lightSpaceMatricies.clear();
			lightSpaceMatricies.push_back(projection * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
			lightSpaceMatricies.push_back(projection * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
			lightSpaceMatricies.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
			lightSpaceMatricies.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
			lightSpaceMatricies.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
			lightSpaceMatricies.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
		}

		bool operator==(const PointLight& other) const {
			return linear == other.linear && quadratic == other.quadratic && constant == other.constant && ambient == other.ambient && diffuse == other.diffuse && specular == other.specular;
		}

		bool operator!=(const PointLight& other) const {
			return !operator==(other);
		}

		glm::vec2 textureSizes{ 1024, 1024 };

		Cubemap shadowMap{ (int)textureSizes.x, (int)textureSizes.y, GL_DEPTH_COMPONENT };
		FrameBufferObject shadowFBO{ shadowMap };

		std::vector<glm::mat4> lightSpaceMatricies;

		float constant{};
		float linear{};
		float quadratic{};

		Colour ambient{};
		Colour diffuse{};
		Colour specular{};

		float farPlane = 25.0f;
	};
}