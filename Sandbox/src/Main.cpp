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
#include "Low Level Rendering/Rendering Objects/Camera.h"
#include "Low Level Rendering/GLEW.h"
#include "High Level Rendering/Transform.h"

// Global variables
unsigned int screenWidth = 1920;
unsigned int screenHeight = 1080;

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

// Helper functions
void porcessInput(GLFWwindow* window);

int main() {
	// GLFW and GLEW init
	Jade::Window window(screenWidth, screenHeight, "Sandbox", true);

	window.addFrameBufferSizeCallback(framebufferSizeCallback);
	window.addMousePositionCallback(mouseCallback);
	window.addScrollWheelCallback(scrollCallback);
	window.disableCursor();

	Jade::GLEW glew;

	// OpenGL settings
	glEnable(GL_DEPTH_TEST);

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
	 
	// ======================== Cube ========================
	// Transform
	Jade::Transform cubeTransform;

	// Vertex array object
	Jade::VertexAttributeObject VAO;

	// Vertex buffer object
	Jade::VertexBufferObject VBO(cubeVerticies, sizeof(cubeVerticies));

	// Vertex attribute pointers
	Jade::VertexAttributePointer positionData(3, GL_FLOAT);
	//Jade::VertexAttributePointer texCordData(2, GL_FLOAT);
	Jade::VertexAttributePointer normalData(3, GL_FLOAT);

	std::vector<Jade::VertexAttributePointer> attributePointers = {
		positionData,
		normalData
	};

	VAO.addAttributePointers(attributePointers);

	// Vertex shader
	Jade::VertexShader vertexShader(Jade::TextFile("assets\\shaders\\default.vert"));

	// Fragment shader
	Jade::FragmentShader fragmentShader(Jade::TextFile("assets\\shaders\\default.frag"));

	// Shader program
	Jade::ShaderProgram shaderProgram(fragmentShader, vertexShader);

	shaderProgram.use();
	shaderProgram.setVector3f("objectColour", glm::vec3(1.0f, 0.5f, 0.31f));
	shaderProgram.setVector3f("lightColour", glm::vec3(1.0f, 1.0f, 1.0f));
	shaderProgram.setVector3f("lightPosition", lightPositon);

	// Texture setup
	//Jade::Texture texture1("assets\\textures\\container.jpg");
	//Jade::Texture texture2("assets\\textures\\awesomeface.png");

	//shaderProgram.use();
	//shaderProgram.setInt("texture1", 0);
	//shaderProgram.setInt("texture2", 1);

	//Jade::Texture::activateUnit(0);
	//texture1.bind();
	//Jade::Texture::activateUnit(1);
	//texture2.bind();

	// ======================== Light =======================
	Jade::Transform lightTransform;
	lightTransform.translate(lightPositon);
	lightTransform.scale(0.2f);

	Jade::VertexAttributeObject lightVAO;
	Jade::VertexBufferObject lightVBO(lightVerticies, sizeof(lightVerticies));

	Jade::VertexAttributePointer lightPositonData(3, GL_FLOAT);

	lightVAO.setAttributePointer(lightPositonData);

	Jade::VertexShader lightVertexShader(Jade::TextFile("assets\\shaders\\light.vert"));
	Jade::FragmentShader lightFragmentShader(Jade::TextFile("assets\\shaders\\light.frag"));

	Jade::ShaderProgram lightShaderProgram(lightFragmentShader, lightVertexShader);	

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

		// ======================== Cube ========================
		cubeTransform.clearMatrix();
		cubeTransform.rotate(Jade::Rotation{ glm::vec3(0.5f, 1.0f, 0.0f), (float)glfwGetTime() * 50.0f });

		shaderProgram.use();

		shaderProgram.setMatrix4f("model", cubeTransform.getMatrix());
		shaderProgram.setMatrix4f("view", view);
		shaderProgram.setMatrix4f("projection", projection);

		VAO.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ======================== Light =======================
		lightShaderProgram.use();

		lightShaderProgram.setMatrix4f("model", lightTransform.getMatrix());
		lightShaderProgram.setMatrix4f("view", view);
		lightShaderProgram.setMatrix4f("projection", projection);

		lightVAO.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Render cleanup

		window.swapBuffers();
		glCheckError();
	}

	// Cleanup

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