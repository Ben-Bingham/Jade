#pragma once
#include <GLFW/glfw3.h>

#include "Jade.h"

namespace Jade {
	class Window {
	public:
		Window(int width, int height, std::string name);

		~Window() { dispose(); }

		GLFWwindow* getWindow() { return m_Window; }

		void swapBuffers() { glfwSwapBuffers(m_Window); }

		void dispose() {
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		void pollEvents() { glfwPollEvents(); }

		bool getWindowShouldClose() {
			return glfwWindowShouldClose(m_Window);
		}

		void addFrameBufferSizeCallback(void (*callback)(GLFWwindow* window, int width, int height)) {
			glfwSetFramebufferSizeCallback(m_Window, callback);
		}

		void addMousePositionCallback(void (*callback)(GLFWwindow* window, double xpos, double ypos)) {
			glfwSetCursorPosCallback(m_Window, callback);
		}

		void addScrollWheelCallback(void (*callback)(GLFWwindow* window, double xOffset, double yOffset)) {
			glfwSetScrollCallback(m_Window, callback);
		}

		void disableCursor() {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

	private:
		GLFWwindow* m_Window;
		int m_Width;
		int m_Height;
		std::string m_Name;
	};
	
}
