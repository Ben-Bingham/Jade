#pragma once

#include "PShader.h"

namespace Jade {
	class SolidRuleSet : public PShader {
	public:
		SolidRuleSet() : PShader(SOLID_COLOUR) {}

		void bindAdditionals() override {}

	private:
	};
}