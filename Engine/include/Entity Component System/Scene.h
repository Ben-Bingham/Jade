#pragma once
#include <vector>
#include "Gameobject.h"
#include "Components/PhongRenderingComponent.h"

namespace Jade {
	class Application;

	class Scene {
	public:
		Scene() {}

		void addGameobject(Gameobject* gameobject) { m_Gameobjects.push_back(gameobject); }

		void begin(Application& app);

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
		std::vector<Gameobject*> m_Gameobjects; //TODO if this is pointers that could really affect how reloading a scene would work
		// we would not be able to garentee that the objects were not changed before the scene was loaded for a second time
	};
}