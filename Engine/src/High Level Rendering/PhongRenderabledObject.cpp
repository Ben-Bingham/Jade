#include "High Level Rendering/Renderable Objects/PhongRenderableObject.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void PhongRenderable::uploadUniforms(std::shared_ptr<PShader> shader) {
		Texture::activateUnit(0);
		m_Material->diffuse.bind();
		Texture::activateUnit(1);
		m_Material->specular.bind();
		shader->getProgram().setMaterial("material", *m_Material);

		recalculateModelMatrix();
		shader->getProgram().setMatrix4f("model", m_ModelMatrix);
	}
}