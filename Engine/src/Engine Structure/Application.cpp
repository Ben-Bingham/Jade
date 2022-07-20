#include <glm/glm.hpp>

#include "Jade.h"

#include "Engine Structure/Application.h"

namespace Jade {
	Window window(640, 480, "", false);
	GLEW glew;
	Keyboard keyboard(&window);

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

		window.pollEvents();

		glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Application::lateUpdate() {
		LateUpdate();
		
		window.swapBuffers();
		glCheckError();
	}

	void Application::cleanup() {
		Cleanup();

		m_Renderer.dispose();
		window.dispose();
	}
}