#pragma once

#include "RenderableObject.h"
#include "High Level Rendering/MaterialCreator.h"
#include "Core Systems/Resource Pipeline/Model.h"

namespace Jade {
	class StandardRenderable : public RenderableObject {
	public:
		StandardRenderable(Shape shape = CUBE) 
			: RenderableObject(STANDARD, shape), m_Material(MaterialCreator::DefaultMaterial()) {}

		StandardRenderable(Mesh mesh)
			: RenderableObject(STANDARD, mesh), m_Material(MaterialCreator::DefaultMaterial()) {
		}

		void additionalRendering(const RenderingRuleSet& ruleSet) const override {
			ruleSet.getProgram().setMaterial("material", m_Material);
		}

	private:
		Material m_Material;
	};
}