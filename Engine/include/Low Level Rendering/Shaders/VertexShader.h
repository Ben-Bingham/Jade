#pragma once
#include <GL/glew.h>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Shader.h"

namespace Jade {
	class VertexShader : public Shader {
	public:
		VertexShader(const Jade::TextFile& shaderSourceFile);

		~VertexShader() {
			dispose();
		}

		void dispose() override{ glDeleteShader(getShader()); }
	};
}