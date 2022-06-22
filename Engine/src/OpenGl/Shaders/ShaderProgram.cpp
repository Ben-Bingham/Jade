#include "Jade.h"

#include "OpenGL/Shaders/VertexShader.h"
#include "OpenGL/Shaders/FragmentShader.h"
#include "OpenGL/Shaders/ShaderProgram.h"

namespace Jade {
	namespace OpenGL {
		namespace Shaders {
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
	}
}