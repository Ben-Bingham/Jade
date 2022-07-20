#include <glm/glm.hpp>

#include "Jade.h"

#include "Engine Structure/Application.h"

namespace Jade {
	Window WINDOW(640, 480, "", false);
	Keyboard KEYBOARD(&WINDOW);

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

		WINDOW.pollEvents();

		glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view;
		view = m_Camera.getViewMatrix();

		m_Renderer.setMatrices(view, WINDOW.getProjectionMatrix());
		m_Renderer.render(m_Camera.getPosition());
	}

	void Application::lateUpdate() {
		LateUpdate();
		
		WINDOW.swapBuffers();
		glCheckError();
	}

	void Application::cleanup() {
		Cleanup();

		m_Renderer.dispose();
		WINDOW.dispose();
	}
}