#pragma once

#include "RenderableObject.h"

namespace Jade {
	class TexturedRenderable : public RenderableObject {
	public:
		TexturedRenderable(const Texture& diffuse, const Texture& specular, float shininess, Model shape = CUBE)
			: RenderableObject(TEXTURE, shape), m_Material{ diffuse, specular, shininess } {}

		void additionalRendering(const RenderingRuleSet& ruleSet) const override {
			Texture::activateUnit(0);
			m_Material.diffuse.bind();
			Texture::activateUnit(1);
			m_Material.specular.bind();
		}

		TexturedMaterial getMaterial() { return m_Material; }

	private:
		TexturedMaterial m_Material;
	};
}