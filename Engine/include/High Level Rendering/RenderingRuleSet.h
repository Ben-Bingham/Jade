#pragma once

#include <vector>

#include "Low Level Rendering/Shaders/ShaderHeader.h"

namespace Jade {
	enum RenderingRule {
		VERTEX_POSITIONS,
		VERTEX_NORMALS,
		TEXTURE_CORDINATES
	};

	class RenderingRuleSet {
	public:
		RenderingRuleSet(std::vector<RenderingRule> renderingRules);

		void bind() { m_Program.use(); }

	private:
		std::vector<RenderingRule> m_RenderingRules;
		ShaderProgram m_Program;

		ShaderProgram programInit();
	};
}