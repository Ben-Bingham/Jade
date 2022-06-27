#include "Jade.h"

#include "Low Level Rendering/Shaders/VertexShader.h"
#include "Low Level Rendering/Shaders/FragmentShader.h"
#include "Low Level Rendering/Shaders/ShaderProgram.h"

namespace Jade {
	ShaderProgram::ShaderProgram(FragmentShader& fragmentShader, VertexShader& vertexShader) {
		m_Shaders.push_back(&fragmentShader);
		m_Shaders.push_back(&vertexShader);

		int success;
		char infoLog[512];

		m_Program = glCreateProgram();

		std::vector<Shader*>::iterator it;
		for (it = m_Shaders.begin(); it != m_Shaders.end(); it++) {
			glAttachShader(m_Program, (*it)->getShader());
		}

		glLinkProgram(m_Program);

		glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
			LOGGER.log("Shader program failed to link", Jade::ERROR);
			LOGGER.log(infoLog, Jade::ERROR);
		}

		for (it = m_Shaders.begin(); it != m_Shaders.end(); it++) {
			(*it)->dispose();
		}
	}
}