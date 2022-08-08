#include "Entity Component System/Components/Component.h"
#include "Entity Component System/Gameobjects/Gameobject.h"

namespace Jade {
	Component::~Component() {}

	void Component::begin() {
		Begin();
	}

	void Component::update() {
		Update();
	}

	void Component::cleanup() {
		Cleanup();
	}

	Gameobject Component::getGameobject() {
		return *m_Gameobject; 
	}
}