#pragma once
#include <GL/glew.h>

#include "Core Systems/Logging/Log.h"

#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Shader.h"

namespace Jade {
	class GeometryShader : public Shader {
	public:
		GeometryShader(const Jade::TextFile& shaderSourceFile);

		void dispose() override { glDeleteShader(getShader()); }
	};
}
