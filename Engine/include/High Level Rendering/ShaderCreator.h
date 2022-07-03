#pragma once
#include <vector>

#include "RenderingRuleSet.h"
#include "Low Level Rendering/Shaders/ShaderHeader.h"

namespace Jade {
	class ShaderCreator {
	public:
		ShaderCreator(std::vector<RenderingRule>& renderingRules) {}

		VertexShader getVertexShader() {
			return VertexShader(TextFile("f"));
		}

		FragmentShader getFragmentShader() {
			return FragmentShader(TextFile("f"));

		}

	private:

	};
}