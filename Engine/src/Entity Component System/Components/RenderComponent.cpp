#include "Entity Component System/Components/Rendering Components/RenderComponent.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	RenderComponent::~RenderComponent() {}

	void RenderComponent::render(std::shared_ptr<PShader> shader) {
		shader->bind();
		glCheckError();

		shader->uploadUniforms();
		glCheckError();

		calculateModelMatrix();
		shader->getProgram().setMatrix4f("model", m_ModelMatrix);
		glCheckError();

		shader->getProgram().setMatrix4f("view", gCamera.getViewMatrix());
		glCheckError();

		shader->getProgram().setMatrix4f("projection", gWindow.getProjectionMatrix());
		glCheckError();

		glCheckError();

		for (std::shared_ptr<RenderableObject> renderable : renderables) {
			renderable->render(shader);
		}
		glCheckError();

	}
}