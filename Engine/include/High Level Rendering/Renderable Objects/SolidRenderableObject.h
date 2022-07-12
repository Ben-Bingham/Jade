#pragma once

#include <glm/glm.hpp>

#include "RenderableObject.h"
#include "High Level Rendering/Colour.h"

namespace Jade {
	class SolidRenderable : public RenderableObject {
	public:
		SolidRenderable(Colour objectColour, Shape shape = CUBE)
			: RenderableObject(SOLID_COLOUR, shape), m_ObjectColour(objectColour) {
		}

		void additionalRendering(const RenderingRuleSet& ruleSet) const override {
			ruleSet.getProgram().setVector4f("objectColour", m_ObjectColour.colour);
		}

	private:
		Colour m_ObjectColour;
	};
}