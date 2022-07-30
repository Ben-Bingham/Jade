#pragma once
#include "Jade.h"

namespace Jade {
	class Gameobject;

	class Component {
	public:
		Component() {}
		Component(const Component&) = default;
		Component(Component&&) = default;
		Component& operator=(const Component&) = default;
		Component& operator=(Component&&) = default;
		virtual ~Component() = 0;

		virtual void Update() {}
		virtual void Begin() {}
		virtual void Cleanup() {}

		Gameobject* getGameobject() { return m_Gameobject; }

		void setGameobject(Gameobject* gameobject) { m_Gameobject = gameobject; }

		void update();
		void begin();
		void cleanup();

	private:
		Gameobject* m_Gameobject{ nullptr };
	};
}