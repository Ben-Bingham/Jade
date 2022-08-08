#pragma once

#include "Jade.h"

#include "Entity Component System/Components/FPSController.h"

class DemoScene : public Jade::Scene {
public:
	Jade::DirectionalLight dirLight{};
	Jade::Gameobject lightBox{};

	void Begin() override {
		Jade::Model backpack{ "assets\\models\\backpack\\backpack.obj", false };

		//Jade::Gameobject demoCube{};
		//Jade::Gameobject lightBox{};
		//Jade::PointLight light{};

		//Jade::PhongRenderingComponent demoCubeRenderingComponent{ Jade::CUBE, Jade::MaterialCreator::DefaultMaterial() };

		//Jade::SolidRenderingComponent lightBoxRenderingComponent{ Jade::CUBE, Jade::Colour(255, 255, 255) };

		//demoCube.addComponent(demoCubeRenderingComponent);
		//lightBox.addComponent(lightBoxRenderingComponent);

		//lightBox.getComponent<Jade::Transform>()->Translate(2.0f, 4.0f, -2.0f).Scale(0.2f);
		//light.getComponent<Jade::Transform>()->Translate(1.0f, 2.0f, -1.0f);

		//addGameobject(demoCube);
		//addGameobject(lightBox);
		//addGameobject(light);
		dirLight.getComponent<Jade::Transform>()->Translate(-2.0f, 4.0f, -1.0f);
		//dirLight.direction = glm::normalize(glm::vec3(-1, -1, 0));
		//dirLight.direction = glm::vec3{-0.5, -0.5, -0.5};
		dirLight.diffuse = Jade::Colour(1.0f, 1.0f, 1.0f);
		dirLight.ambient = Jade::Colour(0.1f, 0.1f, 0.1f);
		dirLight.specular = Jade::Colour(0.2f, 0.2f, 0.2f);
		addGameobject(dirLight);

		Jade::Gameobject backpackObject{};
		backpackObject.addComponent(Jade::PhongRenderingComponent{ backpack });
		backpackObject.getComponent<Jade::Transform>()->Translate(5, 0, 0);
		addGameobject(backpackObject);

		Jade::Camera camera;
		Jade::Engine::setCamera(camera);

		Jade::FPSController fpsController;
		camera.addComponent(fpsController);

		addGameobject(camera);

		Jade::Image container2{ "assets\\textures\\container2.png" };
		Jade::Image container2_Specular{ "assets\\textures\\container2_specular.png" };

		Jade::Gameobject cube1{};
		Jade::Material mat(container2, container2_Specular, 32.0f);
		Jade::PhongRenderingComponent phong { 
			Jade::CUBE, mat
		};
		cube1.addComponent(phong);
		cube1.getComponent<Jade::Transform>()->Translate(0.0f, -4, 0.0).Scale(100, 0, 100);
		addGameobject(cube1);

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

		lightBox.addComponent(Jade::SolidRenderingComponent{ Jade::CUBE, Jade::Colour(43, 234, 52) });
		lightBox.getComponent<Jade::Transform>()->Translate(-2.0f, 4.0f, -1.0f);
		addGameobject(lightBox);
	}

	void Update() override {
		if (Jade::gKeyboard.KEY_ESCAPE) {
			stop();
		}

		float velocity = 10.0f * (float)Jade::gTime.deltaTime;

		if (Jade::gKeyboard.KEY_UP) {
			dirLight.getComponent<Jade::Transform>()->position -= glm::vec3{ 0, 0, 1 } *velocity;
			lightBox.getComponent<Jade::Transform>()->position -= glm::vec3{ 0, 0, 1 } * velocity;
		}

		if (Jade::gKeyboard.KEY_LEFT) {
			dirLight.getComponent<Jade::Transform>()->position -= glm::vec3{ 1, 0, 0 } * velocity;
			lightBox.getComponent<Jade::Transform>()->position -= glm::vec3{ 1, 0, 0 } * velocity;
		}

		if (Jade::gKeyboard.KEY_DOWN) {
			dirLight.getComponent<Jade::Transform>()->position += glm::vec3{ 0, 0, 1 } * velocity;
			lightBox.getComponent<Jade::Transform>()->position += glm::vec3{ 0, 0, 1 } * velocity;
		}

		if (Jade::gKeyboard.KEY_RIGHT) {
			dirLight.getComponent<Jade::Transform>()->position += glm::vec3{ 1, 0, 0 } * velocity;
			lightBox.getComponent<Jade::Transform>()->position += glm::vec3{ 1, 0, 0 } * velocity;
		}

		if (Jade::gKeyboard.KEY_O) {
			dirLight.getComponent<Jade::Transform>()->position += glm::vec3{ 0, 1, 0 } * velocity;
			lightBox.getComponent<Jade::Transform>()->position += glm::vec3{ 0, 1, 0 } * velocity;
		}

		if (Jade::gKeyboard.KEY_L) {
			dirLight.getComponent<Jade::Transform>()->position -= glm::vec3{ 0, 1, 0 } * velocity;
			lightBox.getComponent<Jade::Transform>()->position -= glm::vec3{ 0, 1, 0 } * velocity;
		}
	}
};