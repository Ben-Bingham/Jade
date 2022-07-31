#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Entity Component System/Components/Component.h"

namespace Jade {
	class Transform : public Component {
	public:
		Transform() {}

		glm::vec3 position{ 0.0f };
		glm::vec3 scale{ 1.0f };
		glm::quat rotation{ }; //TODO figure out how this works

	private:
	};
}