#pragma once
#include <GL/glew.h>

#include "Log.h"

#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Shader.h"

namespace Jade {
	class FragmentShader : public Shader {
	public:
		FragmentShader(const Jade::TextFile& shaderSourceFile);

		void dispose() override { glDeleteShader(getShader()); }
	};
}
