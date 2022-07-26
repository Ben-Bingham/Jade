#include "Entity Component System/Component.h"

namespace Jade {
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