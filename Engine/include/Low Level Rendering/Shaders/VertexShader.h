#pragma once
#include <GL/glew.h>

#include "Core Systems/Logging/Log.h"

#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Shader.h"

namespace Jade {
	class VertexShader : public Shader {
	public:
		VertexShader(const Jade::TextFile& shaderSourceFile);

		void dispose() override { glDeleteShader(getShader()); }
	};
}