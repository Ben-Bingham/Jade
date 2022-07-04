#include "High Level Rendering/RenderingRuleSet.h"
#include "High Level Rendering/ShaderCreator.h"
#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	RenderingRuleSet::RenderingRuleSet() : m_Program(programInit()), m_ID(getNextID()) {}

	void RenderingRuleSet::createProgram() {

	}

	ShaderProgram RenderingRuleSet::programInit() {
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
		vertexShaderPath += std::to_string(this->m_ID);
		vertexShaderPath += ".vert";

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
		fragmentShaderPath += std::to_string(this->m_ID);
		fragmentShaderPath += ".frag";

		TextFile vertexShaderFile(vertexShaderPath, vertexShaderSource);
		TextFile fragmentShaderFile(fragmentShaderPath, fragmentShaderSource);

		VertexShader vertexShader(vertexShaderFile);
		FragmentShader fragmentShader(fragmentShaderFile);

		return ShaderProgram(fragmentShader, vertexShader);
	}

	int RenderingRuleSet::ID = -1;
}