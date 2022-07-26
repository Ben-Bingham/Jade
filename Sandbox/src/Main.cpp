#include <glm/glm.hpp>

#include "High Level Rendering/PShaders/PShader.h"
#include "High Level Rendering/PShaders/PhongShader.h"
#include "High Level Rendering/PShaders/SolidShader.h"
#include "High Level Rendering/Renderable Objects/SolidRenderableObject.h"
#include "High Level Rendering/Renderable Objects/PhongRenderableObject.h"
#include "High Level Rendering/MaterialCreator.h"
#include "High Level Rendering/LightCreator.h"
#include "Engine Structure/Application.h"

class Game : public Application {
	float cameraSpeed = 0.4f;
	float mouseSensitivity = 0.1f;

	int lastX = WINDOW.getWidth();
	int lastY = WINDOW.getHeight();

	int lastScrollOffset = 0;

	float yaw = 0.0f;
	float pitch = 0.0f;

	void cameraMovement() {
		float xOffset = (float)(MOUSE.getXPosition() - lastX);
		float yOffset = (float)(lastY - MOUSE.getYPosition());
		lastX = MOUSE.getXPosition();
		lastY = MOUSE.getYPosition();

		xOffset *= mouseSensitivity;
		yOffset *= mouseSensitivity;

		yaw += xOffset;
		pitch += yOffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		CAMERA.front = glm::vec3(0.0f);
		CAMERA.front = glm::normalize(direction);

		if (KEYBOARD.getKeyPressed(Jade::KEY_W)) { //TODO delta time
			CAMERA.getTransform().position += CAMERA.front * cameraSpeed;
		}

		if (KEYBOARD.getKeyPressed(Jade::KEY_A)) {
			CAMERA.getTransform().position -= CAMERA.right * cameraSpeed;
		}

		if (KEYBOARD.getKeyPressed(Jade::KEY_S)) {
			CAMERA.getTransform().position -= CAMERA.front * cameraSpeed;
		}

		if (KEYBOARD.getKeyPressed(Jade::KEY_D)) {
			CAMERA.getTransform().position += CAMERA.right * cameraSpeed;
		}

		if (KEYBOARD.getKeyPressed(Jade::KEY_SPACE)) {
			CAMERA.getTransform().position += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
		}

		if (KEYBOARD.getKeyPressed(Jade::KEY_LEFT_SHIFT)) {
			CAMERA.getTransform().position -= glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
		}

		int scrollOffset = MOUSE.getScrollOffset();

		if (scrollOffset != lastScrollOffset) {
			cameraSpeed += scrollOffset * 0.01f;	
		}

		if (cameraSpeed <= 0) {
			cameraSpeed = 0.04f;
		}

		lastScrollOffset = scrollOffset;
	}

	Jade::Model backpack = Jade::Model("assets\\models\\backpack\\backpack.obj", true);

	Jade::Model bike = Jade::Model("assets\\models\\bike\\swapfiets.obj", true);

	Jade::SolidShader solidRuleset;
	Jade::PhongShader phongRuleset;

	glm::vec3 lightPositon = glm::vec3(1.2f, 1.0f, 10.0f);

	Jade::PointLight pointLight = Jade::LightCreator::DefaultPointLight();
	Jade::DirectionalLight directionalLight = Jade::LightCreator::DefaultDirectionalLight();

	void initRulesets() {
		pointLight.position = lightPositon;

		phongRuleset.addDirectionalLight(directionalLight);
		phongRuleset.addPointLight(pointLight);

		addRuleset(&solidRuleset);
		addRuleset(&phongRuleset);
	}

	Jade::Texture containerDiffuse = Jade::Image("assets\\textures\\container2.png");
	Jade::Texture containerSpecular = Jade::Image("assets\\textures\\container2_specular.png");

	Jade::Material containerMaterial = Jade::Material(containerDiffuse, containerSpecular, 255.0f);
	Jade::PhongRenderable containerCube = Jade::PhongRenderable(&containerMaterial, Jade::CUBE);
	Jade::PhongRenderable containerPyramid = Jade::PhongRenderable(&containerMaterial, Jade::PYRAMID);

	Jade::Material standardMaterial = Jade::MaterialCreator::DefaultMaterial();
	Jade::PhongRenderable standardCube = Jade::PhongRenderable(&standardMaterial, Jade::CUBE);
	Jade::PhongRenderable standardPyramid = Jade::PhongRenderable(&standardMaterial, Jade::PYRAMID);

	Jade::SolidRenderable solidCube = Jade::SolidRenderable(Jade::Colour(146, 59, 148), Jade::CUBE);
	Jade::SolidRenderable solidPyramid = Jade::SolidRenderable(Jade::Colour(36, 107, 32), Jade::PYRAMID);
	Jade::SolidRenderable light = Jade::SolidRenderable(Jade::Colour(255, 255, 255));

	std::vector<Jade::PhongRenderable> backpackRenderables;
	std::vector<Jade::Material> backpackMaterials;

	std::vector<Jade::PhongRenderable> bikeRenderables;
	std::vector<Jade::Material> bikeMaterials;


	void initRenderables() {
		for (const Jade::AssimpMaterial& material : backpack.getMaterials()) {
			backpackMaterials.push_back(Jade::Material(material));
		}

		for each (Jade::Mesh mesh in backpack.getMeshes()) {
			backpackRenderables.push_back(Jade::PhongRenderable(&backpackMaterials[mesh.getMaterialIndex()], mesh));
		}

		std::vector<Jade::PhongRenderable>::iterator it;
		for (it = backpackRenderables.begin(); it != backpackRenderables.end(); it++) {
			addRenderable(&(*it));
			it->getTransform().position = glm::vec3(0.0f, 1.0f, 5.0f);
		}

		for (const Jade::AssimpMaterial& material : bike.getMaterials()) {
			bikeMaterials.push_back(Jade::Material(material));
		}

		for each (Jade::Mesh mesh in bike.getMeshes()) {
			bikeRenderables.push_back(Jade::PhongRenderable(&bikeMaterials[mesh.getMaterialIndex()], mesh));
		}

		std::vector<Jade::PhongRenderable>::iterator it2;
		for (it2 = bikeRenderables.begin(); it2 != bikeRenderables.end(); it2++) {
			addRenderable(&(*it2));
			it2->getTransform().position = glm::vec3(-10.0f, 1.0f, 5.0f);
		}

		solidCube.getTransform().position = glm::vec3(-1, 0, -3);
		solidPyramid.getTransform().position = glm::vec3(-1, 2, -3);

		addRenderable(&solidCube);
		addRenderable(&solidPyramid);

		standardCube.getTransform().position = glm::vec3(0, 0, -3);
		standardPyramid.getTransform().position = glm::vec3(0, 2, -3);

		addRenderable(&standardCube);
		addRenderable(&standardPyramid);

		containerCube.getTransform().position = glm::vec3(1, 0, -3);
		containerPyramid.getTransform().position = glm::vec3(1, 2, -3);

		addRenderable(&containerCube);
		addRenderable(&containerPyramid);

		light.getTransform().position = lightPositon;
		light.getTransform().scale = glm::vec3(0.2f);
		addRenderable(&light);
	}

	void Begin() override {
		WINDOW.disableCursor();

		initRulesets();
		initRenderables();
	}

	void Update() override {
		if (KEYBOARD.getKeyPressed(Jade::KEY_ESCAPE)) {
			quit();
		}

		cameraMovement();
	}
};

int main() {
	Jade::Image pic{ "assets\\textures\\container2.png" };

	Game game;
	game.start();

	return 0;
}
