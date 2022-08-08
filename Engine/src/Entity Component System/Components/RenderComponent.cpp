#include "Entity Component System/Components/Rendering Components/RenderComponent.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	RenderComponent::~RenderComponent() {}

	void RenderComponent::render(std::shared_ptr<PShader> shader) {
		shader->bind();
		shader->bindAdditionals();

		calculateModelMatrix();
		shader->getProgram().setMatrix4f("model", m_ModelMatrix);
		shader->getProgram().setMatrix4f("view", gCamera.getViewMatrix());
		shader->getProgram().setMatrix4f("projection", gWindow.getProjectionMatrix());

		for (std::shared_ptr<RenderableObject> renderable : renderables) {
			renderable->render(*shader);
		}
	}
}