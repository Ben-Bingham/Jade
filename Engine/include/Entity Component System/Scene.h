#pragma once
#include <vector>
#include "Gameobject.h"
#include "Components/PhongRenderingComponent.h"

namespace Jade {
	class Application;

	class Scene { //TODO move into engine structor folder
	public:
		Scene() {}
		virtual ~Scene() = 0;

		void addGameobject(Gameobject* gameobject) { m_Gameobjects.push_back(gameobject); }

		void begin(/*Application& app*/);
		void update();
		void cleanup();

		void run() {
			begin();
			
			while (isRunning) {
				update();
				break;
			}

			cleanup();
		}

		void stop() {
			isRunning = false;
		}

		bool isRunning{true};

	private:
		std::vector<Gameobject*> m_Gameobjects; //TODO if this is pointers that could really affect how reloading a scene would work
		// we would not be able to garentee that the objects were not changed before the scene was loaded for a second time
	};
}