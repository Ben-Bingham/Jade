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
		Transform() 
			: position(glm::vec3(0.0f, 0.0f, 0.0f)),
			scale(glm::vec3(1.0f, 1.0f, 1.0f)),
			rotation{ glm::vec3(1.0f, 1.0f, 1.0f), 0.0f },
			m_Model(glm::mat4(1.0f)) {}

		void calculateModelMatrix() {
			m_Model = glm::mat4(1.0);
			m_Model = glm::rotate(m_Model, glm::radians(rotation.angle), rotation.vector);
			m_Model = glm::translate(m_Model, position);
			m_Model = glm::scale(m_Model, scale);
		}

		void rotate(Rotation& rotation) {
			m_Model = glm::rotate(m_Model, glm::radians(rotation.angle), rotation.vector);
		}

		void clearMatrix() { m_Model = glm::mat4(1.0f); }

		void reset() {
			clearMatrix();
			position = glm::vec3(0.0f, 0.0f, 0.0f);
			scale = glm::vec3(1.0f, 1.0f, 1.0f);
			rotation = { glm::vec3(0.0f, 0.0f, 0.0f), 0.0f };
		}

		glm::mat4 getMatrix() const { return m_Model; }

		glm::vec3 position;
		glm::vec3 scale;
		Rotation rotation;

	private:
		glm::mat4 m_Model;
	};
}