#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Jade.h"

namespace Jade {
	class Window {
	public:
		Window(int width, int height, std::string name, bool fullscreen);

		~Window() { dispose(); }

		GLFWwindow* getWindow() const { return m_Window; }

		void swapBuffers() { glfwSwapBuffers(m_Window); }

		void dispose() {
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		void pollEvents() { glfwPollEvents(); }

		bool getWindowOpen() {
			return !glfwWindowShouldClose(m_Window);
		}

		void setFrameBufferSizeCallback(void (*callback)(GLFWwindow* window, int width, int height)) {
			glfwSetFramebufferSizeCallback(m_Window, callback);
		}

		void setMousePositionCallback(void (*callback)(GLFWwindow* window, double xpos, double ypos)) {
			glfwSetCursorPosCallback(m_Window, callback);
		}

		void setScrollWheelCallback(void (*callback)(GLFWwindow* window, double xOffset, double yOffset)) {
			glfwSetScrollCallback(m_Window, callback);
		}

		void setMouseButtonCallback(void (*callback)(GLFWwindow* window, int button, int action, int mods)) {
			glfwSetMouseButtonCallback(m_Window, callback);
		}

		void disableCursor() {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		glm::mat4 getProjectionMatrix() { 
			m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f); //TODO
			return m_ProjectionMatrix;
		}

	private:
		GLFWwindow* m_Window;
		int m_Width;
		int m_Height;
		std::string m_Name;
		glm::mat4 m_ProjectionMatrix;
	};
}
