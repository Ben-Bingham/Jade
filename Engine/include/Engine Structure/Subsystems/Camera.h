#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine Structure/Subsystems/Subsystem.h"
#include "Entity Component System/Gameobjects/Gameobject.h"

namespace Jade {
	struct CameraInfo {
		float* fov;
		glm::vec3* position;
	};

	class Camera : public Gameobject {
	public:
		Camera(float fov = 45.0f, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 getViewMatrix() { 
			recalculateViewMatrix();
			return m_ViewMatrix;
		}

		float getFOV() { return m_FOV; }

		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;

		void updateCameraVectors() {
			right = glm::normalize(glm::cross(front, m_WorldUp));
			up = glm::normalize(glm::cross(right, front));
		}

	private:
		float m_FOV;

		glm::mat4 m_ViewMatrix;

		glm::vec3 m_WorldUp;

		void recalculateViewMatrix() {
			Transform* transform = getComponent<Transform>();
			m_ViewMatrix = glm::lookAt(transform->position, transform->position + front, up);
		}
	};
}