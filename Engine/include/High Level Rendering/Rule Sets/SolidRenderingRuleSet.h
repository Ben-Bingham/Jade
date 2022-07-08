#pragma once

#include "RenderingRuleSet.h"

namespace Jade {
	class SolidRuleSet : public RenderingRuleSet {
	public:
		SolidRuleSet() : RenderingRuleSet(SOLID_COLOUR) {}

		void bindAdditionals() override {}

	private:
	};
}