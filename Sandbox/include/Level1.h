#pragma once
#include "Engine Structure/Scene.h"
#include "Engine Structure/Engine.h"
#include "Entity Component System/Components/Transform.h"

class Level1 : public Jade::Scene {
public:
	Level1() {}

	unsigned int playerScore{ 0 };

	Jade::Model backpack{ "assets\\models\\backpack\\backpack.obj", true };
	Jade::Gameobject testCube{};

	Jade::PhongRenderingComponent backpackRenderer{ &backpack };

	void Begin() override {
		testCube.addComponent(&backpackRenderer);
		testCube.getComponent<Jade::Transform>()->position = glm::vec3(0.0f, 0.0f, -10.0f);
		addGameobject(&testCube);

		addLight(Jade::PointLight());
		addLight(Jade::DirectionalLight());
	}

	bool keyHit{ false };
	bool keyReleased{ false };

	void Update() override {
		if (Jade::gKeyboard.KEY_ENTER) {
			playerScore++;
		}

		if (playerScore > 100) {
			stop();
		}

		if (Jade::gKeyboard.KEY_ESCAPE) {
			Jade::gWindow.setWindowShouldClose();
		}
	}

	void Cleanup() override {
		playerScore = 0;
		isRunning = true;
	}
};
