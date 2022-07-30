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

	class Scene;

	class Engine : public Subsystem {
	public:
		Engine() {}

		void LoadScene(Scene* scene);

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

		void setCamera(const Camera& camera) {
			gCamera = camera;
		}

	private:
		Scene* m_ActiveScene{ nullptr };
	};
}