#include "High Level Rendering/PShaders/PShader.h"
#include "High Level Rendering/ShaderCreator.h"

namespace Jade {
	PShader::PShader(RuleSet rules)
		: m_Program(programInit()), m_ID(getNextID()), ruleSet(rules) {}

	ShaderProgram PShader::programInit() {
		ShaderCreator creator(this);
		ShaderProgram program(creator.getFragmentShader(), creator.getVertexShader());
		return program;
	}

	int PShader::ID = -1;
}