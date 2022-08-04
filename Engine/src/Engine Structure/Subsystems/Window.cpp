#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core Systems/Logging/Log.h"

#include "Engine Structure/Subsystems/Window.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	Window::Window()
		: m_Width(640), m_Height(480), m_Name("Jade Engine"), m_ProjectionMatrix(1.0) {
		bool fullscreen = false;

		if (!glfwInit()) {
			LOG("GLFW failed to initilize.", Jade::ERROR);
		}

		//glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef JADE_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif // JADE_DEBUG

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		if (fullscreen) {
			m_Window = glfwCreateWindow(mode->width, mode->height, m_Name.c_str(), glfwGetPrimaryMonitor(), NULL);
		}
		else {
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL);
		}

		if (!m_Window) {
			LOG("GLFW window creation failed.", Jade::ERROR);
			LOG("OpenGL context creation failed.", Jade::ERROR);
		}

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);
	}

	void Window::update() {
		pollEvents();
		calculateProjectionMatrix(gCamera.getFOV());
	}

	void windowSizeCallBack(GLFWwindow* window, int width, int height) {
		gWindow.setWidth((unsigned int)width);
		gWindow.setHeight((unsigned int)height);

		gWindow.calculateProjectionMatrix(gCamera.getFOV());

		glViewport(0, 0, gWindow.getWidth(), gWindow.getHeight());
	}
}