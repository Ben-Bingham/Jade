#pragma once

#include "RenderableObject.h"
#include "High Level Rendering/MaterialCreator.h"

namespace Jade {
	class StandardRenderable : public RenderableObject {
	public:
		StandardRenderable(Model shape = CUBE) 
			: RenderableObject(STANDARD, shape), m_Material(MaterialCreator::DefaultMaterial()) {}

		void additionalRendering(const RenderingRuleSet& ruleSet) const override {
			ruleSet.getProgram().setMaterial("material", m_Material);
		}

	private:
		Material m_Material;
	};
}