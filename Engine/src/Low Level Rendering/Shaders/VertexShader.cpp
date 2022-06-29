#include <GL/glew.h>

#include "Jade.h"

#include "Low Level Rendering/Shaders/VertexShader.h"

#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	VertexShader::VertexShader(const Jade::TextFile& shaderSourceFile) {
		setShader(glCreateShader(GL_VERTEX_SHADER));
		setShaderSourceFile(shaderSourceFile);

		std::string shaderSource = getShaderSourceFile().getContent();
		const char* charShaderSource = shaderSource.c_str();

		glShaderSource(getShader(), 1, &charShaderSource, NULL);
		glCompileShader(getShader());

		int success;
		char infoLog[512];
		glGetShaderiv(getShader(), GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(getShader(), 512, NULL, infoLog);
			LOGGER.log("Vertex shader failed to compile", Jade::ERROR);
			LOGGER.log(infoLog, Jade::ERROR);
		}
	}
}