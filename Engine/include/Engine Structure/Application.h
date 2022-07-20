#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "High Level Rendering/Renderer.h"
#include "High Level Rendering/Camera.h"
#include "Low Level Rendering/GLEW.h"
#include "Low Level Rendering/Window.h"
#include "Core Systems/Human Interface Devices/Keyboard.h"

namespace Jade {
	extern Window window;
	extern GLEW glew;
	extern Keyboard keyboard;

	class Application {
	public:
		Application() {}

		void start() {
			glCheckError();
			begin();

			while (window.getWindowOpen()) {
				update();
				lateUpdate();
			}

			cleanup();
		}

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

		void begin();
		void update();
		void lateUpdate();
		void cleanup();
	};
}