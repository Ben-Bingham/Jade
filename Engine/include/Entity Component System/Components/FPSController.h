#pragma once
#include "Entity Component System/Component.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void scrollCallback(int xoffset, int yoffset, void* data);

	class FPSController : public Component{
	public:
		FPSController() {}

		float cameraSpeed = 0.4f;
		float mouseSensitivity = 0.1f;

		int lastX = gWindow.getWidth();
		int lastY = gWindow.getHeight();

		int lastScrollOffset = 0;

		float yaw = 45.0f;
		float pitch = 0.0f;

		bool mouseHasMoved = false;

		void Begin() override {
			gMouse.addScrollCallback(scrollCallback, (void*)this);
		}

		void Update() override {
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

			if (gKeyboard.KEY_W) { //TODO delta time
				gCamera.getTransform().position += gCamera.front * cameraSpeed;
			}

			if (gKeyboard.KEY_A) {
				gCamera.getTransform().position -= gCamera.right * cameraSpeed;
			}

			if (gKeyboard.KEY_S) {
				gCamera.getTransform().position -= gCamera.front * cameraSpeed;
			}

			if (gKeyboard.KEY_D) {
				gCamera.getTransform().position += gCamera.right * cameraSpeed;
			}

			if (gKeyboard.KEY_SPACE) {
				gCamera.getTransform().position += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
			}

			if (gKeyboard.KEY_LEFT_SHIFT) {
				gCamera.getTransform().position -= glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
			}

			gCamera.updateCameraVectors();
		}
	};

	void scrollCallback(int xoffset, int yoffset, void* data) {
		FPSController* controller = (FPSController*)data;
		controller->cameraSpeed += yoffset * 0.01f; //TODO delta time

		if (controller->cameraSpeed < 0) {
			controller->cameraSpeed = 0;
		}
	}
}