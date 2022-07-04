#pragma once
#include <GL/glew.h>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Shader.h"

namespace Jade {
	class VertexShader : public Shader {
	public:
		VertexShader(const Jade::TextFile& shaderSourceFile);

		VertexShader(const VertexShader& other) = default;
		VertexShader(VertexShader&& other) = default;
		VertexShader& operator=(VertexShader&&) = default;
		VertexShader& operator=(const VertexShader&) = default;
		~VertexShader() = default;

		void dispose() override{ glDeleteShader(getShader()); }
	};
}