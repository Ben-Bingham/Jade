#pragma once
#include <vector>

#include "PShaders/PShader.h"

namespace Jade {
	class ShaderCreator {
	public:
		ShaderCreator(PShader* ruleSet)
			: m_RuleSet(ruleSet), m_VertexShader(vertexShaderInit()), m_FragmentShader(fragmentShaderInit()), m_GeometryShader(geometryShaderInit()) { }

		VertexShader getVertexShader() { return m_VertexShader; }
		FragmentShader getFragmentShader() { return m_FragmentShader; }
		GeometryShader getGeometryShader() { return m_GeometryShader; }

		void dispose() {
			m_VertexShader.dispose();
			m_FragmentShader.dispose();
			m_GeometryShader.dispose();
		}

	private:
		PShader* m_RuleSet;

		VertexShader m_VertexShader;
		FragmentShader m_FragmentShader;
		GeometryShader m_GeometryShader;

		VertexShader vertexShaderInit();
		FragmentShader fragmentShaderInit();
		GeometryShader geometryShaderInit();
	};
}