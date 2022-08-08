#pragma once
#include "Light.h"
#include "High Level Rendering/Colour.h"
#include "Core Systems/Logging/OpenGLErrors.h"
#include "Low Level Rendering/Rendering Objects/FrameBufferObject.h"

namespace Jade {
	class DirectionalLight : public Light {
	public:
		DirectionalLight(
			glm::vec3 Direction = glm::vec3(1.0f, 1.0f, 0.0f),
			Colour Ambient = Colour{ 0.2f },
			Colour Diffuse = Colour{ 0.5f },
			Colour Specular = Colour{ 1.0f }
		) : ambient(Ambient), diffuse(Diffuse), specular(Specular), direction(Direction), shadowMap(GL_DEPTH_COMPONENT, (int)shadowMapSize.x, (int)shadowMapSize.y) {

			shadowMap.setBorderColour(Colour{ 1.0f, 1.0f, 1.0f });

			FrameBufferObject::unbind();
		}

		void makeLightSpaceMatrix() {
			float near_plane = 1.0f, far_plane = 14.0f;
			glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

			glm::mat4 lightView = glm::lookAt(getComponent<Transform>()->position,
				glm::vec3(direction - getComponent<Transform>()->position),
				glm::vec3(0.0f, 1.0f, 0.0f));

			lightSpaceMatrix = lightProjection * lightView;
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
		glm::vec2 shadowMapSize{ 1024, 1024 };

		Texture shadowMap;

		FrameBufferObject depthFBO{ shadowMap };

		glm::mat4 lightSpaceMatrix{ 1.0f };
	};
}