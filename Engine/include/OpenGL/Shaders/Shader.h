#pragma once
#include "Shaders.h"

namespace Jade {
	namespace OpenGL {
		namespace Shaders {
			class Shader {
			public:
				Shader() {}
				virtual void dispose() = 0;
				virtual unsigned int getShader() = 0;

			private:
				unsigned int m_Shader;
				Jade::Resources::TextFile m_ShaderSourceFile;
			};
		}
	}
}