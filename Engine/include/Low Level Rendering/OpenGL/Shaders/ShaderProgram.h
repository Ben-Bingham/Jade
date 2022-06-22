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

			private:
				unsigned int m_Program;
				std::vector<Shader*> m_Shaders;
			};
		}
	}
}