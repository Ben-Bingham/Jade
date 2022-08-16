#pragma once

#include "RenderableObject.h"

namespace Jade {
	class PhongRenderable : public RenderableObject {
	public:
		PhongRenderable(std::shared_ptr<Material> material, Shape shape = CUBE)
			: RenderableObject(PHONG, shape), m_Material(material) {}

		PhongRenderable(std::shared_ptr<Material> material, Mesh mesh)
			: RenderableObject(PHONG, mesh), m_Material(material) {}

		void uploadUniforms(std::shared_ptr<PShader> shader) override;

	private:
		std::shared_ptr<Material> m_Material;
	};
}