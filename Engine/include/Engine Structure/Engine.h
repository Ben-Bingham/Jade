#pragma once
#include "Subsystems/Subsystem.h"
#include "High Level Rendering/Renderer.h"
#include "Low Level Rendering/Window.h"
#include "High Level Rendering/Camera.h"
#include "Core Systems/Human Interface Devices/Keyboard.h"
#include "Core Systems/Human Interface Devices/Mouse.h"
#include "Low Level Rendering/GLEW.h"

namespace Jade {
	extern Window gWindow;
	extern Keyboard gKeyboard;
	extern Mouse gMouse;
	extern GLEW gGlew;
	extern Camera gCamera;
	extern Renderer gRenderer;

	class Scene;

	class Engine : public Subsystem {
	public:
		Engine() {}

		void LoadScene(Scene* scene);

		void StartUp() override {
			gWindow.StartUp();
			gKeyboard.StartUp();
			gMouse.StartUp();
			gGlew.StartUp();
			gRenderer.StartUp();
		}

		void ShutDown() override {
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