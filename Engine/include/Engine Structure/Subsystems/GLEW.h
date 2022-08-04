#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Log.h"

#include "Engine Structure/Subsystems/Subsystem.h"

namespace Jade {
	class GLEW : public Subsystem {
	public:
		GLEW() {}

		void StartUp() override;

		void ShutDown() override {}
	};

	void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id,
		GLenum severity, GLsizei length, const char* message, const void* userParam);
}