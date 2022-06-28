#pragma once

#include <vector>

#include "Jade.h"

#include "GameObject.h"

namespace Jade {
	class Scene {
	public:
		Scene() {
			LOGGER.log("Scene created", Jade::INFO);
		}

		void render() {
			LOGGER.log("Scene render", Jade::INFO);
			/*for each (GameObject gameObject in m_GameObjects) {
				gameObject.render();
			}*/
		}

		void addGameObject(const GameObject& gameObject) {
			LOGGER.log("Game object added to scene", Jade::INFO);
			//m_GameObjects.push_back(gameObject);
		}

	private:
		std::vector<GameObject> m_GameObjects;
	};
}