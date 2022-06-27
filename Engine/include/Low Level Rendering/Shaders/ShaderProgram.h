#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Jade.h"

#include "VertexShader.h"
#include "FragmentShader.h"


namespace Jade {
	class ShaderProgram {
	public:
		ShaderProgram(FragmentShader& fragmentShader, VertexShader& vertexShader); 

		~ShaderProgram() { dispose(); }

		void use() { glUseProgram(m_Program); }
		void dispose() { glDeleteProgram(m_Program); }

		void setInt(const std::string& variableName, const int value) {
			glUniform1i(glGetUniformLocation(m_Program, variableName.c_str()), value);
		}

		void setMatrix4f(const std::string& variableName, const glm::mat4& matrix) {
			glUniformMatrix4fv(glGetUniformLocation(m_Program, variableName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
		}

	private:
		unsigned int m_Program;
		std::vector<Shader*> m_Shaders;
	};
}