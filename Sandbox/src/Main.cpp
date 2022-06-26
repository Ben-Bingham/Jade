#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Jade.h"

#include "Low Level Rendering/GLFW/GLFW.h"
#include "Low Level Rendering/OpenGL/OpenGL.h"
#include "Core Systems/Logging/OpenGLErrors.h"
#include "Core Systems/Resource Pipeline/Resources.h"

// Global variables
unsigned int screenWidth = 640;
unsigned int screenHeight = 480;

glm::mat4 projection;

float deltaTime;
float lastFrame;

// Function callbacks
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

// Helper functions
void porcessInput(GLFWwindow* window);

// Camera setup
const float cameraSpeed = 2.5f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

int main() {
	// GLFW and GLEW init
	Window window(screenWidth, screenHeight, "Sandbox");

	glfwSetFramebufferSizeCallback(window.getWindow(), framebufferSizeCallback);

	if (glewInit() != GLEW_OK) {
		LOGGER.log("GLEW failed to initilize.", Jade::ERROR);
	}

	// OpenGL settings
	glEnable(GL_DEPTH_TEST);

	// Uncomment for wireframe rendering
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	// Render init

	// Vertex array object
	VertexAttributeObject VAO;

	// Vertex buffer object

	float vertices[] = {
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

	VertexBufferObject VBO(vertices, sizeof(vertices));

	// Vertex attribute pointers
	VertexAttributePointer positionData(3, GL_FLOAT);
	VertexAttributePointer texCordData(2, GL_FLOAT);

	std::vector<VertexAttributePointer> attributePointers = {
		positionData,
		texCordData
	};

	VAO.addAttributePointers(attributePointers);

	// Vertex shader
	VertexShader vertexShader("assets\\shaders\\default.vert");

	// Fragment shader
	FragmentShader fragmentShader("assets\\shaders\\default.frag");

	// Shader program
	ShaderProgram shaderProgram(fragmentShader, vertexShader);

	// Texture setup
	Texture texture1("assets\\textures\\container.jpg");
	Texture texture2("assets\\textures\\awesomeface.png");

	shaderProgram.use();
	shaderProgram.setInt("texture1", 0);
	shaderProgram.setInt("texture2", 1);

	Texture::activateUnit(0);
	texture1.bind();
	Texture::activateUnit(1);
	texture2.bind();

	// Check for errors
	glCheckError();

	// Matrix setup

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	
	// Render loop

	while (!window.getWindowShouldClose()) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		porcessInput(window.getWindow());

		window.pollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		shaderProgram.use();

		shaderProgram.setMatrix4f("model", model);
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
		cameraPos += cameraSpeed * cameraFront * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	screenWidth = width;
	screenHeight = height;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
}