#include "Entity Component System/Component.h"

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