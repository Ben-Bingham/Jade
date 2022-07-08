#include "High Level Rendering/Rule Sets/RenderingRuleSet.h"
#include "High Level Rendering/ShaderCreator.h"
#include "Core Systems/Resource Pipeline/TextFile.h"
#include <High Level Rendering/RenderableObject.h>

namespace Jade {
	RenderingRuleSet::RenderingRuleSet(RuleSet rules) : m_Program(programInit()), m_ID(getNextID()), ruleSet(rules) {
		/*m_Light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		m_Light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		m_Light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
		m_Light.position = glm::vec3(1.2f, 1.0f, 2.0f);*/
	}

	void RenderingRuleSet::createProgram() {
		m_Program.dispose();
		ShaderCreator creator(this);
		m_Program = creator.createProgram();
		creator.dispose();
	}

	ShaderProgram RenderingRuleSet::programInit() {
		ShaderCreator creator(this);
		ShaderProgram program(creator.createProgram());
		return program;
	}

	int RenderingRuleSet::ID = -1;
}