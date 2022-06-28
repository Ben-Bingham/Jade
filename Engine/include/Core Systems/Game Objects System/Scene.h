#pragma once

#include <vector>

#include "Jade.h"

#include "GameObject.h"

namespace Jade {
	class Scene {
	public:
		Scene() {
		}

		void render() {
			/*for each (GameObject gameObject in m_GameObjects) {
				gameObject.render();
			}*/
		}

		void addGameObject(const GameObject& gameObject) {
			//m_GameObjects.push_back(gameObject);
		}

	private:
		std::vector<GameObject> m_GameObjects;
	};
}