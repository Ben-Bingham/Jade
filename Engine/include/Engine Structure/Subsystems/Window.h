#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Jade.h"

#include "Engine Structure/Subsystems/Subsystem.h"

namespace Jade {
	void windowSizeCallBack(GLFWwindow* window, int width, int height);

	class Window : public Subsystem {
	public:
		Window();

		~Window() { dispose(); }

		void StartUp() override{
			setFrameBufferSizeCallback(windowSizeCallBack);
		}

		void ShutDown() override {}

		void update();

		void lateUpdate() {
			swapBuffers();
		}

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

		void setKeyCallback(void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mods)) {
			glfwSetKeyCallback(m_Window, callback);
		}

		void setWindowShouldClose() {
			glfwSetWindowShouldClose(m_Window, true);
		}

		void disableCursor() {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		void calculateProjectionMatrix(float FOV) {
			m_ProjectionMatrix = glm::mat4(1.0);
			m_ProjectionMatrix = glm::perspective(glm::radians(FOV), (float)((float)m_Width / (float)m_Height), 0.1f, 100.0f);
		}

		glm::mat4 getProjectionMatrix() { return m_ProjectionMatrix; }

		void setWidth(unsigned int width) { m_Width = width; }
		void setHeight(unsigned int height) { m_Height = height; }

		unsigned int getHeight() const { return m_Height; }
		unsigned int getWidth() const { return m_Width; }

	private:
		GLFWwindow* m_Window;
		unsigned int m_Width;
		unsigned int m_Height;
		std::string m_Name;
		glm::mat4 m_ProjectionMatrix;
	};
}
