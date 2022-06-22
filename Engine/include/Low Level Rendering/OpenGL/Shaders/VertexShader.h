#pragma once
#include <GL/glew.h>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Shader.h"

namespace Jade {
	namespace OpenGL {
		namespace Shaders {
			class VertexShader : public Shader {
			public:
				VertexShader(Jade::Resources::TextFile& shaderSourceFile);
				VertexShader(std::string& path);
				VertexShader(std::string&& path);

				~VertexShader() {
					dispose();
				}

				void dispose() override{ glDeleteShader(m_Shader); }

				unsigned int getShader() override{ return m_Shader; }

			private:
				unsigned int m_Shader;
				Jade::Resources::TextFile m_ShaderSourceFile;
			};
		}
	}
}