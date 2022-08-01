#include "Entity Component System/Gameobjects/Gameobject.h"

namespace Jade {
	unsigned int Gameobject::staticID = 0;

	void Gameobject::begin() {
		for (std::shared_ptr<Component> component : m_Components) {
			component->begin();
		}

		for (std::shared_ptr<Gameobject> child : m_Children) {
			child->begin();
		}
	}

	void Gameobject::update() {
		for (std::shared_ptr<Component> component : m_Components) {
			component->update();
		}

		for (std::shared_ptr<Gameobject> child : m_Children) {
			child->update();
		}
	}

	void Gameobject::cleanup() {
		for (std::shared_ptr<Component> component : m_Components) {
			component->cleanup();
		}

		for (std::shared_ptr<Gameobject> child : m_Children) {
			child->cleanup();
		}
	}
}