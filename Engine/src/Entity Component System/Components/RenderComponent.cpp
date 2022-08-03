#include "Entity Component System/Components/Rendering Components/RenderComponent.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	RenderComponent::~RenderComponent() {}

	void RenderComponent::render() {
		shader->bind();
		shader->bindAdditionals();

		Render();

		shader->getProgram().setMatrix4f("view", gCamera.getViewMatrix());
		shader->getProgram().setMatrix4f("projection", gWindow.getProjectionMatrix());

		for (std::shared_ptr<RenderableObject> renderable : renderables) {
			renderable->render(*shader);
		}
	}
}