#include "Entity Component System/Components/Component.h"

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
}