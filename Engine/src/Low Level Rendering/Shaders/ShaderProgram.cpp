#include "Core Systems/Logging/Log.h"

#include "Low Level Rendering/Shaders/VertexShader.h"
#include "Low Level Rendering/Shaders/FragmentShader.h"
#include "Low Level Rendering/Shaders/ShaderProgram.h"
#include "Core Systems/Logging/OpenGLErrors.h"

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
			LOG("Shader program failed to link", Jade::ERROR);
			LOG(infoLog, Jade::ERROR);
		}

		for (it = m_Shaders.begin(); it != m_Shaders.end(); it++) {
			(*it)->dispose();
		}
	}

	ShaderProgram::ShaderProgram(FragmentShader& fragmentShader, VertexShader& vertexShader, GeometryShader& geometryShader) {
		m_Shaders.push_back(&fragmentShader);
		m_Shaders.push_back(&vertexShader);
		m_Shaders.push_back(&geometryShader);

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
			LOG("Shader program failed to link", Jade::ERROR);
			LOG(infoLog, Jade::ERROR);
		}

		for (it = m_Shaders.begin(); it != m_Shaders.end(); it++) {
			(*it)->dispose();
		}
	}
}