#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Jade {
	struct Rotation {
		glm::vec3 vector;
		float angle;
	};

	class Transform {
	public:
		Transform() : m_Position(0.0f), m_Scale(1.0f), m_Rotation{ glm::vec3(0.0f), 0.0f }, m_Model(1.0f) {}

		void calculateModelMatrix() {
			m_Model = glm::mat4(1.0);
			m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.angle), m_Rotation.vector);
			m_Model = glm::translate(m_Model, m_Position);
			m_Model = glm::scale(m_Model, m_Scale);
		}

		void rotate(Rotation& rotation) {
			m_Model = glm::rotate(m_Model, glm::radians(rotation.angle), rotation.vector);
		}

		void translate(glm::vec3& vector) {
			m_Position += vector;
			m_Model = glm::translate(m_Model, m_Position);
		}

		void scale(glm::vec3& vector) {
			m_Scale += vector;
			m_Model = glm::scale(m_Model, m_Scale);
		}

		void clearMatrix() { m_Model = glm::mat4(1.0f); }

		void reset() {
			clearMatrix();
			m_Position = glm::vec3(0.0f);
			m_Scale = glm::vec3(1.0f);
			m_Rotation = { glm::vec3(0.0f), 0.0f };
		}

		glm::mat4 getMatrix() { return m_Model; }

	private:

		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		Rotation m_Rotation;

		glm::mat4 m_Model;
	};
}