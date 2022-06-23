#pragma once
#include <vector>

#include "Jade.h"

#include "VertexShader.h"
#include "FragmentShader.h"


namespace Jade {
	namespace OpenGL {
		namespace Shaders {
			class ShaderProgram {
			public:
				ShaderProgram(FragmentShader& fragmentShader, VertexShader& vertexShader); 

				~ShaderProgram() { dispose(); }

				void use() { glUseProgram(m_Program); }
				void dispose() { glDeleteProgram(m_Program); }

				void setInt(const std::string& variableName, int value) {
					glUniform1i(glGetUniformLocation(m_Program, variableName.c_str()), value);
				}

			private:
				unsigned int m_Program;
				std::vector<Shader*> m_Shaders;
			};
		}
	}
}