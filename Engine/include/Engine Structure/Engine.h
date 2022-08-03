#pragma once
#include "Subsystems/Subsystem.h"
#include "Engine Structure/Subsystems/Renderer.h"
#include "Engine Structure/Subsystems/Window.h"
#include "Engine Structure/Subsystems/Camera.h"
#include "Engine Structure/Subsystems/Keyboard.h"
#include "Engine Structure/Subsystems/Mouse.h"
#include "Engine Structure/Subsystems/GLEW.h"
#include "Engine Structure/Subsystems/Time.h"

namespace Jade {
	extern Time gTime;
	extern Window gWindow;
	extern Keyboard gKeyboard;
	extern Mouse gMouse;
	extern GLEW gGlew;
	extern Camera gCamera;
	extern Renderer gRenderer;
	//TODO Event Subsystem

	class Engine : public Subsystem {
	public:
		Engine() {}

		template<typename T>
		void LoadScene(T& scene) {
			if (m_ActiveScene != nullptr) {
				m_ActiveScene->stop();
				m_ActiveScene->cleanup();
			}

			m_ActiveScene = std::make_unique<T>(scene);
			m_ActiveScene->begin();

			while (gWindow.getWindowOpen() && m_ActiveScene->isRunning) {
				gTime.update();
				gWindow.update();
				gRenderer.update(); // Clears the screen

				m_ActiveScene->update();

				gWindow.lateUpdate();
			}
		}

		void StartUp() override {
			gTime.StartUp();
			gWindow.StartUp();
			gKeyboard.StartUp();
			gMouse.StartUp();
			gGlew.StartUp();
			gRenderer.StartUp();
		}

		void ShutDown() override {
			gTime.ShutDown();
			gRenderer.ShutDown();
			gGlew.ShutDown();
			gMouse.ShutDown();
			gKeyboard.ShutDown();
			gWindow.ShutDown();
		}

		static void setCamera(const Camera& camera) {
			gCamera = camera;
		}

	private:
		std::shared_ptr<Scene> m_ActiveScene;
	};
}