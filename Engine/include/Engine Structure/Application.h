#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "High Level Rendering/Renderer.h"
#include "High Level Rendering/Camera.h"
#include "Low Level Rendering/GLEW.h"
#include "Low Level Rendering/Window.h"
#include "Core Systems/Human Interface Devices/Keyboard.h"
#include "Core Systems/Human Interface Devices/Mouse.h"

namespace Jade {
	extern Window WINDOW;
	extern Keyboard KEYBOARD;
	extern Mouse MOUSE;

	class Application {
	public:
		Application() {}

		void start() {
			glCheckError();
			begin();

			while (WINDOW.getWindowOpen()) {
				update();
				lateUpdate();
			}

			cleanup();
		}

		void addRuleset(RenderingRuleSet* ruleset) { //TODO remove
			m_Renderer.addRuleSet(ruleset);
		}

		void addRenderable(RenderableObject* renderable) { //TODO remove
			m_Renderer.addRenderable(renderable);
		}

		Camera& getCamera() { return m_Camera; }

		virtual void Begin() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void Cleanup() {}

	private:
		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;

		bool m_MouseHasMoved = false;

		Camera m_Camera;
		Renderer m_Renderer;
		GLEW m_Glew;

		void begin();
		void update();
		void lateUpdate();
		void cleanup();
	};

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	void mouseScrolWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
}

using Jade::KEYBOARD;
using Jade::WINDOW;
using Jade::MOUSE;
using Jade::Application;