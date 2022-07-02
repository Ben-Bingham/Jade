#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

namespace Jade {
	class GameObject;
	class Component; //TODO

	struct Rotation {
		glm::vec3 vector;
		float angle;

		Rotation(glm::vec3 vec, float ang) : vector(vec), angle(ang) {}
	};

	class Transform {
	public:
		Transform(GameObject& gameobject) : m_Position(0.0f), m_Scale(1.0f), m_Rotation(glm::vec3(0.0f), 0.0f) {
			calculateModelMatrix();
		}

		glm::mat4 getModelMatrix() { return m_ModelMatrix; }

		glm::vec3 getPosition() { return m_Position; }
		glm::vec3 getScale() { return m_Scale; }
		Rotation getRotation() { return m_Rotation; }

		void setPositon(glm::vec3 position) { m_Position = position; calculateModelMatrix(); }
		void setScale(glm::vec3 scale) { m_Scale = scale; calculateModelMatrix(); }
		void setRotation(Rotation rotation) { m_Rotation = rotation; calculateModelMatrix(); }

	private:
		glm::mat4 m_ModelMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		Rotation m_Rotation;

		void calculateModelMatrix() {
			m_ModelMatrix = glm::mat4(1.0f);
			m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.angle), m_Rotation.vector);
			m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
			m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
		}
	};
}