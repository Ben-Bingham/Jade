#include <glm/glm.hpp>

#include "Jade.h"

#include "Engine Structure/Application.h"

namespace Jade {
	void Application::begin() {
		Begin();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glEnable(GL_DEPTH_TEST);

		glCheckError();

	}

	void Application::update() {
		Update();

		m_Window.pollEvents();

		glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Application::lateUpdate() {
		LateUpdate();
		
		m_Window.swapBuffers();
		glCheckError();
	}

	void Application::cleanup() {
		Cleanup();

		m_Renderer.dispose();
		m_Window.dispose();
	}

	//void Application::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	//	glViewport(0, 0, width, height);
	//	m_ScreenWidth = width;
	//	m_ScreenHeight = height;

	//	projection = glm::mat4(1.0f);
	//	float aspectRatio = (float)width / (float)height;
	//	projection = glm::perspective(glm::radians(m_Camera.getFOV()), aspectRatio, 0.1f, 100.0f); //TODO objects seem to stretch when window is resized
	//}

	//void Application::mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	//	if (m_MouseHasMoved) {
	//		m_LastMouseX = (float)xPos;
	//		m_LastMouseY = (float)yPos;
	//		m_MouseHasMoved = false;
	//	}

	//	float xOffset = (float)xPos - m_LastMouseX;
	//	float yOffset = m_LastMouseY - (float)yPos; // reversed since y-coordinates range from bottom to top
	//	m_LastMouseX = (float)xPos;
	//	m_LastMouseY = (float)yPos;

	//	m_Camera.processMouseMovement(xOffset, yOffset);
	//}

	//void Application::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	//	m_Camera.processScollWheel(yOffset);
	//}
}