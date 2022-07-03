#include "High Level Rendering/RenderingRuleSet.h"
#include "High Level Rendering/ShaderCreator.h"

namespace Jade {
	RenderingRuleSet::RenderingRuleSet(std::vector<RenderingRule> renderingRules) 
		: m_RenderingRules(std::move(renderingRules)), m_Program(programInit()) {}

	ShaderProgram RenderingRuleSet::programInit() {
		ShaderCreator creator(m_RenderingRules);
		return ShaderProgram(creator.getFragmentShader(), creator.getVertexShader());
	}
}