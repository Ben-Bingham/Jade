#pragma once
#include <GL/glew.h>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Shader.h"

namespace Jade {
	class FragmentShader : public Shader {
	public:
		FragmentShader(const Jade::TextFile& shaderSourceFile);

		~FragmentShader() {
			dispose();
		}

		void dispose() override { glDeleteShader(getShader()); }
	};
}
