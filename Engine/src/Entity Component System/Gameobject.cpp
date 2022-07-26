#include "Entity Component System/Gameobject.h"

namespace Jade {
	unsigned int Gameobject::staticID = 0;

	void Gameobject::begin() {
		for (Component* component : m_Components) {
			component->begin();
		}

		for (Gameobject* child : m_Children) {
			child->begin();
		}
	}

	void Gameobject::update() {
		for (Component* component : m_Components) {
			component->update();
		}

		for (Gameobject* child : m_Children) {
			child->update();
		}
	}

	void Gameobject::cleanup() {
		for (Component* component : m_Components) {
			component->cleanup();
		}

		for (Gameobject* child : m_Children) {
			child->cleanup();
		}
	}
}