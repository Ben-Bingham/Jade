#pragma once
#include "Entity Component System/Scene.h"

namespace Jade {
	class Engine {
	public:
		Engine() {}

		void LoadScene(Scene& scene) {
			if (m_ActiveScene != nullptr) {
				m_ActiveScene->stop();
			}

			m_ActiveScene = &scene;
			m_ActiveScene->run();
		}

		void StartUp() {
			
		}

		void ShutDown() {

		}

	private:
		Scene* m_ActiveScene{nullptr};
	};
}