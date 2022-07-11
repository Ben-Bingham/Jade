#pragma once
#include <vector>

#include "Rule Sets/RenderingRuleSet.h"

namespace Jade {
	class ShaderCreator {
	public:
		ShaderCreator(RenderingRuleSet* ruleSet)
			: m_RuleSet(ruleSet), m_VertexShader(vertexShaderInit()), m_FragmentShader(fragmentShaderInit()) {}

		VertexShader getVertexShader() { return m_VertexShader; }
		FragmentShader getFragmentShader() { return m_FragmentShader; }

		void dispose() {
			m_VertexShader.dispose();
			m_FragmentShader.dispose();
		}

	private:
		RenderingRuleSet* m_RuleSet;

		VertexShader m_VertexShader;
		FragmentShader m_FragmentShader;

		VertexShader vertexShaderInit();
		FragmentShader fragmentShaderInit();
	};
}