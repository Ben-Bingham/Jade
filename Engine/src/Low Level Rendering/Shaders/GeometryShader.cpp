#include <GL/glew.h>

#include "Core Systems/Logging/Log.h"

#include "Low Level Rendering/Shaders/GeometryShader.h"

#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	GeometryShader::GeometryShader(const Jade::TextFile& shaderSourceFile)
		: Shader(glCreateShader(GL_GEOMETRY_SHADER), shaderSourceFile) {

		std::string shaderSource = getShaderSourceFile().getContent();
		const char* charShaderSource = shaderSource.c_str();

		glShaderSource(getShader(), 1, &charShaderSource, NULL);
		glCompileShader(getShader());

		int success;
		char infoLog[512];
		glGetShaderiv(getShader(), GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(getShader(), 512, NULL, infoLog);
			LOG("Geometry shader failed to compile", Jade::ERROR);
			LOG(infoLog, Jade::ERROR);
		}
	}
}