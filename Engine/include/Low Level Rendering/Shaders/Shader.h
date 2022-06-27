#pragma once

#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	class Shader {
	public:
		Shader() {}
		virtual void dispose() = 0;
		virtual unsigned int getShader() = 0;

	private:
		unsigned int m_Shader;
		Jade::TextFile m_ShaderSourceFile;
	};
}