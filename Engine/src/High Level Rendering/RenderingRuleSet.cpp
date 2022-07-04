#include "High Level Rendering/RenderingRuleSet.h"
#include "High Level Rendering/ShaderCreator.h"
#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	RenderingRuleSet::RenderingRuleSet() : m_Program(programInit()), m_ID(getNextID()) {}

	void RenderingRuleSet::createProgram() {
		ShaderCreator creator(*this);
		m_Program = creator.createProgram();
	}

	ShaderProgram RenderingRuleSet::programInit() {
		ShaderCreator creator(*this);
		return creator.createProgram();
	}

	int RenderingRuleSet::ID = -1;
}