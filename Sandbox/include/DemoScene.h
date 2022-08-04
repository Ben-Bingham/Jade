#pragma once

#include "Jade.h"

#include "Entity Component System/Components/FPSController.h"

class DemoScene : public Jade::Scene {
public:
	void Begin() override {
		Jade::Model backpack{ "assets\\models\\backpack\\backpack.obj", false };

		Jade::Gameobject demoCube{};
		//Jade::Gameobject lightBox{};
		Jade::PointLight light{};

		Jade::PhongRenderingComponent demoCubeRenderingComponent{ Jade::CUBE, Jade::MaterialCreator::DefaultMaterial() };

		Jade::SolidRenderingComponent lightBoxRenderingComponent{ Jade::CUBE, Jade::Colour(255, 255, 255) };

		demoCube.addComponent(demoCubeRenderingComponent);
		//lightBox.addComponent(lightBoxRenderingComponent);

		//lightBox.getComponent<Jade::Transform>()->Translate(2.0f, 4.0f, -2.0f).Scale(0.2f);
		light.getComponent<Jade::Transform>()->Translate(1.0f, 2.0f, -1.0f);

		addGameobject(demoCube);
		//addGameobject(lightBox);
		//addGameobject(light);
		addGameobject(Jade::DirectionalLight{});

		Jade::Gameobject backpackObject{};
		backpackObject.addComponent(Jade::PhongRenderingComponent{ backpack });

		backpackObject.getComponent<Jade::Transform>()->Translate(5, 0, 0);
		addGameobject(backpackObject);

		Jade::Camera camera;
		Jade::Engine::setCamera(camera);

		Jade::FPSController fpsController;
		camera.addComponent(fpsController);

		addGameobject(camera);

		Jade::Gameobject floor{};
		floor.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::MaterialCreator::SpecifiedMaterial(Jade::Colour{ 153, 121, 63} ) });
		floor.getComponent<Jade::Transform>()->Scale(100, 0, 100).Translate(0, -5, 0);
		addGameobject(floor);

		Jade::Image container2{ "assets\\textures\\container2.png" };
		Jade::Image container2_Specular{ "assets\\textures\\container2_specular.png" }; 

		Jade::Gameobject cube2{};
		cube2.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		cube2.getComponent<Jade::Transform>()->Translate(10, 1, 3).Rotate(glm::vec3(0.5, 0.5, 0.5), 33.0f);
		addGameobject(cube2);

		Jade::Gameobject cube3{};
		cube3.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		cube3.getComponent<Jade::Transform>()->Translate(4, 4, -6).Rotate(glm::vec3(0.1, 0.9, 4), 90.0f);
		addGameobject(cube3);
	}

	void Update() override{
		if (Jade::gKeyboard.KEY_ESCAPE) {
			stop();
		}
	}
};