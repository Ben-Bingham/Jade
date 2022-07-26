#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "High Level Rendering/Renderer.h"
#include "High Level Rendering/Camera.h"
#include "Low Level Rendering/GLEW.h"
#include "Low Level Rendering/Window.h"
#include "Core Systems/Human Interface Devices/Keyboard.h"
#include "Core Systems/Human Interface Devices/Mouse.h"
#include "Entity Component System/Scene.h"

namespace Jade {
	extern Window WINDOW;
	extern Keyboard KEYBOARD;
	extern Mouse MOUSE;
	extern Camera CAMERA;

	class Application { //TODO make it so that the user can optionally attach a callback to the mouse moving or scrolling
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

		void addRuleset(PShader* ruleset) { //TODO remove
			m_Renderer.addShader(ruleset);
		}

		void addRenderable(RenderableObject* renderable) { //TODO remove
			m_Renderer.addRenderable(renderable);
		}

		void setActiveScene(Scene* scene) { m_ActiveScene = scene; }

		virtual void Begin() {} //TODO there needs to be a good way to remove these
		virtual void Update() {} //TODO there needs to be a good way to remove these
		virtual void LateUpdate() {} //TODO there needs to be a good way to remove these
		virtual void Cleanup() {} //TODO there needs to be a good way to remove these
		
		void quit() { WINDOW.setWindowShouldClose(); }

	private:
		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;

		bool m_MouseHasMoved = false;

		Renderer m_Renderer{};
		GLEW m_Glew{};
		Scene* m_ActiveScene{};

		void begin();
		void update();
		void lateUpdate();
		void cleanup();
	};

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	void mouseScrolWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
	void windowSizeCallBack(GLFWwindow* window, int width, int height);

	void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
		GLsizei length, const char* message, const void* userParam);
}

using Jade::KEYBOARD;
using Jade::WINDOW;
using Jade::MOUSE;
using Jade::CAMERA;
using Jade::Application;