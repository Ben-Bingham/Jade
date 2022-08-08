#include <vector>

#include "Entity Component System/Components/Transform.h"
#include "Entity Component System/Gameobjects/Gameobject.h"

namespace Jade {
	Transform& Transform::Translate(const glm::vec3& vector) {
		position += vector;

		auto val = getGameobject();
		auto val2 = getGameobject().getChildren();

		std::vector<std::shared_ptr<Gameobject>> children = getGameobject().getChildren();
		for (std::shared_ptr<Gameobject> child : children) {
			Transform* transfrom = child->getComponent<Transform>();
			if (transfrom != nullptr) {
				transfrom->Translate(vector);
			}
		}

		return *this;
	}

	Transform& Transform::Translate(float x, float y, float z) {
		return Translate(glm::vec3(x, y, z));
	}

	Transform& Transform::Scale(const glm::vec3& vector) {
		glm::vec3 vec{ minOf1(vector.x), minOf1(vector.y), minOf1(vector.z) };
		scale *= vector;

		std::vector<std::shared_ptr<Gameobject>> children = getGameobject().getChildren();
		for (std::shared_ptr<Gameobject> child : children) {
			Transform* transfrom = child->getComponent<Transform>();
			if (transfrom != nullptr) {
				transfrom->Scale(vector);
			}
		}

		return *this;
	}

	Transform& Transform::Scale(float x, float y, float z) {
		return Scale(glm::vec3(minOf1(x), minOf1(y), minOf1(z)));
	}

	Transform& Transform::Scale(float scaler) {
		return Scale(minOf1(scaler), minOf1(scaler), minOf1(scaler));
	}

	Transform& Transform::Rotate(const glm::quat& quat) {
		rotation += quat;
		return *this;
	}

	Transform& Transform::Rotate(glm::vec4& vector) {
		rotation += glm::quat(vector);
		return *this;
	}

	Transform& Transform::Rotate(float x, float y, float z, float w) {
		rotation += glm::quat(x, y, z, w);
		return *this;
	}

	Transform& Transform::Rotate(glm::vec3& vector, float angle) {
		glm::vec3 normalized = glm::normalize(vector);
		rotation += glm::quat(
			cos(glm::radians(angle / 2.0f)), 
			sin(glm::radians(angle / 2.0f)) * normalized.x,
			sin(glm::radians(angle / 2.0f)) * normalized.y,
			sin(glm::radians(angle / 2.0f)) * normalized.z
		);
		return *this;
	}
}