#include "Engine Structure/Engine.h"
#include "Engine Structure/Scene.h"

namespace Jade {
	Time gTime{};
	Window gWindow{};
	Keyboard gKeyboard{};
	Mouse gMouse{};
	GLEW gGlew{};
	Camera gCamera{};
	Renderer gRenderer{};

	void Engine::LoadScene(Scene* scene) {
		if (m_ActiveScene != nullptr) {
			m_ActiveScene->stop();
			m_ActiveScene->cleanup();
		}

		m_ActiveScene = scene;
		m_ActiveScene->begin();

		while (gWindow.getWindowOpen() && m_ActiveScene->isRunning) {
			gTime.update();
			gWindow.update();
			gRenderer.update();

			m_ActiveScene->update();
			
			gWindow.lateUpdate();
		}
	}
}