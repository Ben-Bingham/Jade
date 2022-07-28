#pragma once
#include <vector>
#include "Entity Component System/Gameobject.h"
#include "Entity Component System/Components/PhongRenderingComponent.h"

namespace Jade {
	class Application;

	class Scene {
	public:
		Scene() {}
		Scene(const Scene&) = default;
		Scene(Scene&&) = default;
		Scene& operator=(const Scene&) = default;
		Scene& operator=(Scene&&) = default;
		virtual ~Scene() = 0;

		void addGameobject(Gameobject* gameobject) { m_Gameobjects.push_back(gameobject); }

		void begin();
		void update();
		void cleanup();

		virtual void Begin() {}
		virtual void Update() {}
		virtual void Cleanup() {}

		void stop() {
			isRunning = false;
		}

		bool isRunning{true};

	private:
		std::vector<Gameobject*> m_Gameobjects;
	};
}