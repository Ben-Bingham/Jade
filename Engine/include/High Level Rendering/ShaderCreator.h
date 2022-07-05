#pragma once
#include <vector>

#include "RenderingRuleSet.h"
#include "Low Level Rendering/Shaders/ShaderHeader.h"

namespace Jade {
	class ShaderCreator {
	public:
		ShaderCreator(RenderingRuleSet& ruleSet)
			: m_RuleSet(ruleSet), m_VertexShader(vertexShaderInit()), m_FragmentShader(fragmentShaderInit()) {}

		ShaderProgram createProgram() { return ShaderProgram(m_FragmentShader, m_VertexShader); }

		void dispose() {
			m_VertexShader.dispose();
			m_FragmentShader.dispose();
		}
	private:
		RenderingRuleSet m_RuleSet;

		VertexShader m_VertexShader;
		FragmentShader m_FragmentShader;

		VertexShader& vertexShaderInit();
		FragmentShader& fragmentShaderInit();
	};
}