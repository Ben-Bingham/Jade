#pragma once

#include "Jade.h"

#include "Entity Component System/Components/FPSController.h"

class DemoScene : public Jade::Scene {
public:
	void Begin() override {
		Jade::Model backpack{ "assets\\models\\backpack\\backpack.obj", false };

		Jade::Gameobject demoCube{};
		Jade::Gameobject lightBox{};
		Jade::PointLight light{};

		Jade::PhongRenderingComponent demoCubeRenderingComponent{ Jade::CUBE, Jade::MaterialCreator::DefaultMaterial() };

		Jade::SolidRenderingComponent lightBoxRenderingComponent{ Jade::CUBE, Jade::Colour(255, 255, 255) };

		demoCube.addComponent(demoCubeRenderingComponent);
		lightBox.addComponent(lightBoxRenderingComponent);

		lightBox.getComponent<Jade::Transform>()->Translate(2.0f, 4.0f, -2.0f).Scale(0.2f);
		light.getComponent<Jade::Transform>()->Translate(1.0f, 2.0f, -1.0f);

		addGameobject(demoCube);
		addGameobject(lightBox);
		addGameobject(light);
		addGameobject(Jade::DirectionalLight{});

		Jade::Gameobject backpackObject{};
		backpackObject.addComponent(Jade::PhongRenderingComponent{ backpack });

		addGameobject(backpackObject);

		Jade::Camera camera;
		Jade::Engine::setCamera(camera);

		Jade::FPSController fpsController;
		camera.addComponent(fpsController);

		addGameobject(camera);
	}

	void Update() override{
		if (Jade::gKeyboard.KEY_ESCAPE) {
			stop();
		}
	}
};