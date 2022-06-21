#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Jade.h"

#include "OpenGL/OpenGL.h"

int main() {
	// GLFW and GLEW init

	if (!glfwInit()) {
		LOGGER.log("GLFW failed to initilize.", Jade::ERROR);
	}

	// Minimum required OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Jade", NULL, NULL);
	if (!window) {
		LOGGER.log("GLFW window creation failed.", Jade::ERROR);
		LOGGER.log("OpenGL context creation failed.", Jade::ERROR);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		LOGGER.log("GLEW failed to initilize.", Jade::ERROR);
	}

	// Render init

	// Vertex array object
	VertexAttributeObject VAO;

	// Vertex buffer object
	float vertices[] = {
		-0.5,  0.5,  0.0, // Top left
		 0.5,  0.5,  0.0, // Top right
		 0.5, -0.5,  0.0, // Bottom right
		-0.5, -0.5,  0.0  // Bottom left
	};

	VertexBufferObject VBO(vertices, sizeof(vertices));

	// Element buffer object
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	ElementBufferObject EBO(indices, sizeof(indices));

	// Vertex attribute pointers
	VAO.addAttributePointer(VertexArrtibutePointer(3, GL_FLOAT));

	// Vertex shader
	VertexShader vertexShader(Jade::Resources::TextFile("assets\\shaders\\default.vert"));

	// Fragment shader
	FragmentShader fragmentShader(Jade::Resources::TextFile("assets\\shaders\\default.frag"));

	// Shader program
	int success;
	char infoLog[512];

	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader.getShader());
	glAttachShader(shaderProgram, fragmentShader.getShader());
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		LOGGER.log("Shader program failed to link", Jade::ERROR);
		LOGGER.log(infoLog, Jade::ERROR);
	}

	vertexShader.dispose();
	fragmentShader.dispose();

	// Render loop

	while (!glfwWindowShouldClose(window)) {
		
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		VAO.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

	// Cleanup

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}