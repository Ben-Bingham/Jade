#pragma once
#include "Entity Component System/Component.h"

class TestComponent : public Jade::Component {
public:
	void Update() {
		LOG("Gameobject updated");
	}

private:

};