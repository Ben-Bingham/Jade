#include <GLFW/glfw3.h>

#include "Jade.h"

#include "GLFW/Window.h"

namespace Jade {
	namespace GLFW {
		Window::Window(int width, int height, std::string name) 
			: m_Width(width), m_Height(height), m_Name(name) {

			if (!glfwInit()) {
				LOGGER.log("GLFW failed to initilize.", Jade::ERROR);
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

			m_Window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

			if (!m_Window) {
				LOGGER.log("GLFW window creation failed.", Jade::ERROR);
				LOGGER.log("OpenGL context creation failed.", Jade::ERROR);
			}

			glfwMakeContextCurrent(m_Window);
			glfwSwapInterval(1);
		}
	}
}