#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "High Level Rendering/Renderer.h"
#include "High Level Rendering/Camera.h"
#include "Low Level Rendering/GLEW.h"
#include "Low Level Rendering/Window.h"

namespace Jade {
	class Application {
	public:
		Application() :
			m_ScreenWidth(640),
			m_ScreenHeight(480),
			m_Window(m_ScreenWidth, m_ScreenHeight, "Engine", false),
			m_Glew() {

			begin();

			while (m_Window.getWindowOpen()) {
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
		unsigned int m_ScreenWidth;
		unsigned int m_ScreenHeight;

		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;

		bool m_MouseHasMoved = false;

		Camera m_Camera;
		Renderer m_Renderer;
		Window m_Window;
		GLEW m_Glew;

		void begin();
		void update();
		void lateUpdate();
		void cleanup();
	};
}