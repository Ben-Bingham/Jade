#include "High Level Rendering/RenderingRuleSet.h"
#include "High Level Rendering/ShaderCreator.h"
#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	RenderingRuleSet::RenderingRuleSet() : m_Program(programInit()), m_ID(getNextID()) {}

	void RenderingRuleSet::createProgram() {
		processRules();
		m_Program.dispose();
		ShaderCreator creator(*this);
		m_Program = creator.createProgram();
		creator.dispose();
	}

	ShaderProgram RenderingRuleSet::programInit() {
		ShaderCreator creator(*this);
		ShaderProgram program(creator.createProgram());
		return program;
	}

	int RenderingRuleSet::ID = -1;
}