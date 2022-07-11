#pragma once

#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	class Shader {
	public:
		Shader(unsigned int shaderID, TextFile sourceFile) : m_Shader(shaderID), m_ShaderSourceFile(sourceFile) {}

		virtual void dispose() = 0;

		unsigned int getShader() const { return m_Shader; };

		Jade::TextFile getShaderSourceFile() const { return m_ShaderSourceFile; }

	private:
		unsigned int m_Shader;
		TextFile m_ShaderSourceFile;
	};
}