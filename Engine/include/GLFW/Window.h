#pragma once
#include <GLFW/glfw3.h>

#include "Jade.h"

namespace Jade {
	namespace GLFW {
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

		private:
			GLFWwindow* m_Window;
			int m_Width;
			int m_Height;
			std::string m_Name;
		};
	}
}
