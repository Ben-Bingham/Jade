#include "Engine Structure/Subsystems/Mouse.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void Mouse::StartUp() {
		gWindow.setMouseButtonCallback(mouseButtonCallback);
		gWindow.setMousePositionCallback(mousePositionCallback);
		gWindow.setScrollWheelCallback(mouseScrolWheelCallback);
		gWindow.setCursorEntersCallback(cursorEnterCallback);
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_1: gMouse.button1 = intToMouseState(action); break;
		case GLFW_MOUSE_BUTTON_2: gMouse.button2 = intToMouseState(action); break;
		case GLFW_MOUSE_BUTTON_3: gMouse.button3 = intToMouseState(action); break;
		}
	}

	void mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
		gMouse.xPosition = (int)xpos;
		gMouse.yPosition = (int)ypos;

		int count{ 0 };
		for (void (*callback)(int xpos, int ypos, void* data) : gMouse.mousePositionCallbacks) {
			callback((int)xpos, (int)ypos, gMouse.mousePositionCallbackData[count]);
			count++;
		}
	}

	void mouseScrolWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
		int count{ 0 };
		for (void (*callback)(int xoffset, int yoffset, void* data) : gMouse.scrollCallbacks) {
			callback((int)xoffset, (int)yoffset, gMouse.scrollCallbacksData[count]);
			count++;
		}
	}

	void cursorEnterCallback(GLFWwindow* window, int entered) {}

	MouseButtonState intToMouseState(int state) {
		switch (state) {
		default:
		case GLFW_PRESS: return BUTTON_PRESSED;
		case GLFW_RELEASE: return BUTTON_RELEASED;
		}
	}
}