#pragma once
#include "Entity Component System/Components/Component.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void scrollCallback(int xoffset, int yoffset, void* data);

	class FPSController : public Component{
	public:
		FPSController() {}

		float cameraSpeed = 10.0f;
		float mouseSensitivity = 0.1f;

		int lastX = gWindow.getWidth();
		int lastY = gWindow.getHeight();

		int lastScrollOffset = 0;

		float yaw = -90.0f;
		float pitch = 0.0f;

		bool firstMouse = true;

		void Begin() override {
			gMouse.addScrollCallback(scrollCallback, (void*)this);
		}

		void Update() override {
			if (firstMouse) {
				lastX = gMouse.xPosition;
				lastY = gMouse.yPosition;
				firstMouse = false;
			}

			float xOffset = (float)(gMouse.xPosition - lastX);
			float yOffset = (float)(lastY - gMouse.yPosition);
			lastX = gMouse.xPosition;
			lastY = gMouse.yPosition;

			xOffset *= mouseSensitivity;
			yOffset *= mouseSensitivity;

			yaw += xOffset;
			pitch += yOffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

			gCamera.front = glm::vec3(0.0f);
			gCamera.front = glm::normalize(direction);

			float velocity = cameraSpeed * (float)gTime.deltaTime;

			if (gKeyboard.KEY_W) {
				gCamera.getTransform().position += gCamera.front * velocity;
			}

			if (gKeyboard.KEY_A) {
				gCamera.getTransform().position -= gCamera.right * velocity;
			}

			if (gKeyboard.KEY_S) {
				gCamera.getTransform().position -= gCamera.front * velocity;
			}

			if (gKeyboard.KEY_D) {
				gCamera.getTransform().position += gCamera.right * velocity;
			}

			if (gKeyboard.KEY_SPACE) {
				gCamera.getTransform().position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
			}

			if (gKeyboard.KEY_LEFT_SHIFT) {
				gCamera.getTransform().position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
			}

			gCamera.updateCameraVectors();
		}
	};

	void scrollCallback(int xoffset, int yoffset, void* data) {
		FPSController* controller = (FPSController*)data;
		controller->cameraSpeed += yoffset * (float)gTime.deltaTime * 10;

		if (controller->cameraSpeed < 0) {
			controller->cameraSpeed = 0;
		}
	}
}