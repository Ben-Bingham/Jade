#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Jade.h"

#include "Low Level Rendering/GLFW/GLFW.h"
#include "Low Level Rendering/OpenGL/OpenGL.h"
#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Core Systems/Logging/OpenGLErrors.h"
#include "Core Systems/Resource Pipeline/Image.h"

int main() {
	// GLFW and GLEW init
	Window window(640, 480, "Sandbox");

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
	VAO.addAttributePointer(VertexAttributePointer(3, GL_FLOAT));

	// Vertex shader
	VertexShader vertexShader("assets\\shaders\\default.vert");

	// Fragment shader
	FragmentShader fragmentShader("assets\\shaders\\default.frag");

	// Shader program
	ShaderProgram shaderProgram(fragmentShader, vertexShader);

	glCheckError();

	// Render loop

	while (!window.getWindowShouldClose()) {
		
		window.pollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();
		VAO.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.swapBuffers();
		glCheckError();
	}

	// Cleanup

	window.dispose();

	return 0;
}