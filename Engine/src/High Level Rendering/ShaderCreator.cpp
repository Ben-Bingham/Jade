#include "Log.h"

#include "High Level Rendering/ShaderCreator.h"
#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	VertexShader ShaderCreator::vertexShaderInit() {
		std::string vertexShaderPath = "..\\Engine\\assets\\shaders\\";

		switch (m_RuleSet->ruleSet) {
		default:
		case SOLID_COLOUR: vertexShaderPath += "SolidRuleSet.vert"; break;
		case PHONG: vertexShaderPath += "PhongRuleSet.vert"; break;
		}

		TextFile vertexShaderFile(vertexShaderPath);

		return VertexShader(vertexShaderFile);
	}

	FragmentShader ShaderCreator::fragmentShaderInit() {
		std::string fragmentShaderPath = "..\\Engine\\assets\\shaders\\";

		switch (m_RuleSet->ruleSet) {
		default:
		case SOLID_COLOUR: fragmentShaderPath += "SolidRuleSet.frag"; break;
		case PHONG: fragmentShaderPath += "PhongRuleSet.frag"; break;
		}

		TextFile fragmentShaderFile(fragmentShaderPath);

		return FragmentShader(fragmentShaderFile);
	}
}