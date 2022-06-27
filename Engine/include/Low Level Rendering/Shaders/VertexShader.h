#pragma once
#include <GL/glew.h>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Shader.h"

namespace Jade {
	class VertexShader : public Shader {
	public:
		VertexShader(Jade::TextFile& shaderSourceFile);
		VertexShader(std::string& path);
		VertexShader(std::string&& path);

		~VertexShader() {
			dispose();
		}

		void dispose() override{ glDeleteShader(m_Shader); }

		unsigned int getShader() override{ return m_Shader; }

	private:
		unsigned int m_Shader;
		Jade::TextFile m_ShaderSourceFile;
	};
}