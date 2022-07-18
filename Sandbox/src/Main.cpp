#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Jade.h"

#include "Low Level Rendering/Window.h"
#include "Core Systems/Logging/OpenGLErrors.h"
#include "High Level Rendering/Camera.h"
#include "Low Level Rendering/GLEW.h"
#include "High Level Rendering/Renderer.h"
#include "High Level Rendering/Rule Sets/StandardRenderingRuleSet.h"
#include "High Level Rendering/Rule Sets/SolidRenderingRuleSet.h"
#include "High Level Rendering/Rule Sets/TextureRenderingRuleSet.h"
#include "High Level Rendering/Renderable Objects/StandardRenderableObject.h"
#include "High Level Rendering/Renderable Objects/SolidRenderableObject.h"
#include "High Level Rendering/Renderable Objects/TexturedRenderableObject.h"
#include "High Level Rendering/Renderable Objects/DiffuseRenderableObject.h"
#include "High Level Rendering/Rule Sets/DiffuseRenderingRuleSet.h"
#include "High Level Rendering/Colour.h"
#include "Core Systems/Resource Pipeline/Model.h"

// Global variables
unsigned int screenWidth = 640;
unsigned int screenHeight = 480;

glm::mat4 projection;

float deltaTime;
float lastFrame;

// Camera Globals

float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;

Jade::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool firstMouse = true;

// Light Globals

glm::vec3 lightPositon(1.2f, 1.0f, 2.0f);

// Function callbacks
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
	GLsizei length, const char* message, const void* userParam);

// Helper functions
void processInput(GLFWwindow* window);

int main() {
	// GLFW and GLEW init
	Jade::Window window(screenWidth, screenHeight, "Sandbox", false);

	window.addFrameBufferSizeCallback(framebufferSizeCallback);
	window.addMousePositionCallback(mouseCallback);
	window.addScrollWheelCallback(scrollCallback);
	window.disableCursor();

	Jade::GLEW glew;

	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	
	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		LOGGER.log("OpenGL debug context available", Jade::INFO);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	// Uncomment for wireframe rendering
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ======================== Standard Renderer ========================
	Jade::StandardRuleSet ruleSet;

	Jade::PointLight light = Jade::LightCreator::DefaultPointLight();
	light.position = lightPositon;
	ruleSet.addPointLight(light);
	
	Jade::DirectionalLight directionalLight = Jade::LightCreator::DefaultDirectionalLight();
	ruleSet.setDirectionalLight(directionalLight);

	Jade::Renderer renderer;
	renderer.addRuleSet(&ruleSet);

	Jade::StandardRenderable standardRenderable(Jade::CUBE);

	renderer.addRenderable(&standardRenderable);

	Jade::StandardRenderable standardRenderable2(Jade::PYRAMID);
	standardRenderable2.getTransform().translate(0, 2, 0);

	renderer.addRenderable(&standardRenderable2);

	// ======================== Model Loading testing ========================
	Jade::Model model("assets\\models\\backpack\\backpack.obj", false);
	std::vector<Jade::StandardRenderable> modelRenderables;
	for each (Jade::Mesh mesh in model.getMeshes()) {
		modelRenderables.push_back(Jade::StandardRenderable(mesh));
	}

	std::vector<Jade::StandardRenderable>::iterator it;
	for (it = modelRenderables.begin(); it != modelRenderables.end(); it++) {
		renderer.addRenderable(&(*it));
		it->getTransform().translate(0.0f, 1.0f, 5.0f);
		it->getTransform().rotate(Jade::Rotation{ glm::vec3(0.0f, 1.0f, 0.0f), 180.0f });
	}

	// ======================== Solid Renderer ========================
	Jade::SolidRuleSet solidRuleSet;

	//Jade::Renderer renderer2(&solidRuleSet);
	renderer.addRuleSet(&solidRuleSet);

	Jade::SolidRenderable solidRenderable(Jade::Colour(255, 255, 255));
	solidRenderable.getTransform().translate(lightPositon);
	solidRenderable.getTransform().scale(0.1f);

	renderer.addRenderable(&solidRenderable);

	Jade::SolidRenderable solidRenderable2(Jade::Colour(83, 194, 91));
	solidRenderable2.getTransform().translate(2, 0, 0);

	renderer.addRenderable(&solidRenderable2);

	Jade::SolidRenderable solidRenderable3(Jade::Colour(52, 174, 235), Jade::PYRAMID);
	solidRenderable3.getTransform().translate(2, 2, 0);

	renderer.addRenderable(&solidRenderable3);

	// ======================== Textured Renderer ========================
	Jade::TextureRuleSet textureRuleSet;

	textureRuleSet.addPointLight(light);
	textureRuleSet.setDirectionalLight(directionalLight);

	//Jade::Renderer renderer3(&textureRuleSet);
	renderer.addRuleSet(&textureRuleSet);

	Jade::TexturedRenderable texturedRenderable(Jade::Texture(Jade::Image("assets\\textures\\container2.png")), Jade::Texture(Jade::Image("assets\\textures\\container2_specular.png")), 32.0f);
	texturedRenderable.getTransform().translate(1, 0, 0);
	
	renderer.addRenderable(&texturedRenderable);

	Jade::TexturedRenderable texturedRenderable2(Jade::Texture(Jade::Image("assets\\textures\\container2.png")), Jade::Texture(Jade::Image("assets\\textures\\container2_specular.png")), 32.0f, Jade::PYRAMID);
	texturedRenderable2.getTransform().translate(1, 2, 0);

	renderer.addRenderable(&texturedRenderable2);

	// ======================== Textured Model Loading testing ========================
	Jade::Texture diffuse = Jade::Texture(*model.getDiffuseImage());
	Jade::Texture specular = Jade::Texture(*model.getSpecularImage());

	std::vector<Jade::TexturedRenderable> modelRenderables2;
	for each (Jade::Mesh mesh in model.getMeshes()) {
		modelRenderables2.push_back(Jade::TexturedRenderable(diffuse, specular, 32.0f, mesh));
	}

	std::vector<Jade::TexturedRenderable>::iterator it2;
	for (it2 = modelRenderables2.begin(); it2 != modelRenderables2.end(); it2++) {
		renderer.addRenderable(&(*it2));
		it2->getTransform().translate(4.0f, 1.0f, 5.0f);
		it2->getTransform().rotate(Jade::Rotation{ glm::vec3(0.0f, 1.0f, 0.0f), 180.0f });
	}

	// ======================== Textured Model Loading testing 2 ========================
	Jade::DiffuseRuleSet diffuseRuleSet;

	diffuseRuleSet.addPointLight(light);
	diffuseRuleSet.setDirectionalLight(directionalLight);
	//Jade::Renderer renderer4(&diffuseRuleSet);
	renderer.addRuleSet(&diffuseRuleSet);

	Jade::Model texturedCube("assets\\models\\texturedCube\\Textured_Cube.obj", true);
	diffuse = Jade::Texture(*texturedCube.getDiffuseImage());

	std::vector<Jade::DiffusedRenderable> modelRenderables3;
	for each (Jade::Mesh mesh in texturedCube.getMeshes()) {
		modelRenderables3.push_back(Jade::DiffusedRenderable(diffuse, glm::vec3(1.0f, 1.0f, 1.0f), 32.0f, mesh));
	}

	std::vector<Jade::DiffusedRenderable>::iterator it3;
	for (it3 = modelRenderables3.begin(); it3 != modelRenderables3.end(); it3++) {
		renderer.addRenderable(&(*it3));
		it3->getTransform().translate(4.0f, 4.0f, 5.0f);
	}

	// Check for errors
	glCheckError();

	// Matrix setup

	glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	
	// Render loop

	while (!window.getWindowShouldClose()) {
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window.getWindow());

		window.pollEvents();
		glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view;
		view = camera.getViewMatrix();

		renderer.setMatrices(view, projection);
		renderer.render(camera.getPosition());

		window.swapBuffers();
		glCheckError();
	}

	renderer.dispose();

	window.dispose();

	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.processMovement(Jade::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.processMovement(Jade::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.processMovement(Jade::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.processMovement(Jade::RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.processMovement(Jade::UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.processMovement(Jade::DOWN, deltaTime);
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	screenWidth = width;
	screenHeight = height;

	projection = glm::mat4(1.0f);
	float aspectRatio = (float)width / (float)height;
	projection = glm::perspective(glm::radians(camera.getFOV()), aspectRatio, 0.1f, 100.0f); //TODO objects seem to stretch when window is resized
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = (float)xPos;
		lastY = (float)yPos;
		firstMouse = false;
	}

	float xOffset = (float)xPos - lastX;
	float yOffset = lastY - (float)yPos; // reversed since y-coordinates range from bottom to top
	lastX = (float)xPos;
	lastY = (float)yPos;

	camera.processMouseMovement(xOffset, yOffset);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	camera.processScollWheel(yOffset);
}

void APIENTRY glDebugOutput(
	GLenum source, 
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam) {
	Jade::LogLevel level;
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:			level = Jade::ERROR; break;
	case GL_DEBUG_SEVERITY_MEDIUM:			level = Jade::WARNING; break;
	case GL_DEBUG_SEVERITY_LOW:				level = Jade::WARNING; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:	level = Jade::INFO; break;
	}
	
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
	LOGGER.log("---------------", level);

	std::string string = "Debug message (";
	string += std::to_string(id);
	string += "): ";
	string += message;
	
	LOGGER.log(string, level);

	string = "";
	switch (source) {
	case GL_DEBUG_SOURCE_API:             string += "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   string += "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: string += "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     string += "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     string += "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           string += "Source: Other"; break;
	}
	LOGGER.log(string, level);

	string = "";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:               string += "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: string += "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  string += "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         string += "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         string += "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              string += "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          string += "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           string += "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               string += "Type: Other"; break;
	}
	LOGGER.log(string, level);
	string = "";
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:         string += "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       string += "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          string += "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: string += "Severity: notification"; break;
	}
	LOGGER.log(string, level);
	LOGGER.log("---------------", level);
}