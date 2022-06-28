#pragma once

#include <glm/glm.hpp>

#include "Component.h"

namespace Jade {
	class GameObject;
	class Component;

	class Transform : public Component {
	public:
		Transform(GameObject gameobject) : Component(gameobject) {}

		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);
		glm::vec3 rotation = glm::vec3(1.0f);
	};
}