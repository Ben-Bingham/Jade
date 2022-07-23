#pragma once

#include "RenderableObject.h"
#include "Core Systems/Logging/OpenGLErrors.h"

namespace Jade {
	class DiffusedRenderable : public RenderableObject {
	public:
		DiffusedRenderable(const Texture& diffuse, const glm::vec3& specular, float shininess, Shape shape = CUBE) //TODO change specular to Colour class
			: RenderableObject(DIFFUSE, shape), m_Material{ diffuse, specular, shininess } {}

		DiffusedRenderable(const Texture& diffuse, const glm::vec3& specular, float shininess, Mesh mesh)
			: RenderableObject(DIFFUSE, mesh), m_Material{ diffuse, specular, shininess } {}

		void additionalRendering(const RenderingRuleSet& ruleSet) const override {
			Texture::activateUnit(0);
			glCheckError();
			m_Material.diffuse.bind();
			glCheckError();
			ruleSet.getProgram().setDiffuseMaterial("material", getMaterial());
			glCheckError();
		}

		DiffuseMaterial getMaterial() const { return m_Material; }

	private:
		DiffuseMaterial m_Material;
	};
}