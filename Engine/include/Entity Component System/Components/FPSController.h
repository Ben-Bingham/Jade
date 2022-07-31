#pragma once
#include "Entity Component System/Components/Component.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void scrollCallback(int xoffset, int yoffset, void* data);
	void mousePositionCallback(int xpos, int ypos, void* data);

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
			gMouse.addMousePositionCallback(mousePositionCallback, (void*)this);
		}

		void Update() override {
			float velocity = cameraSpeed * (float)gTime.deltaTime;

			if (gKeyboard.KEY_W) {
				gCamera.getComponent<Transform>()->position += gCamera.front * velocity;
			}

			if (gKeyboard.KEY_A) {
				gCamera.getComponent<Transform>()->position -= gCamera.right * velocity;
			}

			if (gKeyboard.KEY_S) {
				gCamera.getComponent<Transform>()->position -= gCamera.front * velocity;
			}

			if (gKeyboard.KEY_D) {
				gCamera.getComponent<Transform>()->position += gCamera.right * velocity;
			}

			if (gKeyboard.KEY_SPACE) {
				gCamera.getComponent<Transform>()->position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
			}

			if (gKeyboard.KEY_LEFT_SHIFT) {
				gCamera.getComponent<Transform>()->position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
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

	void mousePositionCallback(int xPos, int yPos, void* data) {
		FPSController* controller = (FPSController*)data;
		if (controller->firstMouse) {
			controller->lastX = gMouse.xPosition;
			controller->lastY = gMouse.yPosition;
			controller->firstMouse = false;
		}

		float xOffset = (float)(gMouse.xPosition - controller->lastX);
		float yOffset = (float)(controller->lastY - gMouse.yPosition);
		controller->lastX = gMouse.xPosition;
		controller->lastY = gMouse.yPosition;

		xOffset *= controller->mouseSensitivity;
		yOffset *= controller->mouseSensitivity;

		controller->yaw += xOffset;
		controller->pitch += yOffset;

		if (controller->pitch > 89.0f)
			controller->pitch = 89.0f;
		if (controller->pitch < -89.0f)
			controller->pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(controller->yaw)) * cos(glm::radians(controller->pitch));
		direction.y = sin(glm::radians(controller->pitch));
		direction.z = sin(glm::radians(controller->yaw)) * cos(glm::radians(controller->pitch));

		gCamera.front = glm::vec3(0.0f);
		gCamera.front = glm::normalize(direction);
	}
}