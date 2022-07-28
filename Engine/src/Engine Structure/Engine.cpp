#include "Engine Structure/Engine.h"
#include "Entity Component System/Scene.h"

namespace Jade {
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
			gWindow.update();
			gRenderer.update();

			m_ActiveScene->update();
			
			gWindow.lateUpdate();
		}
	}
}