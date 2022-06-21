#pragma once
#include <GL/glew.h>

#include "Jade.h"

#include "Resource Pipeline/TextFile.h"
#include "Shader.h"

namespace Jade {
	namespace OpenGL {
		namespace Shaders {
			class FragmentShader : public Shader {
			public:
				FragmentShader(Jade::Resources::TextFile& shaderSourceFile);

				~FragmentShader() {
					dispose();
				}

				void dispose() override { glDeleteShader(m_Shader); }

				unsigned int getShader() override { return m_Shader; }

			private:
				unsigned int m_Shader;
				Jade::Resources::TextFile m_ShaderSourceFile;
			};
		}
	}
}
