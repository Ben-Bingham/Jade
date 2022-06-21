#pragma once
#include <GL/glew.h>

#include "Jade.h"

#include "Resource Pipeline/TextFile.h"

class VertexShader {
public:
	VertexShader(Jade::Resources::TextFile& shaderSourceFile) 
		: m_Shader(glCreateShader(GL_VERTEX_SHADER)), m_ShaderSourceFile(shaderSourceFile) {

		std::string shaderSource = m_ShaderSourceFile.getContent();
		const char* charShaderSource = shaderSource.c_str();

		glShaderSource(m_Shader, 1, &charShaderSource, NULL);
		glCompileShader(m_Shader);

		int success;
		char infoLog[512];
		glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(m_Shader, 512, NULL, infoLog);
			LOGGER.log("Vertex shader failed to compile", Jade::ERROR);
			LOGGER.log(infoLog, Jade::ERROR);
		}
	}
	
	~VertexShader() {
		dispose();
	}

	void dispose() {
		glDeleteShader(m_Shader);
	}

	unsigned int getShader() { return m_Shader; }

private:
	unsigned int m_Shader;
	Jade::Resources::TextFile m_ShaderSourceFile;
};