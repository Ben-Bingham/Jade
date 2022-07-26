#pragma once
#include <vector>
#include "Gameobject.h"

namespace Jade {
	class Scene {
	public:
		Scene() {}

		void addGameobject(Gameobject* gameobject) { m_Gameobjects.push_back(gameobject); }

		void begin() {
			for (Gameobject* gameobject : m_Gameobjects) {
				gameobject->begin();
			}
		}

		void update() {
			for (Gameobject* gameobject : m_Gameobjects) {
				gameobject->update();
			}
		}

		void cleanup() {
			for (Gameobject* gameobject : m_Gameobjects) {
				gameobject->cleanup();
			}
		}

	private:
		std::vector<Gameobject*> m_Gameobjects;

		
	};
}