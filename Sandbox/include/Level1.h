#pragma once
#include "Entity Component System/Scene.h"

class Level1 : public Jade::Scene {
public:
	Level1() {}

	unsigned int playerScore{ 0 };
};
