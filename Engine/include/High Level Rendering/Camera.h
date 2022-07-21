#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "High Level Rendering/Transform.h"

namespace Jade {
	enum MovementDirection {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	class Camera { //TODO make the camera class extend the future GameObject class
	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = defaultYaw, float pitch = defaultPitch) 
			: m_WorldUp(worldUp), m_Speed(defaultSpeed), m_Yaw(yaw), m_Pitch(pitch), m_Sensitivity(defaultMouseSens), m_FOV(defaultFOV) {

			updateCameraVectors();
		}

		glm::mat4 getViewMatrix() { 
			recalculateViewMatrix();
			return m_ViewMatrix;
		}

		glm::mat4& getViewMatrixReference() {
			recalculateViewMatrix();
			return m_ViewMatrix;
		}

		float getFOV() { return m_FOV; }

		Transform& getTransform() { return m_Transform; }

		static constexpr float defaultSpeed = 2.5f;
		static constexpr float defaultYaw = -90.0f;
		static constexpr float defaultPitch = 0.0f;
		static constexpr float defaultMouseSens = 0.1f;
		static constexpr float defaultFOV = 45.0f;

	private:
		Transform m_Transform;

		float m_Speed;
		float m_Yaw;
		float m_Pitch;
		float m_Sensitivity;
		float m_FOV;

		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;

		void updateCameraVectors() {
			glm::vec3 front;
			front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
			front.y = sin(glm::radians(m_Pitch));
			front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
			m_Front = glm::normalize(front);

			m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
			m_Up = glm::normalize(glm::cross(m_Right, m_Front));
		}

		void recalculateViewMatrix() {
			m_ViewMatrix = glm::lookAt(m_Transform.position, m_Transform.position + m_Front, m_Up);
		}
	};
}