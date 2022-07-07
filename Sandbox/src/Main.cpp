#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Jade.h"

#include "Low Level Rendering/Window.h"
#include "Low Level Rendering/Rendering Objects/RenderingObjectsHeader.h"
#include "Low Level Rendering/Shaders/ShaderHeader.h"
#include "Core Systems/Logging/OpenGLErrors.h"
#include "Core Systems/Resource Pipeline/Resources.h"
#include "High Level Rendering/Camera.h"
#include "Low Level Rendering/GLEW.h"
#include "High Level Rendering/Transform.h"
#include "High Level Rendering/RenderingRuleSet.h"
#include "High Level Rendering/ShaderCreator.h"
#include "High Level Rendering/RenderableObject.h"
#include "High Level Rendering/Renderer.h"
#include "High Level Rendering/StandardRenderingRuleSet.h"

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
void porcessInput(GLFWwindow* window);

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

	// Uncomment for wireframe rendering
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	// Render init
	float cubeVerticies[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	float lightVerticies[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	// ======================== Shader Creator Testing ========================
	Jade::StandardRuleSet ruleSet;

	Jade::Light light;

	light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

	light.position = lightPositon;
	ruleSet.addLight(light);

	ruleSet.createProgram();

	Jade::Renderer renderer(&ruleSet, camera.getViewMatrix(), projection);

	// Object 1
	Jade::RenderableObject renderObject(Jade::CUBE, glm::vec4(0.2f, 0.5f, 0.2f, 1.0f));

	renderer.addRenderable(renderObject);

	// Check for errors
	glCheckError();

	// Matrix setup

	glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	
	// Render loop

	while (!window.getWindowShouldClose()) {
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		porcessInput(window.getWindow());

		window.pollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view;
		view = camera.getViewMatrix();

		renderObject.getTransform().clearMatrix();
		renderObject.getTransform().rotate(Jade::Rotation{ glm::vec3(0.5f, 1.0f, 0.0f), (float)glfwGetTime() * 50.0f });

		renderer.setMatrices(view, projection);
		renderer.getRuleSet()->getProgram().use();
		renderer.getRuleSet()->getProgram().setVector3f("cameraPosition", camera.getPosition());
		renderer.render();

		//Render cleanup
		window.swapBuffers();
		glCheckError();
	}

	renderer.dispose();

	window.dispose();

	return 0;
}

void porcessInput(GLFWwindow* window) {
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