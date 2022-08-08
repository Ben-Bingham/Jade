#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Entity Component System/Components/Component.h"

namespace Jade {
	class Gameobject;

	class Transform : public Component {
	public:
		Transform() {}

		glm::vec3 position{ 0.0f };
		glm::vec3 scale{ 1.0f };
		glm::quat rotation{ 0.0f, 0.0f, 0.0f, 0.0f};

		Transform& Translate(const glm::vec3& vector);
		Transform& Translate(float x, float y, float z);

		Transform& Scale(const glm::vec3& vector);
		Transform& Scale(float x, float y, float z);
		Transform& Scale(float scaler);

		Transform& Rotate(const glm::quat& quat);
		Transform& Rotate(glm::vec4& vector);
		Transform& Rotate(float x, float y, float z, float w);
		Transform& Rotate(glm::vec3& vector, float angle);

	private:
		float minOf1(float val) {
			if (val == 0.0f) {
				return 1.0f;
			}
		}
	};
}