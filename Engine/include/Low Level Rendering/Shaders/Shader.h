#pragma once

#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	class Shader { //TODO could be a lot better, duel defines of m_Shader and source file
	public:
		virtual void dispose() = 0;

		unsigned int getShader() { return m_Shader; };
		void setShader(unsigned int shader) { m_Shader = shader; }

		Jade::TextFile getShaderSourceFile() { return m_ShaderSourceFile; }
		void setShaderSourceFile(Jade::TextFile shaderSource) { m_ShaderSourceFile = shaderSource; }

	private:
		unsigned int m_Shader;
		Jade::TextFile m_ShaderSourceFile;
	};
}