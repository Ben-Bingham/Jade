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

// Function callbacks
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

// Helper functions
void porcessInput(GLFWwindow* window);

int main() {
	// GLFW and GLEW init
	Jade::Window window(screenWidth, screenHeight, "Sandbox");

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
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
	Jade::Transform cubeTransfrom;

	// Vertex array object
	Jade::VertexAttributeObject VAO;

	// Vertex buffer object
	Jade::VertexBufferObject VBO(cubeVerticies, sizeof(cubeVerticies));

	// Vertex attribute pointers
	Jade::VertexAttributePointer positionData(3, GL_FLOAT);
	Jade::VertexAttributePointer texCordData(2, GL_FLOAT);

	std::vector<Jade::VertexAttributePointer> attributePointers = {
		positionData,
		texCordData
	};

	VAO.addAttributePointers(attributePointers);

	// Vertex shader
	Jade::VertexShader vertexShader(Jade::TextFile("assets\\shaders\\default.vert"));

	// Fragment shader
	Jade::FragmentShader fragmentShader(Jade::TextFile("assets\\shaders\\default.frag"));

	// Shader program
	Jade::ShaderProgram shaderProgram(fragmentShader, vertexShader);

	// Texture setup
	Jade::Texture texture1("assets\\textures\\container.jpg");
	Jade::Texture texture2("assets\\textures\\awesomeface.png");

	shaderProgram.use();
	shaderProgram.setInt("texture1", 0);
	shaderProgram.setInt("texture2", 1);

	Jade::Texture::activateUnit(0);
	texture1.bind();
	Jade::Texture::activateUnit(1);
	texture2.bind();

	// ======================== Light =======================
	//Jade::VertexAttributeObject lightVAO;
	//Jade::VertexBufferObject lightVBO(lightVerticies, sizeof(lightVerticies));

	//Jade::VertexAttributePointer lightPositonData(3, GL_FLOAT);

	//VAO.addAttributePointer(lightPositonData);



	// Check for errors
	glCheckError();

	// Matrix setup

	glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	
	// Render loop

	while (!window.getWindowShouldClose()) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		porcessInput(window.getWindow());

		window.pollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cubeTransfrom.clearMatrix();
		cubeTransfrom.rotate(Jade::Rotation{ glm::vec3(0.5f, 1.0f, 0.0f), (float)glfwGetTime() * glm::radians(50.0f) });

		glm::mat4 view;
		view = camera.getViewMatrix();

		shaderProgram.use();

		shaderProgram.setMatrix4f("model", cubeTransfrom.getMatrix());
		shaderProgram.setMatrix4f("view", view);
		shaderProgram.setMatrix4f("projection", projection);

		VAO.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

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
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	screenWidth = width;
	screenHeight = height;

	projection = glm::perspective(glm::radians(camera.getFOV()), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f); //TODO objects seem to stretch when window is resized
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos; // reversed since y-coordinates range from bottom to top
	lastX = xPos;
	lastY = yPos;

	camera.processMouseMovement(xOffset, yOffset);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	camera.processScollWheel(yOffset);
}