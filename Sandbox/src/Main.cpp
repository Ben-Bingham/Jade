#include <glm/glm.hpp>

#include "High Level Rendering/Rule Sets/StandardRenderingRuleSet.h"
#include "High Level Rendering/Rule Sets/SolidRenderingRuleSet.h"
#include "High Level Rendering/Rule Sets/TextureRenderingRuleSet.h"
#include "High Level Rendering/Rule Sets/DiffuseRenderingRuleSet.h"
#include "High Level Rendering/Renderable Objects/StandardRenderableObject.h"
#include "High Level Rendering/Renderable Objects/SolidRenderableObject.h"
#include "High Level Rendering/Renderable Objects/TexturedRenderableObject.h"
#include "High Level Rendering/Renderable Objects/DiffuseRenderableObject.h"
#include "Engine Structure/Application.h"

class Game : public Application {
	Jade::Camera& camera = getCamera();

	float cameraSpeed = 0.4f;
	float mouseSensitivity = 0.1f;

	int lastX = WINDOW.getWidth();
	int lastY = WINDOW.getHeight();

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

		camera.front = glm::vec3(0.0f);
		camera.front = glm::normalize(direction);

		if (KEYBOARD.getKeyPressed(Jade::KEY_W)) {
			camera.getTransform().position += camera.front * cameraSpeed;
		}

		if (KEYBOARD.getKeyPressed(Jade::KEY_A)) {
			camera.getTransform().position -= camera.right * cameraSpeed;
		}

		if (KEYBOARD.getKeyPressed(Jade::KEY_S)) {
			camera.getTransform().position -= camera.front * cameraSpeed;
		}

		if (KEYBOARD.getKeyPressed(Jade::KEY_D)) {
			camera.getTransform().position += camera.right * cameraSpeed;
		}

		if (KEYBOARD.getKeyPressed(Jade::KEY_SPACE)) {
			camera.getTransform().position += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
		}

		if (KEYBOARD.getKeyPressed(Jade::KEY_LEFT_SHIFT)) {
			camera.getTransform().position -= glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
		}
	}

	Jade::Model backpack = Jade::Model("assets\\models\\backpack\\backpack.obj", false);
	Jade::Texture backpackDiffuse = Jade::Texture(*backpack.getDiffuseImage());
	Jade::Texture backpackSpecular = Jade::Texture(*backpack.getSpecularImage());

	Jade::Model texturedCube = Jade::Model("assets\\models\\texturedCube\\Textured_Cube.obj", true);
	Jade::Texture texturedCubeDiffuse = Jade::Texture(*texturedCube.getDiffuseImage());

	Jade::Texture containerDiffuse = Jade::Texture(Jade::Image("assets\\textures\\container2.png"));
	Jade::Texture containerSpecular = Jade::Texture(Jade::Image("assets\\textures\\container2_specular.png"));

	Jade::StandardRuleSet standardRuleSet;
	Jade::TextureRuleSet texturedRuleSet;
	Jade::DiffuseRuleSet diffuseRuleset;
	Jade::SolidRuleSet solidRuleset;

	glm::vec3 lightPositon = glm::vec3(1.2f, 1.0f, 2.0f);

	Jade::PointLight pointLight = Jade::LightCreator::DefaultPointLight();
	Jade::DirectionalLight directionalLight = Jade::LightCreator::DefaultDirectionalLight();

	void initRulesets() {
		pointLight.position = lightPositon;

		standardRuleSet.addPointLight(pointLight);
		standardRuleSet.setDirectionalLight(directionalLight);

		texturedRuleSet.addPointLight(pointLight);
		texturedRuleSet.setDirectionalLight(directionalLight);

		diffuseRuleset.addPointLight(pointLight);
		diffuseRuleset.setDirectionalLight(directionalLight);

		addRuleset(&standardRuleSet);
		addRuleset(&texturedRuleSet);
		addRuleset(&diffuseRuleset);
		addRuleset(&solidRuleset);
	}

	Jade::StandardRenderable standardCube = Jade::StandardRenderable(Jade::CUBE);
	Jade::StandardRenderable standardPyramid = Jade::StandardRenderable(Jade::PYRAMID);

	Jade::TexturedRenderable texturedCubeRenderable = Jade::TexturedRenderable(containerDiffuse, containerSpecular, 32.0f, Jade::CUBE);
	Jade::TexturedRenderable texturedPyramid = Jade::TexturedRenderable(containerDiffuse, containerSpecular, 32.0f, Jade::PYRAMID);

	Jade::DiffusedRenderable diffuesdCube = Jade::DiffusedRenderable(containerDiffuse, glm::vec3(1.0f), 32.0, Jade::CUBE);
	Jade::DiffusedRenderable diffuesdPyramid = Jade::DiffusedRenderable(containerDiffuse, glm::vec3(1.0f), 32.0, Jade::PYRAMID);

	Jade::SolidRenderable solidCube = Jade::SolidRenderable(Jade::Colour(146, 59, 148), Jade::CUBE);
	Jade::SolidRenderable solidPyramid = Jade::SolidRenderable(Jade::Colour(36, 107, 32), Jade::PYRAMID);
	Jade::SolidRenderable light = Jade::SolidRenderable(Jade::Colour(255, 255, 255));

	std::vector<Jade::StandardRenderable> backpackStandardRenderables;
	std::vector<Jade::TexturedRenderable> backpackTexturedRenderables;

	void initRenderables() {
		for each (Jade::Mesh mesh in backpack.getMeshes()) {
			backpackStandardRenderables.push_back(Jade::StandardRenderable(mesh));
		}

		std::vector<Jade::StandardRenderable>::iterator it;
		for (it = backpackStandardRenderables.begin(); it != backpackStandardRenderables.end(); it++) {
			addRenderable(&(*it));
			it->getTransform().position = glm::vec3(0.0f, 1.0f, 5.0f);
		}

		for each (Jade::Mesh mesh in backpack.getMeshes()) {
			backpackTexturedRenderables.push_back(Jade::TexturedRenderable(backpackDiffuse, backpackSpecular, 32.0f, mesh));
		}

		std::vector<Jade::TexturedRenderable>::iterator it2;
		for (it2 = backpackTexturedRenderables.begin(); it2 != backpackTexturedRenderables.end(); it2++) {
			addRenderable(&(*it2));
			it2->getTransform().position = glm::vec3(4.0f, 1.0f, 5.0f);
		}

		standardCube.getTransform().position = glm::vec3(2, 0, -3);
		standardPyramid.getTransform().position = glm::vec3(2, 2, -3);

		addRenderable(&standardCube);
		addRenderable(&standardPyramid);

		texturedCubeRenderable.getTransform().position = glm::vec3(1, 0, -3);
		texturedPyramid.getTransform().position = glm::vec3(1, 2, -3);

		addRenderable(&texturedCubeRenderable);
		addRenderable(&texturedPyramid);

		diffuesdCube.getTransform().position = glm::vec3(0, 0, -3);
		diffuesdPyramid.getTransform().position = glm::vec3(0, 2, -3);

		addRenderable(&diffuesdCube);
		addRenderable(&diffuesdPyramid);

		solidCube.getTransform().position = glm::vec3(-1, 0, -3);
		solidPyramid.getTransform().position = glm::vec3(-1, 2, -3);

		addRenderable(&solidCube);
		addRenderable(&solidPyramid);

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
	Game game;
	game.start();

	return 0;
}
