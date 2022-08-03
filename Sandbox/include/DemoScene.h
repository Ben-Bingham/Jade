#pragma once

#include "Engine Structure/Scene.h"

class DemoScene : public Jade::Scene {
public:
	Jade::Model backpack{ "assets\\models\\backpack\\backpack.obj", false };

	void Begin() override {
		Jade::Gameobject demoCube{};
		Jade::Gameobject lightBox{};
		Jade::PointLight light{};

		Jade::PhongRenderingComponent demoCubeRenderingComponent{ Jade::CUBE, Jade::MaterialCreator::DefaultMaterial() };

		Jade::SolidRenderingComponent lightBoxRenderingComponent{ Jade::CUBE, Jade::Colour(255, 255, 255) };

		demoCube.addComponent(demoCubeRenderingComponent);
		lightBox.addComponent(lightBoxRenderingComponent);

		lightBox.getComponent<Jade::Transform>()->position = glm::vec3(2.0f, 4.0f, -2.0f);
		lightBox.getComponent<Jade::Transform>()->scale = glm::vec3(0.2f);
		light.getComponent<Jade::Transform>()->position = glm::vec3(1.0f, 2.0f, -1.0f);

		addGameobject(demoCube);
		addGameobject(lightBox);
		addLight(light);

		Jade::Gameobject backpackObject{};
		backpackObject.addComponent(Jade::PhongRenderingComponent{ &backpack });

		addGameobject(backpackObject);
	}

	void Update() override {

	}
};