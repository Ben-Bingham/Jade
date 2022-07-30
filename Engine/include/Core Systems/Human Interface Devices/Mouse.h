#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Engine Structure/Subsystems/Subsystem.h"

namespace Jade {
	enum MouseButtonState {
		BUTTON_RELEASED = 0, 
		BUTTON_PRESSED = 1
	};
 
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);

	class Mouse : public Subsystem {
	public:
		Mouse() {}

		void StartUp() override;
		void ShutDown() override {}

		int xPosition{ 0 };
		int yPosition{ 0 };

		MouseButtonState button1{ BUTTON_RELEASED }; // Left
		MouseButtonState button2{ BUTTON_RELEASED }; // Right
		MouseButtonState button3{ BUTTON_RELEASED }; // Middle

		void addScrollCallback(void (*callback)(int xoffset, int yoffset, void* data), void* data) {
			scrollCallbacks.push_back(callback);
			scrollCallbacksData.push_back(data);
		}

		std::vector<void (*)(int xoffset, int yoffset, void* data)> scrollCallbacks;
		std::vector<void*> scrollCallbacksData;
	};

	MouseButtonState intToMouseState(int state);
}