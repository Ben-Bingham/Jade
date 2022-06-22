#pragma once
#include <GLFW/glfw3.h>

#include "Jade.h"

namespace Jade {
	namespace GLFW {
		class Window {
		public:
			Window(int width, int height, std::string name);

			GLFWwindow* getWindow() { return m_Window; }

		private:
			GLFWwindow* m_Window;
			int m_Width;
			int m_Height;
			std::string m_Name;
		};
	}
}
