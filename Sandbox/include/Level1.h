#pragma once
#include "Engine Structure/Scene.h"
#include "Engine Structure/Engine.h"

class Level1 : public Jade::Scene {
public:
	Level1() {}

	unsigned int playerScore{ 0 };

	Jade::Model backpack{ "assets\\models\\backpack\\backpack.obj", true };
	Jade::Gameobject testCube{};

	Jade::PhongRenderingComponent backpackRenderer{ &backpack };

	void Begin() override {
		backpackRenderer.translate(glm::vec3(0, 0, -10));
		testCube.addComponent(&backpackRenderer);
		addGameobject(&testCube);
	}

	bool keyHit{ false };
	bool keyReleased{ false };

	void Update() override {
		LOG(std::to_string(playerScore));
		if (Jade::gKeyboard.getKeyPressed(Jade::KEY_ENTER)) {
			playerScore++;
		}


		if (playerScore > 100) {
			stop();
		}

		if (Jade::gKeyboard.getKeyPressed(Jade::KEY_ESCAPE)) {
			Jade::gWindow.setWindowShouldClose();
		}
	}

	void Cleanup() override {
		playerScore = 0;
		isRunning = true;
	}
};
