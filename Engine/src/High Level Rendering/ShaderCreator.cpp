#include "High Level Rendering/ShaderCreator.h"

namespace Jade {
	VertexShader ShaderCreator::vertexShaderInit() {
		std::string vertexShaderSource =
			"#version 330 core\n\
\n\
layout (location = 0) in vec3 inputPositon;\n\
\n\
void main()\n\
{\n\
	gl_Position = vec4(inputPositon, 1.0);\n\
}\0";

		std::string vertexShaderPath = "assets\\shaders\\ruleSet";
		vertexShaderPath += std::to_string(m_RuleSet.getID());
		vertexShaderPath += ".vert";

		return VertexShader(TextFile(vertexShaderPath, vertexShaderSource));
	}

	FragmentShader ShaderCreator::fragmentShaderInit() {
		std::string fragmentShaderSource =
			"#version 330 core\n\
\n\
out vec4 FragColor;\n\
\n\
void main()\n\
{\n\
	FragColor = vec4(1.0);\n\
}\0";
		std::string fragmentShaderPath = "assets\\shaders\\ruleSet";
		fragmentShaderPath += std::to_string(m_RuleSet.getID());
		fragmentShaderPath += ".frag";

		return FragmentShader(TextFile(fragmentShaderPath, fragmentShaderSource));
	}
}