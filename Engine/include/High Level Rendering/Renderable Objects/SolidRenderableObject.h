#pragma once

#include <glm/glm.hpp>

#include "RenderableObject.h"

namespace Jade {
	class SolidRenderable : public RenderableObject {
	public:
		SolidRenderable(glm::vec4 objectColour, Model shape = CUBE)
			: RenderableObject(SOLID_COLOUR, shape), m_ObjectColour(objectColour) {
		}

		void additionalRendering(const RenderingRuleSet& ruleSet) const override {
			ruleSet.getProgram().setVector4f("objectColour", m_ObjectColour);
		}

	private:
		glm::vec4 m_ObjectColour;
	};
}