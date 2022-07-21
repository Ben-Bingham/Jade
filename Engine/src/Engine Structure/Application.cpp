#include <glm/glm.hpp>

#include "Jade.h"

#include "Engine Structure/Application.h"

namespace Jade {
	Window WINDOW(640, 480, "", false); //TODO make a getter that creates one than always returns the same one
	Keyboard KEYBOARD(&WINDOW);
	Mouse MOUSE;

	void Application::begin() {
		Begin();

		WINDOW.setMouseButtonCallback(mouseButtonCallback);
		WINDOW.setMousePositionCallback(mousePositionCallback);
		WINDOW.setScrollWheelCallback(mouseScrolWheelCallback);
		WINDOW.setFrameBufferSizeCallback(windowSizeCallBack);

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

		WINDOW.calculateProjectionMatrix(m_Camera.getFOV());

		m_Renderer.setMatrices(view, WINDOW.getProjectionMatrix());
		m_Renderer.render(m_Camera.getTransform().position);
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

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		MOUSE.setButton(Mouse::intToMouseButton(button), Mouse::intToMouseState(action));
	}

	void mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
		MOUSE.setPosition((unsigned int)xpos, (unsigned int)ypos);
	}

	void mouseScrolWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
		MOUSE.setScrollOffset((int)yoffset);
	}

	void windowSizeCallBack(GLFWwindow* window, int width, int height) {
		WINDOW.setWidth((unsigned int)width);
		WINDOW.setHeight((unsigned int)height);

		WINDOW.calculateProjectionMatrix(45.0f);

		glViewport(0, 0, WINDOW.getWidth(), WINDOW.getHeight());
	}
}