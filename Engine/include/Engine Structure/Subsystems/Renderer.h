#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine Structure/Subsystems/Subsystem.h"

namespace Jade {
	class Engine;

	class Renderer : public Subsystem {
	public:
		Renderer() {}

		void StartUp() override {}

		void ShutDown() override {}

		void update() {
			glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	};
}