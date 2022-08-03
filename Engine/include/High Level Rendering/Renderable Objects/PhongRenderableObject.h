#pragma once

#include "RenderableObject.h"

namespace Jade {
	class PhongRenderable : public RenderableObject {
	public:
		PhongRenderable(std::shared_ptr<Material> material, Shape shape = CUBE)
			: RenderableObject(PHONG, shape), m_Material(material) {}

		PhongRenderable(std::shared_ptr<Material> material, Mesh mesh)
			: RenderableObject(PHONG, mesh), m_Material(material) {}

		void additionalRendering(const PShader& ruleSet) const override {
			Texture::activateUnit(0);
			m_Material->diffuse.bind();
			Texture::activateUnit(1);
			m_Material->specular.bind();
			ruleSet.getProgram().setMaterial("material", *m_Material);
		}

	private:
		std::shared_ptr<Material> m_Material;
	};
}