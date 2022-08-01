#pragma once
#include "Engine Structure/Scene.h"
#include "Engine Structure/Engine.h"
#include "Entity Component System/Components/Transform.h"

class Level1 : public Jade::Scene {
public:
	Level1() {}

	unsigned int playerScore{ 0 };

	Jade::Model backpack{ "assets\\models\\backpack\\backpack.obj", true };

	Jade::PhongRenderingComponent backpackRenderer{ &backpack };
	Jade::PhongRenderingComponent defaultd{ Jade::PYRAMID, Jade::MaterialCreator::DefaultMaterial() };

	void Begin() override {
		Jade::Gameobject testCube{};
		testCube.addComponent(backpackRenderer);
		testCube.getComponent<Jade::Transform>()->position = glm::vec3(0.0f, 0.0f, -10.0f);
		addGameobject(testCube);

		addLight(Jade::PointLight{});
		addLight(Jade::DirectionalLight{});

		Jade::Gameobject testPyramid{};
		testPyramid.addComponent(defaultd);
		addGameobject(testPyramid);
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
};
