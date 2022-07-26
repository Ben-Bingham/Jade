#include "Entity Component System/Components/PhongRenderingComponent.h"
#include "Engine Structure/Application.h"

namespace Jade {
	void PhongRenderingComponent::addRenderables(Application& app) {
		for (PhongRenderable& renderable : m_Renderables) {
			app.addRenderable(&renderable);
		}
	}
}