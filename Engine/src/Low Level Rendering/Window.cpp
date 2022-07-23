#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Jade.h"

#include "Low Level Rendering/Window.h"

namespace Jade {
	Window::Window(int width, int height, std::string name, bool fullscreen)
		: m_Width(width), m_Height(height), m_Name(name), m_ProjectionMatrix(1.0) {

		if (!glfwInit()) {
			LOG("GLFW failed to initilize.", Jade::ERROR);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef JADE_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif // JADE_DEBUG

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		if (fullscreen) {
			m_Window = glfwCreateWindow(mode->width, mode->height, name.c_str(), glfwGetPrimaryMonitor(), NULL);
		}
		else {
			m_Window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		}

		if (!m_Window) {
			LOG("GLFW window creation failed.", Jade::ERROR);
			LOG("OpenGL context creation failed.", Jade::ERROR);
		}

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);
	}
}