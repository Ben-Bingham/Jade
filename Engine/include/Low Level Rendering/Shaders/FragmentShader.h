#pragma once
#include <GL/glew.h>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Shader.h"

namespace Jade {
	class FragmentShader : public Shader {
	public:
		FragmentShader(const Jade::TextFile& shaderSourceFile);

		FragmentShader(const FragmentShader&) = default;
		FragmentShader(FragmentShader&&) = default;
		FragmentShader& operator=(const FragmentShader&) = default;
		FragmentShader& operator=(FragmentShader&&) = default;
		~FragmentShader() = default;

		void dispose() override { glDeleteShader(getShader()); }
	};
}
