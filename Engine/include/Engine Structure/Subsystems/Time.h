#pragma once
#include <GLFW/glfw3.h>

#include "Engine Structure/Subsystems/Subsystem.h"

namespace Jade {
	class Time : public Subsystem {
	public:
		Time() {}

		void StartUp() override {}

		void ShutDown() override {}

		void update() {
			double currentFrame{ glfwGetTime() };
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
		}

		double deltaTime{ 0.0 };

	private:
		double lastFrame{ 0.0 };
	};
}