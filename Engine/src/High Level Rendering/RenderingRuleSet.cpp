#include "High Level Rendering/Rule Sets/RenderingRuleSet.h"
#include "High Level Rendering/ShaderCreator.h"
#include "Core Systems/Resource Pipeline/TextFile.h"
#include "High Level Rendering/Renderable Objects/RenderableObject.h"

namespace Jade {
	RenderingRuleSet::RenderingRuleSet(RuleSet rules) : m_Program(programInit()), m_ID(getNextID()), ruleSet(rules) {}

	ShaderProgram RenderingRuleSet::programInit() {
		ShaderCreator creator(this);
		ShaderProgram program(creator.getFragmentShader(), creator.getVertexShader());
		return program;
	}

	int RenderingRuleSet::ID = -1;
}