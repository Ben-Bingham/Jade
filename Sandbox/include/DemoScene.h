#pragma once

#include "Jade.h"

#include "Entity Component System/Components/FPSController.h"

class DemoScene : public Jade::Scene {
public:
	Jade::Gameobject lightBox{};
	Jade::PointLight pointLight{};

	void Begin() override {
		Jade::Model backpack{ "assets\\models\\backpack\\backpack.obj", false };

		Jade::Gameobject backpackObject{};
		backpackObject.addComponent(Jade::PhongRenderingComponent{ backpack });
		backpackObject.getComponent<Jade::Transform>()->Translate(5, 0, 0);
		addGameobject(backpackObject);

		Jade::Camera camera;
		Jade::Engine::setCamera(camera);

		Jade::FPSController fpsController;
		camera.addComponent(fpsController);

		addGameobject(camera);

		addGameobject(pointLight);

		Jade::Image container2{ "assets\\textures\\container2.png" };
		Jade::Image container2_Specular{ "assets\\textures\\container2_specular.png" };

		Jade::Gameobject cube1{};
		cube1.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		cube1.getComponent<Jade::Transform>()->Translate(0.0f, -4, 0.0).Scale(100, 0, 100);
		addGameobject(cube1);

		Jade::Gameobject wall1{};
		wall1.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		wall1.getComponent<Jade::Transform>()->Scale(100, 0, 100).Rotate(glm::vec3(0, 0, 1), 90.0f).Translate(0, 15, 0);
		addGameobject(wall1);

		Jade::Gameobject wall2{};
		wall2.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		wall2.getComponent<Jade::Transform>()->Scale(100, 0, 100).Rotate(glm::vec3(0, 0, 1), -90.0f).Translate(0, 15, 0);
		addGameobject(wall2);

		Jade::Gameobject wall3{};
		wall3.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		wall3.getComponent<Jade::Transform>()->Scale(100, 0, 100).Rotate(glm::vec3(1, 0, 0), 90.0f).Translate(0, 15, 0);
		addGameobject(wall3);

		Jade::Gameobject wall4{};
		wall4.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		wall4.getComponent<Jade::Transform>()->Scale(100, 0, 100).Rotate(glm::vec3(1, 0, 0), -90.0f).Translate(0, 15, 0);
		addGameobject(wall4);

		Jade::Gameobject cube2{};
		cube2.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		cube2.getComponent<Jade::Transform>()->Translate(0.0f, 1.5f, 0.0).Scale(0.5f);
		addGameobject(cube2);

		Jade::Gameobject cube3{};
		cube3.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		cube3.getComponent<Jade::Transform>()->Translate(2.0f, 0.0f, 1.0).Scale(0.5f);
		addGameobject(cube3);

		Jade::Gameobject cube4{};
		cube4.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		cube4.getComponent<Jade::Transform>()->Translate(-1.0f, 0.0f, 2.0).Rotate(glm::vec3(1.0, 0.0, 1.0), 60.0f).Scale(0.25);
		addGameobject(cube4);

		Jade::Gameobject cube5{};
		cube5.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::Material(container2, container2_Specular, 32.0f) });
		cube5.getComponent<Jade::Transform>()->Translate(0, -3, 0);
		addGameobject(cube5);

		Jade::Gameobject cube6{};
		cube6.addComponent(Jade::PhongRenderingComponent{ Jade::CUBE, Jade::MaterialCreator::SpecifiedMaterial(Jade::Colour(61, 52, 191)) });
		cube6.getComponent<Jade::Transform>()->Translate(0, -4.0f + 0.2f, 0).Scale(5, 0 ,5);
		addGameobject(cube6);

		lightBox.addComponent(Jade::SolidRenderingComponent{ Jade::CUBE, Jade::Colour(255, 255, 255) });
		lightBox.getComponent<Jade::Transform>()->Translate(pointLight.getComponent<Jade::Transform>()->position);
		addGameobject(lightBox);
	}

	void Update() override {
		if (Jade::gKeyboard.KEY_ESCAPE) {
			stop();
		}

		float velocity = 10.0f * (float)Jade::gTime.deltaTime;

		if (Jade::gKeyboard.KEY_UP) {
			pointLight.getComponent<Jade::Transform>()->position -= glm::vec3{ 0, 0, 1 } *velocity;
			lightBox.getComponent<Jade::Transform>()->position -= glm::vec3{ 0, 0, 1 } * velocity;
		}

		if (Jade::gKeyboard.KEY_LEFT) {
			pointLight.getComponent<Jade::Transform>()->position -= glm::vec3{ 1, 0, 0 } * velocity;
			lightBox.getComponent<Jade::Transform>()->position -= glm::vec3{ 1, 0, 0 } * velocity;
		}

		if (Jade::gKeyboard.KEY_DOWN) {
			pointLight.getComponent<Jade::Transform>()->position += glm::vec3{ 0, 0, 1 } * velocity;
			lightBox.getComponent<Jade::Transform>()->position += glm::vec3{ 0, 0, 1 } * velocity;
		}

		if (Jade::gKeyboard.KEY_RIGHT) {
			pointLight.getComponent<Jade::Transform>()->position += glm::vec3{ 1, 0, 0 } * velocity;
			lightBox.getComponent<Jade::Transform>()->position += glm::vec3{ 1, 0, 0 } * velocity;
		}

		if (Jade::gKeyboard.KEY_O) {
			pointLight.getComponent<Jade::Transform>()->position += glm::vec3{ 0, 1, 0 } * velocity;
			lightBox.getComponent<Jade::Transform>()->position += glm::vec3{ 0, 1, 0 } * velocity;
		}

		if (Jade::gKeyboard.KEY_L) {
			pointLight.getComponent<Jade::Transform>()->position -= glm::vec3{ 0, 1, 0 } * velocity;
			lightBox.getComponent<Jade::Transform>()->position -= glm::vec3{ 0, 1, 0 } * velocity;
		}
	}
};